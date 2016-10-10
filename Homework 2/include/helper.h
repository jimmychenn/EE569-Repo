#ifndef HELPER_H
#define HELPER_H
#include "bayermatrix.h"
#include "errordiffusion.h"
#include <vector>

image_type dither(image_type image, filter T) {
	for(int y = 0; y < image.shape()[0]; y++) {
		for(int x = 0; x < image.shape()[1]; x++) {
			for(int k = 0; k < image.shape()[2]; k++) {
				int f_y = y%T.shape()[0];
				int f_x = x%T.shape()[1];
				if(image[y][x][k] > T[f_y][f_x]) {
					image[y][x][k] = 255;
				} else {
					image[y][x][k] = 0;
				}
			}
		}
	}
	return image;
}

double_image_type floyd_steinberg(double_image_type image) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	int bytes = image.shape()[2];
	for(int y = 0; y < height; y++) {
		int x_start;
		int x_end;
		int inc;
		if(y%2 == 0) {
			x_start = 0;
			x_end = width;
			inc = 1;
		} else if(y%2 == 1) {
			x_start = width - 1;
			x_end = -1;
			inc = -1;
		}
		for(int x = x_start; x != x_end; x += inc) {
			for(int k = 0; k < bytes; k++) {
				int p = image[y][x][k];
				if(p > 127)
					image[y][x][k] = 255;
				else
					image[y][x][k] = 0;
				double error = p - image[y][x][k];
				int l_index = x - 1;
				int r_index = x + 1;
				int b_index = y + 1;

				//right of center
				if(r_index < width)
					image[y][r_index][k] += error*0.4375;
				//bottom left of center
				if(b_index < height && l_index >= 0)
					image[b_index][l_index][k] += error*0.1875;
				//bottom of center
				if(b_index < height)
					image[b_index][x][k] += error*0.3125;
				//bottom right of center
				if(r_index < width && b_index < height)
					image[b_index][r_index][k] += error*0.0625;
			}
		}
	}
	return image;
}

double_image_type error_diffusion(double_image_type image, double_filter T) {
	int f_height = T.shape()[0];
	int f_width = T.shape()[1];

	int height = image.shape()[0];
	int width = image.shape()[1];
	int bytes = image.shape()[2];
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			for(int k = 0; k < bytes; k++) {
				int p = image[y][x][k];
				if(p > 127)
					image[y][x][k] = 255;
				else
					image[y][x][k] = 0;
				double error = p - image[y][x][k];
				
				for(int fy = f_height/2; fy < f_height; fy++) {
					for(int fx = 0; fx < f_width; fx++) {
						int y_ind = y + fy - f_height/2;
						int x_ind = x + fx;
						//std::cout << y_ind << " " << x_ind << std::endl;
						if(y_ind > 0 && y_ind < height && x_ind > 0 && x_ind < width)
							image[y_ind][x_ind][k] += error * T[fy][fx];
					}
				}
			}
		}
	}
	return image;
}

double_image_type unsigned_char_image_to_double(image_type image) {
	double_image_type double_image(boost::extents[image.shape()[0]][image.shape()[1]][image.shape()[2]]);
	for(int i = 0; i < image.shape()[0]; i++) {
		for(int j = 0; j < image.shape()[1]; j++) {
			for(int k = 0; k < image.shape()[2]; k++) {
				double_image[i][j][k] = image[i][j][k];
			}
		}
	}
	return double_image;
}

image_type double_image_to_unsigned_char(double_image_type double_image) {
	image_type image(boost::extents[double_image.shape()[0]][double_image.shape()[1]][double_image.shape()[2]]);
	for(int i = 0; i < image.shape()[0]; i++) {
		for(int j = 0; j < image.shape()[1]; j++) {
			for(int k = 0; k < image.shape()[2]; k++) {
				image[i][j][k] = double_image[i][j][k];
			}
		}
	}
	return image;
}

image_type to_grayscale(image_type image) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	int bytes = image.shape()[2];
	image_type grayscale_image(boost::extents[height][width][1]);
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			grayscale_image[i][j][0] = (double) image[i][j][0] * 0.3
									 + (double) image[i][j][1] * 0.59
									 + (double) image[i][j][2] * 0.11;
		}
	}
	return grayscale_image;
}


image_type binarize(image_type image, int num) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	int bytes = image.shape()[2];

	image_type binarized_image(boost::extents[height][width][1]);

	//global mean as threshold
	if(num == 1) {
		int sum = 0;
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				for(int k = 0; k < bytes; k++) {
					sum += image[y][x][k];
				}
			}
		}
		int threshold = sum / (height * width);

		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				for(int k = 0; k < bytes; k++) {
					if(image[y][x][k] > threshold) binarized_image[y][x][k] = 255;
					else binarized_image[y][x][k] = 0;
				}
			}
		}

	}
	//adaptive binarization
	//local mean of pixel neighborhood
	//VERY SLOW
	if(num == 2) {
		int filt_size = 25;
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				for(int k = 0; k < bytes; k++) {
					int sum = 0;
					for(int fy = -filt_size/2; fy < /*maybe add an = here */ filt_size/2; fy++) {
						for(int fx = -filt_size/2; fx < filt_size/2; fx++) {
							int y_ind = y + fy;
							int x_ind = x + fx;
							if(y_ind < 0) y_ind = height + fy;
							if(x_ind < 0) x_ind = width + fy;
							if(y_ind >= height) y_ind %= height;
							if(x_ind >= width) x_ind %= width;

							//std::cout << y_ind << " " << x_ind << std::endl;

							sum += image[y_ind][x_ind][k];
						}
					}
					int threshold = sum / (filt_size * filt_size);
					if(image[y][x][k] > threshold) binarized_image[y][x][0] = 0;
					else binarized_image[y][x][0] = 255;

				}
			}
		}
	}

	//Otsu method
	//inspecting the histogram, most of the background pixels are at a grayscale value of 72
	if(num == 3) {

	}

	return binarized_image;
}

image_type median_filter(image_type image) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	int bytes = image.shape()[2];

	image_type filtered_image(boost::extents[height][width][bytes]);
	std::vector<int> med_filter;
	int f_size = 3;
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				//Iterating over the filter space
				for(int u = -f_size/2; u <= f_size/2; u++) {
					for(int v = -f_size/2; v <= f_size/2; v++) {
						int y = (i + u) % height;
						int x = (j + v) % width;
						if(x < 0) x += width;
						if(y < 0) y += height;
						//std::cout << y << " " << x << std::endl;

						//std::cout << x << " " << y << std::endl;
						med_filter.push_back(image[y][x][k]);
					}
				}
				//std::cout << std::endl;
				sort(med_filter.begin(), med_filter.end());
				int index = f_size*f_size/2;
				int med = med_filter[index];

				filtered_image[i][j][k] = med;

				med_filter.clear();
			}
		}
	}
	return filtered_image;
}

//*TODO*//
/*
//Recursive function that returns a Bayer Identity matrix given the size
filter createBayesFilter(int size) {
	filter filt;
	if(size%2 != 0) {
		return filt;
	}
	if(size == 2) {
		filter I2(boost::extents[2][2]);
		I2[0][0] = 0; I2[0][1] = 2; I2[1][0] = 3; I2[1][1] = 1;
	}
}
*/

#endif