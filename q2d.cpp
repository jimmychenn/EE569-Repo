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
#include <random>

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
	int BytesPerPixel = 1;
	int Width;
	int Height;
	int PixelNum;
	
	// Check for proper syntax
	if (argc < 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image1.raw output_image width height" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color

	if (argc == 5) {
		Width = atoi(argv[3]);
		Height = atoi(argv[4]);
		PixelNum = Width * Height;
	}
	
	// Allocate image data array
	unsigned char originalImage[Height][Width][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(originalImage, sizeof(unsigned char), Width * Height * BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	unsigned char targetImage[Height][Width][BytesPerPixel];

	typedef map<int, vector<Point> >::iterator it_type;

	const int nrolls=PixelNum;  // number of experiments
	//const int nstars = PixelNum;    // maximum number of stars to distribute
	int gauss[256] = {0};
	default_random_engine generator;
	normal_distribution<double> distribution(125.0, 40.0);

	int min_index = 255;
	for(int i = 0; i < nrolls; i++) {
		double res = distribution(generator);
		if(res < 255.0 && res > 0.0){
			gauss[(int)res]++;
			if(res < min_index){
				min_index = res;
			}			
		}
	}
/*
	for(int i = 0; i < 256; i++) {
		cout << i << ":\t" << gauss[i] << endl;
	}
*/
	std::map<int, vector<Point> > hist;
	for(int i =0; i < 256; i++) {
		hist[i] = vector<Point>();
	}

	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			int val = (int) originalImage[i][j][0];
			hist[val].push_back(Point(i,j));
		}
	}

	int bin_count = 0;
	int bin_size = gauss[min_index];
	for(it_type it = hist.begin(); it != hist.end(); it++) {
		for(int i = 0; i < it->second.size(); i++) {
			int x_ind = it->second[i].getX();
			int y_ind = it->second[i].getY();
			targetImage[x_ind][y_ind][0] = min_index;
			if(++bin_count == bin_size){
				bin_count = 0;
				bin_size = gauss[++min_index];
			}
		}
	}

	
	//Bin method
/*
	for(int k = 0; k < BytesPerPixel; k++) {
		for(it_type it = histRGB[k].begin(); it != histRGB[k].end(); it++) {
			for(int i = 0; i < it->second.size(); i++) {
				int x_ind = it->second[i].getX();
				int y_ind = it->second[i].getY();
				targetImage[x_ind][y_ind][k] = start_index[k];
				if(++bin_count[k] == targetImageBinSizes[start_index[k]][k]){
					bin_count[k] = 0;
					start_index[k]++;
				}
			}
		}
	}
*/
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
	string toName(argv[2]);
	string fileName = toName + "mod.raw";


	if (!(file=fopen(fileName.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(targetImage, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	return 0;
}
