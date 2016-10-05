#ifndef SOLUTIONS_H
#define SOLUTIONS_H
#include "global.h"
#include "userio.h"

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

image_type solutionq1b(image_type pieceImage) {
	int pHeight = pieceImage.shape()[0]; int pWidth = pieceImage.shape()[1];
	int oHeight = 512; int oWidth = 512;

	int find_piece_start;
	int find_piece_end;

	Point center;
	double angle;
	Point fill_start;
	Point fill_end;
	double scale_factor_y;
	double scale_factor_x;
	Point downscale_start;
	Point downscale_end;
	Point piece_start;
	Point piece_end;

	image_type Hillary = read(HILLARY_FILE, oHeight, oWidth, BytesPerPixel);
	image_type Trump = read(TRUMP_FILE, oHeight, oWidth, BytesPerPixel);

	int userin = userInput();
	if(userin == 1 ) {
		find_piece_start = 0;
		find_piece_end = pWidth/2;
		angle = 15/180.0 * M_PI;
		center.x = 149;
		center.y = 149;
		fill_start.y = 79;
		fill_start.x = 74;
		fill_end.y = 218;
		fill_end.x = 224;
		scale_factor_x = 0.676;
		scale_factor_y = 0.730;
		downscale_start.y = 80;
		downscale_start.x = 75;
		downscale_end.y = 217;
		downscale_end.x = 223;
		piece_start.y = 58;
		piece_start.x = 50;
		piece_end.y = 158;
		piece_end.x = 150;
	} else if(userin == 2) {
		find_piece_start = pWidth/2;
		find_piece_end = pWidth;
		angle = -4.57/180.0 * M_PI;
		center.x = 342;
		center.y = 330;
		fill_start.y = 294;
		fill_start.x = 306;
		fill_end.y = 366;
		fill_end.x = 378;
		piece_start.y = 0;
		piece_start.x = 0;
		piece_end.y = 100;
		piece_end.x = 100;
	}





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
	int y_min = pieceImage.shape()[0];
	Point topCorner;
	int y_max = 0;
	Point botCorner;
	int x_min = pieceImage.shape()[1];
	Point leftCorner;
	int x_max = 0;
	Point rightCorner;
	for(int i = find_piece_start; i < find_piece_end; i++) {
		for(int j = 0; j < pWidth; j++) {
			for(int k = 0; k < pieceImage.shape()[2]; k++) {
				int pixel_value = pieceImage[i][j][k];
				if(pixel_value != 255) {
					if(userin == 1) {
						if(i < y_min) {
							y_min = i;
							topCorner.y = i;
							topCorner.x = j;
						}
						if(i >= y_max) {
							y_max = i;
							botCorner.y = i;
							botCorner.x = j;
						}
						if(j <= x_min) {
							x_min = j;
							leftCorner.y = i;
							leftCorner.x = j;
						}
						if(j > x_max) {
							x_max = j;
							rightCorner.y = i;
							rightCorner.x = j;
						}
					} else if(userin == 2) {
						if(i <= y_min) {
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
						if(j >= x_max) {
							x_max = j;
							rightCorner.y = i;
							rightCorner.x = j;
						}
					}
				}
			}
		}
	}
	
	std::cout << "topCorner:" << topCorner.x << " " << topCorner.y << std::endl;
	std::cout << "botCorner:" << botCorner.x << " " << botCorner.y << std::endl;
	std::cout << "leftCorner:" << leftCorner.x << " " << leftCorner.y << std::endl;
	std::cout << "rightCorner:" << rightCorner.x << " " << rightCorner.y << std::endl << std::endl;

	std::cout << "x_min:" << x_min << std::endl;
	std::cout << "y_min" << y_min << std::endl;
	std::cout << "x_max:" << x_max << std::endl;
	std::cout << "y_max"<< y_max << std::endl << std::endl;
	
	//center point of rotated piece

	image_type image_test(boost::extents[pieceImage.shape()[0]][pieceImage.shape()[1]][pieceImage.shape()[2]]);
	//rotation of image
	//angle value found by trial and error
	for(int y = y_min; y < y_max; y++) {
		for(int x = x_min; x < x_max; x++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				if(pieceImage[y][x][k] != 255) {
					//std::cout << x << " " << y << std::endl;
					double x_new = x - center.x;
					double y_new = y - center.y;
					x_new = cos(angle) * x_new + sin(angle) * y_new;
					y_new = -sin(angle) * x_new + cos(angle) * y_new;
					x_new = x_new + center.x;
					y_new = y_new + center.y;
					//std::cout << x_new << " " << y_new << std::endl;
					image_test[y_new][x_new][k] = pieceImage[y][x][k];
				}
			}
		}
	}

	//some black dots appear in the image. Fill in
	for(int y = fill_start.y; y < fill_end.y; y++) {
		for(int x = fill_start.x; x < fill_end.x; x++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				if(image_test[y][x][k] == 0) {
					image_test[y][x][k] = image_test[y-1][x-1][k];
				}
			}
		}
	}

	image_type image_test2(boost::extents[pHeight][pWidth][BytesPerPixel]);
	//for Trump picture rotate another 90 degrees
	if(userin == 2) {
		for(int y = fill_start.y; y < fill_end.y; y++) {
			for(int x = fill_start.x; x < fill_end.x; x++) {
				for(int k = 0; k < BytesPerPixel; k++) {
					if(image_test[y][x][k] != 0) {
						int x_ind = fill_end.x - y + fill_start.y;
						int y_ind = fill_start.y + x - fill_start.x;
						image_test2[y_ind][x_ind][k] = image_test[y][x][k];
					}
				}
			}
		}
		for(int y = fill_start.y; y < fill_end.y + 1; y++) {
			for(int x = fill_start.x; x < fill_end.x + 1; x++) {
				for(int k = 0; k < BytesPerPixel; k++) {
					if(image_test[y][x][k] != 0) {
						image_test2[y-fill_start.y][x-fill_start.x][k] = image_test2[y][x][k];
					}
				}
			}
		}
	}
