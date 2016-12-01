#include "readraw.h"
#include "global.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
	if(argc < 2) {
		std::cout << "Please include a valid picture file in command line" << std::endl;
		return 1;
	}
	char* image_file = argv[1];
	int width = 481;
	int height = 321;
	int bytes = 3;
    //Mat image = read(image_file, width, height, bytes);
    Mat image(height, width, CV_8UC3);

	FILE *file;
	unsigned char Imagedata[height][width][bytes];
	if (!(file=fopen(image_file,"rb"))) {
		std::cout << "Cannot open file: " << image_file <<std::endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), width*height*bytes, file);
	fclose(file);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			for(int k = 0; k < bytes; k++) {
				//RGB to BGR
				int to_k = 1;
				if(k == 2) to_k = 0;
				if(k == 0) to_k = 2;
				image.at<Vec3b>(i,j)[to_k] = Imagedata[i][j][k];
			}
		}
	}

	// imshow("original image", image);

	Mat gray_image, edges, edges_image;
	cvtColor(image, gray_image, CV_BGR2GRAY);


	for(int low_threshold = 50; low_threshold <= 250; low_threshold += 50) {
		for(int high_threshhold = low_threshold + 100; high_threshhold <= low_threshold + 250; high_threshhold += 50) {

			Canny( gray_image, edges, low_threshold, high_threshhold, 3, true);
			edges.convertTo(edges_image, CV_8U);
			// namedWindow("image", CV_WINDOW_AUTOSIZE);
			// imshow("image", edges_image);

			uchar edgesImagedata[height][width];
			for(int i = 0; i < height; i++) {
				for(int j = 0; j < width; j++) {
					edgesImagedata[i][j] = edges_image.at<uchar>(i,j);
				}
			}


			std::stringstream ss;
			string str1(image_file);
			string str(str1.begin() + str1.find_last_of("/") + 1, str1.begin() + str1.find("."));
			ss.str("");
			ss << str << "_out";
			ss << low_threshold << "_" << high_threshhold << ".raw";
			const char* name = ss.str().c_str();


			if (!(file=fopen(name,"wb"))) {
				std::cout << "Cannot open file: " << name << std::endl;
				exit(1);
			}
			fwrite(edgesImagedata, sizeof(unsigned char), width*height, file);
			fclose(file);


		}
	}
	

	//waitKey(0);
/*	src1 = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow( "Original image", CV_WINDOW_AUTOSIZE );
	imshow( "Original image", src1 );
 
	Mat gray, edge, draw;
	cvtColor(src1, gray, CV_BGR2GRAY);
 
	Canny( gray, edge, 50, 150, 3);
 
	edge.convertTo(draw, CV_8U);
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", draw);
 
	waitKey(0);  
	*/
    return 0;
} 