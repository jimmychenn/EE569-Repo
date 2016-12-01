#include <iostream>
#include <opencv2/core.hpp>
#include "readraw.h"
#include "helper.h"
#include "laws.h"
#include "kmeans.c"

using namespace std;

Mat getEnergyOfPixelsInWindow(Mat image, int N) {
	int height = image.size[0];
	int width = image.size[1];
	int bytes = image.size[2];
	int sz[] = {height, width, bytes};
	Mat energy_mat(3, sz, CV_64F, Scalar::all(0));
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				// cout << "i,j,k:" << i << "," << j << "," << k << endl;
				double energy = 0;
				for(int u = -N/2; u <= N/2; u++) {
					for(int v = -N/2; v <= N/2; v++) {
						int y = (i + u) % height;
						int x = (j + v) % width;
						if(x < 0) x += width;
						if(y < 0) y += height;
						//cout << "pixel:" << image.at<int>(y,x,k) << endl;
						energy += pow(image.at<int>(y,x,k),2);
					}
				}
				//cout << "energy:" << energy << endl;
				energy_mat.at<double>(i,j,k) = energy;
			}
		}
	}
	return energy_mat;
}

vector<Mat> create_energy_mat(char* input, Laws Laws) {
	Mat image = read(input, 500, 425, 1);
	Mat double_image;
	int mean = subtract_DC_component(image);
	image.convertTo(double_image, CV_32S, 1, 0);
	vector<Mat> e_vector;

	for(int i = 0; i < Laws.filts.size(); i++) {
		Mat f_resp = convolve(double_image, Laws.filts[i]);
		// print_filter(Laws.filts[i]);
		// print_image(double_image);
		//print_image(energy_mat);
		e_vector.push_back(getEnergyOfPixelsInWindow(f_resp, 13));
	}
	// print_image(e_vector[0]);

	return e_vector;
}

void normalize_energy(vector<Mat>& features) {
	int height = features[0].size[0];
	int width = features[0].size[1];
	int bytes = features[0].size[2];
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				for(int f = 1; f < features.size(); f++) {
				// cout << features[f].at<double>(i,j,k) << endl;
					features[f].at<double>(i,j,k) /= features[0].at<double>(i,j,k);
				// cout << features[f].at<double>(i,j,k) << endl;
				}
			}
		}
	}
	features[0].setTo(Scalar(1));
}


int main() {
	Global Global;
	Laws Laws;
	//for comb_1
	int height = 512;
	int width = 512;

	vector<Mat> e_vector = create_energy_mat(P1B_IN1, Laws);


	normalize_energy(e_vector);

	// for(int i = 0; i < e_vector.size(); i++) {
	// 	cout << e_vector[i].at<double>(3,4) << endl;
	// }


	int num_points = height*width;
	double** data_points = new double*[num_points];
	for(int i = 0; i < num_points; i++) {
		data_points[i] = new double[25];
		for(int j = 0; j < 25; j++) {
			int x = i % width;
			int y = i / width;
			//cout << "i:" << i << " j:" << j << endl;
			//cout << "y:" << y << " x:" << x << endl;
			data_points[i][j] = e_vector[j].at<double>(y,x);

		}
	}

	int* c = k_means(data_points, num_points, 25, 4, 1, 0);
	
	int sz[] = {height, width, 1};
	Mat segmented_image(3, sz, CV_8U, Scalar::all(0));
	for (int i = 0; i < num_points; i++) {
		int x = i % width;
		int y = i / width;
		if(c[i] == 0)
			segmented_image.at<uchar>(y,x) = 0;
		else if(c[i] == 1)
			segmented_image.at<uchar>(y,x) = 85;
		else if(c[i] == 2)
			segmented_image.at<uchar>(y,x) = 170;
		else if(c[i] == 3)
			segmented_image.at<uchar>(y,x) = 255;
		printf("data point %d is in cluster %d\n", i, c[i]);
	}
	//data_points
	write(segmented_image, "SegmentedImage.raw");

	for(int i = 0; i < num_points; i++)
		delete[] data_points[i];

	free(c);

	return 0;
}