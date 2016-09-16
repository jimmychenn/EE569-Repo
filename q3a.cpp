// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
	int Width;
	int Height;
	
	// Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image_noisy.raw input_image_clean.raw output_image width height" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc == 5){
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

	unsigned char CleanImageData[Height][Width][BytesPerPixel];
	if(!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	read(CleanImageData, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char TargetImageData[Height][Width][BytesPerPixel];

	


	// Write image data (filename specified by second argument) from image data matrix
	String toName(argv[3]);
	toName += "cleaned.raw";
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(TargetImageData, sizeof(unsigned char), cWidth*cHeight*BytesPerPixel, file);
	fclose(file);

	return 0;
}
