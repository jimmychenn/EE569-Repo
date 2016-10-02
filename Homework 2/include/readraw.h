#ifndef READRAW_H
#define READRAW_H

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "boost/multi_array.hpp"
#include "global.h"

bool checkArgs(int argc, char* argv[]) {
	// Check for proper syntax
	if (argc != 6){
		std::cout << "Syntax Error - Incorrect Parameter Usage:" << std::endl;
		std::cout << "program_name input_image.raw output_image.raw BytesPerPixel Width Height" << std::endl;
		return false;
	}

	BytesPerPixel = atoi(argv[3]);
	Width = atoi(argv[4]);
	Height = atoi(argv[5]);

	return true;
}

image_type read(char* inFilename) {
	FILE *file;
	unsigned char Imagedata[Width][Height][BytesPerPixel];
	image_type image(boost::extents[Width][Height][BytesPerPixel]);
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(inFilename,"rb"))) {
		std::cout << "Cannot open file: " << inFilename <<std::endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	for(int i = 0; i < Width; i++) {
		for(int j = 0; j < Height; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				image[i][j][k] = Imagedata[i][j][k];
			}
		}
	}
	return image;
}

image_type read(char* inFilename, int height, int width, int bytesperpixel) {
	FILE *file;
	unsigned char Imagedata[width][height][bytesperpixel];
	image_type image(boost::extents[width][height][bytesperpixel]);
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(inFilename,"rb"))) {
		std::cout << "Cannot open file: " << inFilename <<std::endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height*bytesperpixel, file);
	fclose(file);

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			for(int k = 0; k < bytesperpixel; k++) {
				image[i][j][k] = Imagedata[i][j][k];
			}
		}
	}
	return image;
}

void write(image_type image, char* outFilename) {
	FILE *file;
	unsigned char Imagedata[Width][Height][BytesPerPixel];

	for(int i = 0; i < Width; i++) {
		for(int j = 0; j < Height; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				Imagedata[i][j][k] = image[i][j][k];
			}
		}
	}
	//funcImagedata = func((unsigned char**) Imagedata, Width, Height, BytesPerPixel);
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(outFilename,"wb"))) {
		std::cout << "Cannot open file: " << outFilename << std::endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);
}

void write(image_type image, char* outFilename, int height, int width) {
	FILE *file;
	unsigned char Imagedata[width][height][BytesPerPixel];

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				Imagedata[i][j][k] = image[i][j][k];
			}
		}
	}
	//funcImagedata = func((unsigned char**) Imagedata, width, height, BytesPerPixel);
	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(outFilename,"wb"))) {
		std::cout << "Cannot open file: " << outFilename << std::endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
	fclose(file);
}

#endif