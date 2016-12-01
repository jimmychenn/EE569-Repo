#ifndef READRAW_H
#define READRAW_H
#include "global.h"

//does not support color images
Mat read(char* inFilename, int width, int height, int bytesperpixel) {
	FILE *file;
	unsigned char Imagedata[height][width][bytesperpixel];
	int sz[] = {height, width, bytesperpixel};
	Mat image(3, sz, CV_8U, Scalar::all(0));
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(inFilename,"rb"))) {
		std::cout << "Cannot open file: " << inFilename <<std::endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height*bytesperpixel, file);
	fclose(file);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytesperpixel; k++) {
				image.at<uchar>(i,j,k) = Imagedata[i][j][k];
			}
		}
	}
	return image;
}


void write(Mat image, char* outFilename) {
	FILE *file;
	int height = image.size[0];
	int width = image.size[1];
	int bytesperpixel = image.size[2];

	unsigned char Imagedata[height][width][bytesperpixel];

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytesperpixel; k++) {
				Imagedata[i][j][k] = image.at<uchar>(i,j,k);
			}
		}
	}
	// Write image data from image data matrix
	if (!(file=fopen(outFilename,"wb"))) {
		std::cout << "Cannot open file: " << outFilename << std::endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), width*height*bytesperpixel, file);
	fclose(file);
	std::cout << "Dimensions:" << width << "x" << height << std::endl;
}


void write_image(Mat image, char* name, const char* suffix) {
	char str[80];
	strcpy(str, name);
	strcat(str, suffix);
	write(image, str);
}


#endif