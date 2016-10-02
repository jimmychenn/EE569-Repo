#ifndef SOLUTIONS_H
#define SOLUTIONS_H
#include "global.h"

class Point {
  public:
  	Point(){ x = 0; y = 0;};
  	Point(int _x, int _y) { x = _x; y = _y; }
  	int x;
  	int y;
};

image_type solutionq1a(image_type image) {
	image_type imageMod(boost::extents[Width][Height][BytesPerPixel]);
	for(int y = 0; y < Height; y++) {
		for(int x = 0; x < Width; x++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int x_new;
				int y_new;
				if(y <= Height/2) {
					if(x <= y){
						x_new = x - 0.5 * y + 75;
						y_new = 0.5 * y + 75;
					} else if(x <= Width/2) {
						x_new = x * 0.5 + 75;
						y_new = y - x * 0.5 + 75;
					} else if(x <= Width - y) {
						x_new = 0.5 * x + 75;
						y_new = 0.5 * x + y - 75;
					} else if(x <= Width) {
						x_new = x + y/2 - 75;
						y_new = 0.5 * y + 75;
					}
				} else if( y < Height) {
					if(x <= Width/2 - y + Height/2) {
						x_new = x + 0.5 * y - 75;
						y_new = 0.5 * y + 75;
					} else if(x < Width/2) {
						x_new = 0.5 * x + 75;
						y_new = 0.5 * x + y - 75;
					} else if(x <= y) {
						x_new = 0.5 * x + 75;
						y_new = y - 0.5 * x + 75;
					} else if(x <= Width) {
						x_new = x - y/2 + 75;
						y_new = 0.5 * y + 75;
					}
				}
				imageMod[y_new][x_new][k] = image[y][x][k];
			}
		}
	}
	return imageMod;
}

image_type solutionq1b(image_type image) {
	
	int pHeight = 500; int pWidth = 500;
	image_type pieceImage = read(piece_image_file, pHeight, pWidth, BytesPerPixel);
	image_type imageMod(boost::extents[pWidth][pHeight][BytesPerPixel]);

	/*
	if(Hillary) {
		for loop from 0 to pHeight/2
		angle = 15
		scale x = 0.69
		scale y = 0.6666
		pixel_value == 255
		i_ind = start at 43
		j_ind = start at 57
	}
	*/

	//finding the corners of the piece image
	int y_min = pHeight;
	Point topCorner;
	int y_max = 0;
	Point botCorner;
	int x_min = pWidth;
	Point leftCorner;
	int x_max = 0;
	Point rightCorner;
	for(int i = 0; i < pHeight/2; i++) {
		for(int j = 0; j < pWidth; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int pixel_value = pieceImage[i][j][k];
				if(pixel_value != 255) {
					if(i < y_min) {
						y_min = i;
						topCorner.y = i;
						topCorner.x = j;
					}
					if(i > y_max) {
						y_max = i;
						botCorner.y = i;
						botCorner.x = j;
					}
					if(j < x_min) {
						x_min = j;
						leftCorner.y = i;
						leftCorner.x = j;
					}
					if(j > x_max) {
						x_max = j;
						rightCorner.y = i;
						rightCorner.x = j;
					}
				}
			}
		}
	}
	
	std::cout << "leftCorner:" << leftCorner.x << " " << leftCorner.y << std::endl;
	std::cout << "topCorner:" << topCorner.x << " " << topCorner.y << std::endl;
	std::cout << "botCorner:" << botCorner.x << " " << botCorner.y << std::endl;
	std::cout << "rightCorner:" << rightCorner.x << " " << rightCorner.y << std::endl << std::endl;
	
	std::cout << "x_min:" << x_min << std::endl;
	std::cout << "x_max:" << x_max << std::endl;
	std::cout << "y_min:" << y_min << std::endl;
	std::cout << "y_max:" << y_max << std::endl;

	//rotation of image
	//angle value found by trial and error
	double angle = -30/180.0 * M_PI;
	for(int y = y_min; y < y_max; y++) {
		for(int x = x_min; x < x_max; x++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				//std::cout << x << " " << y << std::endl;
				double x_new = x - x_max/2;
				double y_new = y - y_max/2;
				x_new = cos(angle) * x_new - sin(angle) * y_new;
				y_new = sin(angle) * x_new + cos(angle) * y_new;
				x_new = x_new + x_max/2;
				y_new = y_new + y_max/2;
				//std::cout << x_new << " " << y_new << std::endl;
				if(x_new > 0 && y_new > 0)
					imageMod[y][x][k] = pieceImage[y_new][x_new][k];
			}
		}
	}
	//write(imageMod, "trumpOut.raw", 500, 500);

	//Down-scaling of image piece
	image_type image2(boost::extents[Width][Height][BytesPerPixel]);
	for(int y = y_min; y < y_max; y++) {
		for(int x = x_min; x < x_max; x++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				if(imageMod[y][x][k] != 255){
					//std::cout << x << " " << y << std::endl;
					double x_new = x * 0.69;
					double y_new = y * 0.6666;
					//std::cout << x_new << " " << y_new << std::endl;
					image2[y_new][x_new][k] = imageMod[y][x][k];
				}
			}
		}
	}
	

	//finding the corners of the missing piece in the original image
	y_min = Height;
	y_max = 0;
	x_min = Width;
	x_max = 0;
	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			int pixel_value = image[i][j][0] + image[i][j][1] + image[i][j][2];
			if(pixel_value == 0) {
				if(i < y_min) {
					y_min = i;
					topCorner.y = i;
					topCorner.x = j;
				}
				else if(i >= y_max) {
					y_max = i;
					botCorner.y = i;
					botCorner.x = j;
				}
				if(j <= x_min) {
					x_min = j;
					leftCorner.y = i;
					leftCorner.x = j;
				}
				else if(j > x_max) {
					x_max = j;
					rightCorner.y = i;
					rightCorner.x = j;
				}
			}
		}
	}
	
	std::cout << "leftCorner:" << leftCorner.x << " " << leftCorner.y << std::endl;
	std::cout << "topCorner:" << topCorner.x << " " << topCorner.y << std::endl;
	std::cout << "botCorner:" << botCorner.x << " " << botCorner.y << std::endl;
	std::cout << "rightCorner:" << rightCorner.x << " " << rightCorner.y << std::endl << std::endl;
	

	//Replacing the missing piece with the transformed piece
	for(int i = y_min; i < y_max+1; i++) {
		for(int j = x_min; j < x_max+1; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int i_ind = 43 + i - y_min;
				int j_ind = 57 + j - x_min;
				image[i][j][k] = image2[i_ind][j_ind][k];
			}
		}
	}

	return image;
}

#endif