//	write(image_test2, "PieceOutBefore.raw");

	image_type image_test3(boost::extents[pHeight][pWidth][BytesPerPixel]);
	//Rescaling of image piece
	if(userin == 1) {
		for(int y = downscale_start.y; y < downscale_end.y; y++) {
			for(int x = downscale_start.x; x < downscale_end.x; x++) {
				for(int k = 0; k < BytesPerPixel; k++) {
					if(image_test2[y][x][k] != 255){
						double x_new = x * scale_factor_x;
						double y_new = y * scale_factor_y;
						image_test2[y_new][x_new][k] = image_test[y][x][k];
					}
				}
			}
		}
	} else if(userin == 2) {
		int Size = 72;
		int cSize = 100;
		float delta = (float) Size / (float) cSize;

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

					if(r_index >= Size) r_index %= Size;
					if(b_index >= Size) b_index %= Size;

					
					// std::cout << "i:" << i << " j:" << j << std::endl;
					// std::cout << "i_delta:" << i_delta << " j_delta:" << j_delta << std::endl;
					// std::cout << "i_index:" << i_index << " j_index:" << j_index << std::endl;
					// std::cout << "r_index:" << r_index << " b_index:" << b_index << std::endl;
					

					int t_left = (1 - i_delta) * (1 - j_delta) * image_test2[i_index][j_index][k];
					int t_right = (1 - i_delta) * j_delta * image_test2[i_index][r_index][k];					
					int b_left = i_delta * (1 - j_delta) * image_test2[b_index][j_index][k];
					int b_right = i_delta * j_delta * image_test2[b_index][r_index][k];

					image_test3[i][j][k] = t_left + t_right + b_left + b_right;
				}
			}
		}
	}
		
	//write(image_test3, "PieceOutAfter.raw");

	
	



	//finding the corners of the missing piece in the original image (guaranteed square)
	y_min = oHeight;
	y_max = 0;
	x_min = oWidth;
	x_max = 0;
	int pixel_value;
	for(int i = 0; i < oHeight; i++) {
		for(int j = 0; j < oWidth; j++) {
			if(userin == 1)
				pixel_value = Hillary[i][j][0] + Hillary[i][j][1] + Hillary[i][j][2];
			else if(userin == 2)
				pixel_value = Trump[i][j][0] + Trump[i][j][1] + Trump[i][j][2];
			if(pixel_value == 765) {
				//top left
				if(i < y_min) {
					y_min = i;
					topCorner.y = i;
					topCorner.x = j;
				}
				//bottom left
				if(j <= x_min) {
					x_min = j;
					leftCorner.y = i;
					leftCorner.x = j;
				}
				//bottom right
				if(i >= y_max) {
					y_max = i;
					botCorner.y = i;
					botCorner.x = j;
				}
				//top right
				if(j > x_max) {
					x_max = j;
					rightCorner.y = i;
					rightCorner.x = j;
				}
			}
		}
	}
	
	std::cout << "topleftCorner:" << topCorner.x << " " << topCorner.y << std::endl;
	std::cout << "toprightCorner:" << rightCorner.x << " " << rightCorner.y << std::endl;
	std::cout << "bottomleftCorner:" << leftCorner.x << " " << leftCorner.y << std::endl;
	std::cout << "bottomrightCorner:" << botCorner.x << " " << botCorner.y << std::endl << std::endl;

	int xdiff = topCorner.x - piece_start.x;
	int ydiff = topCorner.y - piece_start.y;
	//Replacing the missing piece with the transformed piece
	for(int i = piece_start.y; i < piece_end.y; i++) {
		for(int j = piece_start.x; j < piece_end.x; j++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				int i_ind = i + ydiff;
				int j_ind = j + xdiff;
				if(userin == 1)
					Hillary[i_ind][j_ind][k] = image_test2[i][j][k];
				else if(userin == 2)
					Trump[i_ind][j_ind][k] = image_test3[i][j][k];
			}
		}
	}
	if(userin == 1)
		return Hillary;
	else if(userin == 2)
		return Trump;
}

#endif