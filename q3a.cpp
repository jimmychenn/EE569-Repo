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

bool SPLIT_RGB = false;
const int MED_FILT_SIZE = 3;

int main(int argc, char *argv[]) {
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
	int Width;
	int Height;
	
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
	unsigned char TargetImageData[Height][Width][BytesPerPixel];
	unsigned char TargetImageData2[Height][Width][BytesPerPixel];

	unsigned char NoisyImageDataR[Height][Width];
	unsigned char NoisyImageDataG[Height][Width];
	unsigned char NoisyImageDataB[Height][Width];

	//Get PSNR Values
	double PSNR[3] = {0};
	double MSE[3] = {0};
	for(int k = 0; k < BytesPerPixel; k++) {
		for(int i = 0; i < Height; i++) {
			for(int j = 0; j < Width; j++) {
				if(k == 0)
					NoisyImageDataR[i][j] = NoisyImageData[i][j][k];
				if(k == 1)
					NoisyImageDataG[i][j] = NoisyImageData[i][j][k];
				if(k == 2)
					NoisyImageDataB[i][j] = NoisyImageData[i][j][k];

				int diff = NoisyImageData[i][j][k] - OriginalImageData[i][j][k];
				MSE[k] += pow(diff, 2);
			}
		}
		MSE[k] /= Height * Width;
		PSNR[k] = 10 * log10( pow(255, 2) / MSE[k]);
		cout << "Channel " << k << " PSNR:" << PSNR[k] << " MSE:" << MSE[k] << endl;
	}

	if(SPLIT_RGB){
		if (!(file=fopen("NoisyImageDataR.raw","wb"))) {
			cout << "Cannot open file: " << endl;
			exit(1);
		}
		fwrite(NoisyImageDataR, sizeof(unsigned char), Width*Height, file);
		fclose(file);

		if (!(file=fopen("NoisyImageDataG.raw","wb"))) {
			cout << "Cannot open file: " << endl;
			exit(1);
		}
		fwrite(NoisyImageDataG, sizeof(unsigned char), Width*Height, file);
		fclose(file);

		if (!(file=fopen("NoisyImageDataB.raw","wb"))) {
			cout << "Cannot open file: " << endl;
			exit(1);
		}
		fwrite(NoisyImageDataB, sizeof(unsigned char), Width*Height, file);
		fclose(file);	
	}

	//3x3 median filtering
	vector<int> med_filter;
	int Size = pow(MED_FILT_SIZE, 2);
	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int top = (i - 1) % Height;
				int bot = (i + 1) % Height;
				int left = (j - 1) % Width;
				int right = (j + 1) % Width;
				if(top < 0) top += Height;
				if(left < 0) left += Width;

				med_filter.push_back(NoisyImageData[top][left][k]);
				med_filter.push_back(NoisyImageData[top][j][k]);
				med_filter.push_back(NoisyImageData[top][right][k]);
				med_filter.push_back(NoisyImageData[i][left][k]);
				med_filter.push_back(NoisyImageData[i][j][k]);
				med_filter.push_back(NoisyImageData[i][right][k]);
				med_filter.push_back(NoisyImageData[bot][left][k]);
				med_filter.push_back(NoisyImageData[bot][j][k]);
				med_filter.push_back(NoisyImageData[bot][right][k]);
				sort(med_filter.begin(), med_filter.end());
				int med = med_filter[9/2];

				TargetImageData[i][j][k] = med;

				med_filter.clear();
			}
		}
	}

	//PSNR
	cout << "After 3x3 Median Filtering" << endl;
	for(int k = 0; k < BytesPerPixel; k++) {
		for(int i = 0; i < Height; i++) {
			for(int j = 0; j < Width; j++) {
				int diff = TargetImageData[i][j][k] - OriginalImageData[i][j][k];
				MSE[k] += pow(diff, 2);
			}
		}
		MSE[k] /= Height * Width;
		PSNR[k] = 10 * log10( pow(255, 2) / MSE[k]);
		cout << "Channel " << k << " PSNR:" << PSNR[k] << " MSE:" << MSE[k] << endl;
	}

	//Noise cleaning masking
	//        [1 2 1]
	//  1/16  [2 4 2]
	//        [1 2 1]
	int mask[3][3];
	mask[0][0] = 1;
	mask[0][1] = 2;
	mask[0][2] = 1;
	mask[1][0] = 2;
	mask[1][1] = 4;
	mask[1][2] = 2;
	mask[2][0] = 1;
	mask[2][1] = 2;
	mask[2][2] = 1;

	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			for(int k = 0; k < BytesPerPixel; k++){
				int top = (i - 1) % Height;
				int bot = (i + 1) % Height;
				int left = (j - 1) % Width;
				int right = (j + 1) % Width;
				if(top < 0) top += Height;
				if(left < 0) left += Width;

				int sum = 0;
				sum += TargetImageData[top][left][k] * mask[0][0];
				sum += TargetImageData[top][j][k] * mask[0][1];
				sum += TargetImageData[top][right][k] * mask[0][2];
				sum += TargetImageData[i][left][k] * mask[1][0];
				sum += TargetImageData[i][j][k] * mask[1][1];
				sum += TargetImageData[i][right][k] * mask[1][2];
				sum += TargetImageData[bot][left][k] * mask[2][0];
				sum += TargetImageData[bot][j][k] * mask[2][1];
				sum += TargetImageData[bot][right][k] * mask[2][2];
				sum /= 16;
				//cout << "Filtered value:" << sum << endl;
				TargetImageData2[i][j][k] = sum;
			}
			
		}
	}

	//PSNR
	cout << "After 3x3 Noise Cleaning Masking" << endl;
	for(int k = 0; k < BytesPerPixel; k++) {
		for(int i = 0; i < Height; i++) {
			for(int j = 0; j < Width; j++) {
				int diff = TargetImageData2[i][j][k] - OriginalImageData[i][j][k];
				MSE[k] += pow(diff, 2);
			}
		}
		MSE[k] /= Height * Width;
		PSNR[k] = 10 * log10( pow(255, 2) / MSE[k]);
		cout << "Channel " << k << " PSNR:" << PSNR[k] << " MSE:" << MSE[k] << endl;
	}


	// Write image data (filename specified by second argument) from image data matrix
	string toName(argv[3]);

	string fileName = toName + "cleaned.raw";
	if (!(file=fopen(fileName.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(TargetImageData, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	string fileName2 = toName + "cleaned2.raw";
	if (!(file=fopen(fileName2.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(TargetImageData2, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	return 0;
}
