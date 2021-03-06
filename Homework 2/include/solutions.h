#ifndef SOLUTIONS_H
#define SOLUTIONS_H
#include "global.h"
#include "userio.h"
#include "helper.h"
#include "errordiffusion.h"
#include "morph.h"
#include "con_com_label.h"

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

void solutionq1b(image_type pieceImage) {
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

	int userin = userInputq1b();
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

	/*
	std::cout << "x_min:" << x_min << std::endl;
	std::cout << "y_min" << y_min << std::endl;
	std::cout << "x_max:" << x_max << std::endl;
	std::cout << "y_max"<< y_max << std::endl << std::endl;
	*/
	//center point of rotated piece

	image_type image_test(boost::extents[pieceImage.shape()[0]][pieceImage.shape()[1]][pieceImage.shape()[2]]);
	//rotation of image
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

	//some black dots may appear in the image. Fill in
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
		for(int y = fill_start.y - 1; y < fill_end.y + 2; y++) {
			for(int x = fill_start.x - 1; x < fill_end.x + 1; x++) {
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
	if(userin == 1) {
		write_image(Hillary, P1B_OUT, "Hillary.raw");
	}
	else if(userin == 2) {
		write_image(Trump, P1B_OUT, "Trump.raw");
	}

}



void solutionq1c(image_type image) {
	image_type tartansImage = read(TARTANS_FILE, 350, 146, 3);
	image_type trojansImage = read(TROJANS_FILE, 350, 146, 3);
	double h11 = 1.7361;
	double h12 = 0.9251;
	double h13 = 334.8499;
	double h21 = 0.4462;
	double h22 = -0.1740;
  	double h23 = 594.5630;
	double h31 = 0.0022;
	double h32 = -0.0006;

	image_type h_image(boost::extents[image.shape()[0]][image.shape()[1]][image.shape()[2]]);

	int userin = userInputq1c();

	Point topleft(20,24);
	Point topright(330,24);
	Point botleft(20,140);
	Point botright(330,140);
	for(int y = topleft.y; y < botright.y; y++) {
		for(int x = topleft.x; x < botright.x; x++) {
			for(int k = 0; k < BytesPerPixel; k++) {
				double x_temp = h11*x + h12*y + h13;
				double y_temp = h21*x + h22*y + h23;
				double w = h31*x + h32*y + 1;
				int x_ind = (double)x_temp/(double)w;
				int y_ind = (double)y_temp/(double)w;

				// std::cout << "x:" << x << " " << "y:" << y << std::endl;
				// std::cout << "x_temp:" << x_temp << " " << "y_temp:" << y_temp << " " << "w:" << w << std::endl;
				// std::cout << "x_ind:" << x_ind << " " << "y_ind:" << y_ind << std::endl;
				if(userin == 1){
					if(tartansImage[y][x][k] > 10)
						//image[y_ind][x_ind][k] = tartansImage[y][x][k];
						h_image[y_ind][x_ind][k] = tartansImage[y][x][k];
				}
				else if(userin == 2){
					if(trojansImage[y][x][k] < 245)
						//image[y_ind][x_ind][k] = trojansImage[y][x][k];
						h_image[y_ind][x_ind][k] = trojansImage[y][x][k];
				}

			}
		}
	}

	h_image = median_filter(h_image);	
	for(int y = 0; y < h_image.shape()[0]; y++) {
		for(int x = 0; x < h_image.shape()[1]; x++) {
			for(int k = 0; k < h_image.shape()[2]; k++) {
				if(h_image[y][x][k] != 0) {
					image[y][x][k] = h_image[y][x][k];
				}
			}
		}
	}
	if(userin == 1)
		write_image(image, P1C_OUT, "TartansField.raw");
	else if(userin == 2)
		write_image(image, P1C_OUT, "TrojansField.raw");

}

void solutionq2a(image_type image) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	int bytesperpixel = image.shape()[2];

	filter T2 = getT2();
	image_type imageI2 = dither(image, T2);
	write_image(imageI2, P2A_OUT, "I2.raw");

	filter T8 = getT8();
	image_type imageI8 = dither(image, T8);
	write_image(imageI8, P2A_OUT, "I8.raw");

	filter T4 = getT4();
	image_type imageI4 = dither(image, T4);
	write_image(imageI4, P2A_OUT, "I4.raw");

	filter A4 = getA4();
	image_type imageA4 = dither(image, A4);
	write_image(imageA4, P2A_OUT, "A4.raw");

	//quarter toning
	filter T4_1 = getT4_1();
	filter T4_2 = getT4_2();

	//Create a 3 dimensional filter that divides the matrix Bayer identity value into 3 parts.
	for(int y = 0; y < image.shape()[0]; y++) {
		for(int x = 0; x < image.shape()[1]; x++) {
			for(int k = 0; k < image.shape()[2]; k++) {
				int f_y = y%T4.shape()[0];
				int f_x = x%T4.shape()[1];
				int p = image[y][x][k];
				if(p > T4[f_y][f_x]) {
					image[y][x][k] = 255;
				} else if(p > T4_2[f_y][f_x]) {
					image[y][x][k] = 170;
				} else if(p > T4_1[f_y][f_x]) {
					image[y][x][k] = 85;
				} else {
					image[y][x][k] = 0;
				}
			}
		}
	}

	write_image(image, P2A_OUT, "I4_Quarter.raw");
}

void solutionq2b(image_type image) {
	double_image_type double_image = unsigned_char_image_to_double(image);
	double_image_type FS_double_image = floyd_steinberg(double_image);

	image_type FS_image = double_image_to_unsigned_char(FS_double_image);
	write_image(FS_image, P2B_OUT, "FloydSteinberg.raw");

	double_image_type JJN_double_image = error_diffusion(double_image, getJJN());
	image_type JJN_image = double_image_to_unsigned_char(JJN_double_image);
	write_image(JJN_image, P2B_OUT, "JJN.raw");

	double_image_type Stucki_double_image = error_diffusion(double_image, getStucki());
	image_type Stucki_image = double_image_to_unsigned_char(Stucki_double_image);
	write_image(Stucki_image, P2B_OUT, "Stucki.raw");
}

void solutionq3a(image_type image) {

	image_type gray_image = to_grayscale(image);
	write_image(gray_image, P3A_OUT, "grayscale_rice.raw");

	image_type binarized_image = binarize(gray_image, GLOBAL_MEAN_THRESHOLD);
	write_image(binarized_image, P3A_OUT, "binarized_rice.raw");

	binarized_image = median_filter(binarized_image);
	write_image(binarized_image, P3A_OUT, "binarized_filtered_rice.raw");

	binarized_image = median_filter(binarized_image);
	binarized_image = median_filter(binarized_image);
	binarized_image = median_filter(binarized_image);
	binarized_image = median_filter(binarized_image);
	write_image(binarized_image,P3A_OUT, "binarized_filtered_five_rice.raw");

	image_type M_matrix = create_M(binarized_image);
	write_image(M_matrix, P3A_OUT, "binarized_filtered_rice_Mmatrix.raw");

	con_com_label labels(binarized_image);
	std::cout << "Number of objects:" << labels.getNumOfObjects() << std::endl;

	std::map<int,int> object_to_sizes = labels.getSizes();
	std::map<int,int> sizes_to_object;
	for(std::map<int,int>::iterator it = object_to_sizes.begin(); it != object_to_sizes.end(); it++) {
		sizes_to_object[it->second] = it->first;
	}
	for(std::map<int,int>::iterator it = sizes_to_object.begin(); it != sizes_to_object.end(); it++) {
		std::cout << "Size: " << it->first << " Object num:" << it->second << std::endl;
	}
/*
	image_type thinned_image = shrink(binarized_image, M_matrix);
	strcpy(name, "thinned_rice1.raw");
	write(thinned_image, name);
	memset(name, 0, sizeof name);

	image_type first_seed_image(boost::extents[48][33][1]);
	for(int i = 18; i < 66; i++) {
		for(int j = 58; j < 91; j++) {
			first_seed_image[i-18][j-58][0] = binarized_image[i][j][0];
			std::cout << (int) binarized_image[i][j][0] << " ";
		}
		std::cout << std::endl;
	}

	write(first_seed_image, "seed_test_image.raw");

	
	for(int i = 0; i < 10; i++) {
		thinned_image = shrink(thinned_image, create_M(thinned_image));
	}
	strcpy(name, "thinned_rice13.raw");
	write(thinned_image, name);
	memset(name, 0, sizeof name);
*/
}

#endif