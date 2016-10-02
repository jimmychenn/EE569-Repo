// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int FILT_SIZE = 3;
const int SEARCH_SIZE = 4;
const double W_STD = 17;

int main(int argc, char *argv[]) {
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
	int Width;
	int Height;
	double PSNR_ave;
	
	// Check for proper syntax
	if (argc < 6){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image_noisy.raw input_image_clean.raw output_image width height" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc == 6){
		Width = atoi(argv[4]);
		Height = atoi(argv[5]);
	} 
	
	// Allocate image data array
	unsigned char NoisyImageData[Height][Width][BytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(NoisyImageData, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	unsigned char OriginalImageData[Height][Width][BytesPerPixel];
	if(!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fread(OriginalImageData, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);



	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	//Get PSNR Values
	double PSNR[3] = {0};
	double MSE[3] = {0};
	for(int k = 0; k < BytesPerPixel; k++) {
		for(int i = 0; i < Height; i++) {
			for(int j = 0; j < Width; j++) {
				int diff = NoisyImageData[i][j][k] - OriginalImageData[i][j][k];
				MSE[k] += pow(diff, 2);
			}
		}
		MSE[k] /= Height * Width;
		PSNR[k] = 10 * log10( pow(255, 2) / MSE[k]);
		//cout << "Channel " << k << " PSNR:" << PSNR[k] << " MSE:" << MSE[k] << endl;
	}
	PSNR_ave = (PSNR[0] + PSNR[1] + PSNR[2])/3.0;
	cout << "Original Ave_PSNR:" << PSNR_ave << endl;


	unsigned char TargetImageData[Height][Width][BytesPerPixel];

	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				//When the search window hits the end of the image, the search window simply stays at the same location and does not wrap
				int i_start = i;
				int j_start = j;
				if(i_start > Height - SEARCH_SIZE) {
					i_start = Height - SEARCH_SIZE;
				}
				//cout << "i_start: " << i_start << " ";
				if(j_start > Width - SEARCH_SIZE) {
					j_start = Width - SEARCH_SIZE;
				}
				//cout << "j_start: " << j_start << endl;

				double new_pixel = 0;
				double w_arr[SEARCH_SIZE][SEARCH_SIZE] = {0};
				double sum = 0;
				//iterating through every pixel in the search space
				for(int q = i_start; q < i_start + SEARCH_SIZE; q++) {
					for(int p = j_start; p < j_start + SEARCH_SIZE; p++) {

						//cout << "\tsearching pixel: " << q << "," << p << endl;

						double eu_dist = 0;
						//iterating through every pixel in the filter
						//not wrapping around to ensure different areas covered by filter window at boundaries 
						for(int u = 0; u < FILT_SIZE; u++) {
							for(int v = 0; v < FILT_SIZE; v++) {
								int x_ori = (i + u - 1) % Height;
								int y_ori = (j + v - 1) % Width;
								if(x_ori < 0) x_ori += Height;
								if(y_ori < 0) y_ori += Width;

								int x_search = (q + u - 1) % SEARCH_SIZE;
								int y_search = (p + v - 1) % SEARCH_SIZE;
								if(x_search < 0) x_search += SEARCH_SIZE;
								if(y_search < 0) y_search += SEARCH_SIZE;

								eu_dist += pow(OriginalImageData[x_ori][y_ori][k] - OriginalImageData[x_search][y_search][k], 2);
								//cout << "original:" << x_ori << "," << y_ori << " val:" << arr[x_ori][y_ori];
								//cout << " compare:" << x_search << "," << y_search << " val:" << arr[x_search][y_search] << endl;
							}
						}
						eu_dist /= pow(FILT_SIZE, 2);
						double w = exp(-eu_dist / (2 * pow(W_STD,2)));
						w_arr[q - i_start][p - j_start] = w;
						new_pixel += w * OriginalImageData[q][p][k];

						//cout << "\t" << i << "," << j << " and " << q << "," << p << endl;
						//cout << "\t\t" << "Euclidean distance " << eu_dist << endl;
						//cout << "\t\t" << "Weight " << w << " sanitycheck:" << w_arr[q - i_start][p - j_start] << endl;

						sum += w;
					}
				}


				//cout << "Sum of all weights:" << sum << endl;
				new_pixel /= sum;
				TargetImageData[i][j][k] = new_pixel;
				//cout << "\tNew Pixel Value:" << new_pixel << endl;
			}			
		}
	}


	//Get PSNR Values
	for(int k = 0; k < BytesPerPixel; k++) {
		for(int i = 0; i < Height; i++) {
			for(int j = 0; j < Width; j++) {
				int diff = TargetImageData[i][j][k] - OriginalImageData[i][j][k];
				MSE[k] += pow(diff, 2);
			}
		}
		MSE[k] /= Height * Width;
		PSNR[k] = 10 * log10( pow(255, 2) / MSE[k]);
		//cout << "Channel " << k << " PSNR:" << PSNR[k] << " MSE:" << MSE[k] << endl;
	}
	PSNR_ave = (PSNR[0] + PSNR[1] + PSNR[2])/3;
	cout << "\tAve_PSNR:\t" << PSNR_ave << endl;

	// Write image data (filename specified by second argument) from image data matrix
	string toName(argv[3]);

	string fileName = toName + "nlm_filter3_search4_std17.raw";
	if (!(file=fopen(fileName.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(TargetImageData, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	return 0;
}
