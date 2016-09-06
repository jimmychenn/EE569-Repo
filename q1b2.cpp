// This sample code reads in image data from a RAW image file and // writes it into another file// NOTE:	The code assumes that the image is of size 256 x 256 and is in the//			RAW format. You will need to make corresponding changes to//			accommodate images of different sizes and/or types#include <stdio.h>#include <iostream>#include <stdlib.h>#include <string>using namespace std;int max(int a, int b) {	if(a > b)		return a;	else		return b;}int min(int a, int b) {	if(a < b)		return a;	else		return b;}int main(int argc, char *argv[]){	// Define file pointer and variables	FILE *file;	int BytesPerPixel;	int Width = 256;	int Height = 256;		// Check for proper syntax	if (argc < 3){		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [width = 256] [height = 256]" << endl;		return 0;	}		// Check if image is grayscale or color	if (argc < 4){		BytesPerPixel = 1; // default is grey image	} 	else {		BytesPerPixel = atoi(argv[3]);		// Check if size is specified		if (argc >= 6){			Width = atoi(argv[4]);			Height = atoi(argv[5]);		}	}		// Allocate image data array	unsigned char Imagedata[Width][Height][BytesPerPixel];	// Read image (filename specified by first argument) into image data matrix	if (!(file=fopen(argv[1],"rb"))) {		cout << "Cannot open file: " << argv[1] <<endl;		exit(1);	}	fread(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);	fclose(file);	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////	unsigned char ImagedataH[Width][Height];	unsigned char ImagedataS[Width][Height];	unsigned char ImagedataL[Width][Height];	int H, S, L;	for(int i = 0; i < Width; i++) {		for(int j = 0; j < Height; j++) {			int M, m, C;			M = max(Imagedata[i][j][0], Imagedata[i][j][1]);			M = max(M, Imagedata[i][j][2]);			m = min(Imagedata[i][j][0], Imagedata[i][j][1]);			m = min(M, Imagedata[i][j][2]);			C = M - m;		}	}	// Write image data (filename specified by second argument) from image data matrix	string toName(argv[2]);	string fileM = toName + "H.raw";	string fileC = toName + "S.raw";	string fileY = toName + "L.raw";	if (!(file=fopen(fileC.c_str(),"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(ImagedataH, sizeof(unsigned char), Width*Height, file);	fclose(file);	if (!(file=fopen(fileM.c_str(),"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(ImagedataS, sizeof(unsigned char), Width*Height, file);	fclose(file);	if (!(file=fopen(fileY.c_str(),"wb"))) {		cout << "Cannot open file: " << argv[2] << endl;		exit(1);	}	fwrite(ImagedataL, sizeof(unsigned char), Width*Height, file);	fclose(file);	return 0;}