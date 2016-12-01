#include <iostream>
#include <opencv2/core.hpp>
#include "readraw.h"
#include "helper.h"
#include "laws.h"
#include "kmeans.c"


using namespace std;

vector<long long> create_fvector(char* input, Laws Laws) {
	Mat image = read(input, 128, 128, 1);
	Mat double_image;
	int mean = subtract_DC_component(image);
	//cout << mean << endl;
	image.convertTo(double_image, CV_32S, 1, -mean);


	/*
	for(int i = 0; i < Laws.filts.size(); i++) {
		cout << i << endl;
		print_filter(Laws.filts[i]);
	}
	*/

	int max = 0;
	vector<long long> f_vector;
	for(int i = 0; i < Laws.filts.size(); i++) {
		Mat f_resp = convolve(double_image, Laws.filts[i]);
		//print_filter(Laws.filts[i]);
		long long energy = sum(f_resp)[0];
		energy /= (128 * 128);
		if(energy > max) max = energy;
		// cout << energy << endl;
		f_vector.push_back(energy);
	}

	return f_vector;
}

vector<vector<double> > normalize( vector<vector<long long> > f_vectors) {
	vector<vector<double> > f_vectors_norm;
	for(int i = 0; i < f_vectors.size(); i++) {
		double max = 0;
		vector<double> f_vector_norm;
		for(int j = 0; j < f_vectors[i].size(); j++) {
			if(f_vectors[i][j] > max)
				max = f_vectors[i][j];
		}
		for(int j = 0; j < f_vectors[i].size(); j++) {
			double val = f_vectors[i][j]/max;
			f_vector_norm.push_back(val);
		}
		f_vectors_norm.push_back(f_vector_norm);
	}

	return f_vectors_norm;
}

int main() {
	Global Global;
	Laws Laws;
	int height = 128;
	int width = 128;

	vector<vector<long long> > f_vectors;
	//1,4,6 is class A
	//2,9,12 is class B
	//7,8,10 is class C
	//3,5,11 is class D
	f_vectors.push_back(create_fvector(P1A_IN1, Laws));
	f_vectors.push_back(create_fvector(P1A_IN4, Laws));
	f_vectors.push_back(create_fvector(P1A_IN6, Laws));
	f_vectors.push_back(create_fvector(P1A_IN2, Laws));
	f_vectors.push_back(create_fvector(P1A_IN9, Laws));
	f_vectors.push_back(create_fvector(P1A_IN12, Laws));
	f_vectors.push_back(create_fvector(P1A_IN7, Laws));
	f_vectors.push_back(create_fvector(P1A_IN8, Laws));
	f_vectors.push_back(create_fvector(P1A_IN10, Laws));
	f_vectors.push_back(create_fvector(P1A_IN3, Laws));
	f_vectors.push_back(create_fvector(P1A_IN5, Laws));
	f_vectors.push_back(create_fvector(P1A_IN11, Laws));

	vector<vector<double> > f_vectors_norm = normalize(f_vectors);

	Mat f_matrix = Mat(12, 25, CV_64F, Scalar::all(0));
	//double data_points[12][25];
	double** data_points = new double*[12];
	for(int i = 0; i < 12; i++) {
		data_points[i] = new double[25];
	}

	for(int i = 0; i < f_vectors.size(); i++) {
		for(int j = 0; j < f_vectors[i].size(); j++) {
			f_matrix.at<double>(i,j) = f_vectors_norm[i][j];
			//cout << f_matrix.at<double>(j,i) << " ";
			data_points[i][j] = f_vectors_norm[i][j]; 
		}
		cout << endl;
	}
	//PCA::DATA_AS_ROW = 0
	//PCA::DATA_AS_COL = 1
	PCA pca_analysis(f_matrix, Mat(), 1, 3);
	// cout << f_matrix.rows << endl;
	// cout << f_matrix.cols << endl;

	// cout << pca_analysis.eigenvectors.rows << endl;
	// cout << pca_analysis.eigenvectors.cols << endl;

	for(int i = 0; i < 12; i++) {
		for(int j = 0; j < 3; j++) {
			cout << pca_analysis.eigenvectors.at<double>(j,i) << " ";	
		}
		cout << endl;
	}
	int num_points = 12;
	int* c = k_means(data_points, num_points, 25, 4, 100, 0);

	for (int i = 0; i < num_points; i++) {
		printf("data point %d is in cluster %d\n", i, c[i]);
	}
	free(c);

	double** data_points_pca = new double*[12];
	for(int i = 0; i < 12; i++) {
		data_points_pca[i] = new double[3];
		for(int j = 0; j < 3; j++) {
			data_points_pca[i][j] = pca_analysis.eigenvectors.at<double>(j,i);
		}
	}
	c = k_means(data_points_pca, num_points, 3, 4, 0.0001, 0);
	for (int i = 0; i < num_points; i++) {
		printf("data point %d is in cluster %d\n", i, c[i]);
	}
	free(c);

/*
	//for each feature
	for(int k = 0; k < f_vectors[0].size(); k++) {
		cout << k << endl;
		vector<int> means;
		//for each class
		long long inter_class_var = 0;
		for(int i = 0; i < 4; i++) {
			long long mean = (f_vectors[i*3][k] + f_vectors[i*3+1][k] + f_vectors[i*3+2][k])/3;
			means.push_back(mean);
			
			//all class instances
			long long intra_class_var = 0;
			for(int j = 0; j < 3; j++) {
				int index = i * 3 + j;
				intra_class_var += pow(f_vectors[index][k] - mean,2);
			}
			intra_class_var /= 3;
			cout << "Intra-class variance:" << intra_class_var << endl;
		}

		//calculate mean
		long long mean = (means[0] + means[1] + means[2] + means[3])/4;
		for(int i = 0; i < 4; i++) {
			inter_class_var += pow(means[i] - mean, 2);
		}

		inter_class_var /= 4;
		cout << "Inter-class variance:" << inter_class_var << endl;
		
	}
*/
	for(int i = 0; i < 12; i++) {
		delete[] data_points[i];
		delete[] data_points_pca[i];
	}


	return 0;
}