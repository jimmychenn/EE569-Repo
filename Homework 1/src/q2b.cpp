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

class Point {
  public:
  	Point(int _x, int _y) { x = _x; y = _y; }
  	int getX() { return x;}
  	int getY() { return y;}
  private:
  	int x;
  	int y;
};

class LinStretch {
  public:
  	LinStretch(int, int, int, int);
  	int transform(int actual);
  private:
  	//desired
  	int d_min;
  	int d_max;
  	//actual
  	int a_max;
  	int a_min;
};

LinStretch::LinStretch(int _d_min, int _d_max, int _a_min, int _a_max)
		: d_min(_d_min), d_max(_d_max), a_min(_a_min), a_max(_a_max) {

}

int LinStretch::transform(int actual) {
	int desired = 0;
	double f = (double) (d_max - d_min)/ (double) (a_max - a_min);
	desired = d_min + f * (actual - a_min);
	return desired;
}

int main(int argc, char *argv[]) {
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel = 3;
	int Width = 256;
	int Height = 256;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [width = 256] [height = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 6){
			Width = atoi(argv[4]);
			Height = atoi(argv[5]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[Height][Width][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	
	unsigned char ImagedataA[Height][Width][BytesPerPixel];
	unsigned char ImagedataB[Height][Width][BytesPerPixel];

	typedef map<int, vector<Point> >::iterator it_type;
	vector<map<int, vector<Point> > > histRGB;

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

	int histogramRGB[256][3] = {0};
	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int pixel_value = (int) Imagedata[i][j][k];
				Point point = Point(i,j);
				histogramRGB[pixel_value][k]++;
				histRGB[k].find(pixel_value)->second.push_back(point);
			}
		}
	}

	//initialize variables to find actual min and max
	int hist_min[3] = {255, 255, 255};
	int hist_max[3] = {0};
	//specify desired variables
	int desired_min[3] = {0};
	int desired_max[3] = {255, 255, 255};
	for(int k = 0; k < BytesPerPixel; k++) {
		for(it_type it = histRGB[k].begin(); it != histRGB[k].end(); it++) {
			if(! it->second.empty()) {
				if(hist_min[k] > it->first) {
					hist_min[k] = it->first;
				}
				if(hist_max[k] < it->first) {
					hist_max[k] = it->first;
				}
			}
		}
		cout << k << ": Histogram min:" << hist_min[k] << " Histogram max:" << hist_max[k] << endl;
	}
	LinStretch linR(desired_min[0], desired_max[0], hist_min[0], hist_max[0]);
	LinStretch linG(desired_min[1], desired_max[1], hist_min[1], hist_max[1]);
	LinStretch linB(desired_min[2], desired_max[2], hist_min[2], hist_max[2]);
	vector<LinStretch> linRGB;
	linRGB.push_back(linR); linRGB.push_back(linG); linRGB.push_back(linB); 
	//Cumulative-probability-based histogram equalization method.
	//Bin equalization method

	//add 256 to ensure to get ceiling of division
	//using 170 works
	int bin_size = (Width * Height + 256) / 256;
	int bin_count[3] = {0};
	int bin_num[3] = {0};

	for(int k = 0; k < BytesPerPixel; k++) {
		for(it_type it = histRGB[k].begin(); it != histRGB[k].end(); it++) {
			for(int i = 0; i < it->second.size(); i++) {
				int x_ind = it->second[i].getX();
				int y_ind = it->second[i].getY();
				ImagedataA[x_ind][y_ind][k] = linRGB[k].transform(Imagedata[x_ind][y_ind][k]);
				ImagedataB[x_ind][y_ind][k] = bin_num[k];
				if(++bin_count[k] == bin_size){
					bin_count[k] = 0;
					bin_num[k]++;
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
	string toName(argv[2]);
	string fileTransfer = toName + "Transfer.raw";
	string fileCumulative = toName + "Cumulative.raw";

	if (!(file=fopen(fileTransfer.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataA, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);


	if (!(file=fopen(fileCumulative.c_str(),"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(ImagedataB, sizeof(unsigned char), Width*Height*BytesPerPixel, file);
	fclose(file);

	return 0;
}
