#ifndef HELPER_H
#define HELPER_H
#include <cmath>
#include <iomanip>

double subtract_DC_component(Mat& image) {
	int height = image.size[0];
	int width = image.size[1];
	int bytes = image.size[2];
	double ave = 0;

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				ave += image.at<uchar>(i,j,k);
			}
		}
	}
	ave /= (width * height);

	return ave;
}

//convolution filtering for Laws filtering
Mat convolve(Mat image, Mat filter) {
	int height = image.size[0];
	int width = image.size[1];
	int bytes = image.size[2];
	int sz[] = {height, width, bytes};
	Mat filtered_image(3, sz, image.type(), Scalar::all(0));

	int f_height = filter.rows;
	int f_width = filter.cols;

	// std::cout << "height:" << height << " " << "width:" << width << std::endl;
	// std::cout << "f_height:" << f_height << " " << "f_width:" << f_width << std::endl;

	long energy = 0;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				int conv = 0;				
				for(int u = -f_height/2; u <= f_height/2; u++) {
					for(int v = -f_width/2; v <= f_width/2; v++) {
						int f_y = u + f_height/2;
						int f_x = v + f_width/2;
						int y = (i + u) % height;
						int x = (j + v) % width;
						if(x < 0) x += width;
						if(y < 0) y += height;

						// std::cout << "y:" << y << " " << "x:" << x;
						// std::cout << " f_y:" << f_y << " " << "f_x:" << f_x << std::endl;

						 // std::cout << "\tf:" << filter.at<double>(f_y,f_x);
						 // std::cout << " i: " << image.at<int>(y,x) << std::endl;
						conv += filter.at<double>(f_y,f_x) * image.at<int>(y,x);
					}
				}
				filtered_image.at<int>(i,j,k) = pow(conv,2);
				//std::cout << conv << " ";
				energy += pow(conv,2);
				//std::cout << "e:" << energy << " ";
			}
		}
		//std::cout << std::endl;
	}
	//std::cout << "Total energy:" << energy << std::endl;
	return filtered_image;
}


void print_filter(Mat filter) {
	int height = filter.rows;
	int width = filter.cols;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			//std::cout << "i:" << i << " j:" << j << std::endl;
			std::cout << std::setw(3) << filter.at<double>(i,j) << " ";
		}
		std::cout << std::endl;
	}
}

void print_image(Mat image) {
	int height = image.size[0];
	int width = image.size[1];
	int bytes = image.size[2];
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				std::cout << image.at<int>(i,j) << ",";
			}
			std::cout << " ";				
		}
		std::cout << std::endl;
	}
}

#endif