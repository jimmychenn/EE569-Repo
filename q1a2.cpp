// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the input image is of size 130 x 130 and is in the
//			RAW format.

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
	int Size = 130;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw" << endl;
		return 0;
	}
	
	// Allocate image data array
	unsigned char Imagedata[Size][Size][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	int cSize;
	cout << "Enter new dimension" << endl;
	cin >> cSize;
	printf("Dimensions: %d x %d\n", cSize, cSize);

	float delta = (float) Size / (float) cSize;

	unsigned char newImage[cSize][cSize][BytesPerPixel];
	for(int i = 0; i < cSize; i++) {
		for(int j = 0; j < cSize; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				float i_delta = delta * i;
				float j_delta = delta * j;
				int i_index = i_delta;
				int j_index = j_delta;
				i_delta -= i_index;
				j_delta -= j_index;
				int r_index = j_index + 1;
				int b_index = i_index + 1;

				if(r_index >= Size) r_index %= cSize;
				if(b_index >= Size) b_index %= cSize;

				/*
				cout << "i:" << i << " j:" << j << endl;
				cout << "i_delta:" << i_delta << " j_delta:" << j_delta << endl;
				cout << "i_index:" << i_index << " j_index:" << j_index << endl;
				cout << "r_index:" << r_index << " b_index:" << b_index << endl;
				*/

				int t_left = (1 - i_delta) * (1 - j_delta) * Imagedata[i_index][j_index][k];
				int t_right = (1 - i_delta) * j_delta * Imagedata[i_index][r_index][k];					
				int b_left = i_delta * (1 - j_delta) * Imagedata[b_index][j_index][k];
				int b_right = i_delta * j_delta * Imagedata[b_index][r_index][k];

				newImage[i][j][k] = t_left + t_right + b_left + b_right;
			}
		}
	}


	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(newImage, sizeof(unsigned char), cSize*cSize*BytesPerPixel, file);
	fclose(file);

	return 0;
}
