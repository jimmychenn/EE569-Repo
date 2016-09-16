// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>

using namespace std;

int P_RANGE = 256;

class Point {
  public:
  	Point(int _x, int _y) { x = _x; y = _y; }
  	int getX() { return x;}
  	int getY() { return y;}
  private:
  	int x;
  	int y;
};

int main(int argc, char *argv[]) {	
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
	int WidthOriginal;
	int HeightOriginal;
	int PixelNumOriginal;
	int WidthTarget;
	int HeightTarget;
	int PixelNumTarget;
	
	// Check for proper syntax
	if (argc < 8){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image1.raw input_image2.raw output_image width1 height1 width2 height2" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color

	if (argc == 8) {
		WidthOriginal = atoi(argv[4]);
		HeightOriginal = atoi(argv[5]);
		PixelNumOriginal = WidthOriginal * HeightOriginal;
		WidthTarget = atoi(argv[6]);
		HeightTarget = atoi(argv[7]);
		PixelNumTarget = WidthTarget * HeightTarget;
	}
	
	// Allocate image data array
	unsigned char originalImage[HeightOriginal][WidthOriginal][BytesPerPixel];
	unsigned char targetImage[HeightTarget][WidthTarget][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(originalImage, sizeof(unsigned char), WidthOriginal * HeightOriginal * BytesPerPixel, file);
	fclose(file);

	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(targetImage, sizeof(unsigned char), WidthTarget * HeightTarget * BytesPerPixel,file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char targetImageModified[HeightTarget][WidthTarget][BytesPerPixel];

	typedef map<int, vector<Point> >::iterator it_type;
	vector<map<int, vector<Point> > > histRGB;

	//for target image
	std::map<int, vector<Point> > histR;
	std::map<int, vector<Point> > histG;
	std::map<int, vector<Point> > histB;
	for(int i =0; i < 256; i++) {
		histR[i] = vector<Point>();
		histG[i] = vector<Point>();
		histB[i] = vector<Point>();		
	}
	histRGB.push_back(histR);
	histRGB.push_back(histG);
	histRGB.push_back(histB);

	//for original image
	int targetImageBinSizes[256][3] = {0};
	for(int i = 0; i < HeightOriginal; i++) {
		for(int j = 0; j < WidthOriginal; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int pixel_value = (int) originalImage[i][j][k];
				targetImageBinSizes[pixel_value][k]++;
			}
		}
	}

	int start_index[3] = {255, 255, 255};

	for(int k = 0; k <BytesPerPixel; k++) {
		for(int i = 0; i < 256; i++) {
			double f = (double) (targetImageBinSizes[i][k] + 1) / (double) PixelNumOriginal;
			targetImageBinSizes[i][k] = f * PixelNumTarget;
			if(targetImageBinSizes[i][k] != 0) {
				if(i < start_index[k])
					start_index[k] = i;
			}
			//cout << i << ":\t" << targetImageBinSizes[i][k] << endl;
		}
		//cout << start_index[k] << endl;
	}

	for(int i = 0; i < HeightTarget; i++) {
		for(int j = 0; j < WidthTarget; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int pixel_value = (int) targetImage[i][j][k];
				histRGB[k].find(pixel_value)->second.push_back(Point(i,j));
			}
		}
	}
	
	//Bin method
	int bin_count[3] = {0};

	for(int k = 0; k < BytesPerPixel; k++) {
		for(it_type it = histRGB[k].begin(); it != histRGB[k].end(); it++) {
			for(int i = 0; i < it->second.size(); i++) {
				int x_ind = it->second[i].getX();
				int y_ind = it->second[i].getY();
				targetImageModified[x_ind][y_ind][k] = start_index[k];
				if(++bin_count[k] == targetImageBinSizes[start_index[k]][k]){
					bin_count[k] = 0;
					start_index[k]++;
				}
			}
		}
	}


/*
	typedef map<int, vector<Point> >::iterator it_type;
	for(it_type it = hist.begin(); it != hist.end(); it++){
		cout << it->first << ": ";
		for(int i = 0; i < it->second.size(); i++){
			cout << it->second[i].getX() << "," << it->second[i].getY() << "\t";
		}
		cout << endl;
	}
*/


	/*
	for(int i = 0; i < 256; i++) {
		for(int j = 0; j < BytesPerPixel; j++) {
			cout << histogramRGB[i][j] << '\t';
		}
		cout << endl;
	}
	*/




	// Write image data (filename specified by second argument) from image data matrix
	string toName(argv[3]);
	string fileName = toName + "mod.raw";


	if (!(file=fopen(fileName.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(targetImageModified, sizeof(unsigned char), WidthTarget*HeightTarget*BytesPerPixel, file);
	fclose(file);

	return 0;
}
