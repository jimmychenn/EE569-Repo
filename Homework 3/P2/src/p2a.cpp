#include "global.h"
#include "opencv2/nonfree/features2d.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Please include a valid picture file in command line" << endl;
		return 1;
	}

	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat image_gray = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	//write(image, "output.raw");
	vector<Mat> image_channels(3); //BGR
	split(image, image_channels);

	SIFT SIFT_detector;
	std::vector<KeyPoint> keypointsB_SIFT, keypointsG_SIFT, keypointsR_SIFT;
	std::vector<KeyPoint> keypointsGRAY_SIFT;
	SIFT_detector.detect(image_channels[0], keypointsB_SIFT);
	SIFT_detector.detect(image_channels[1], keypointsG_SIFT);
	SIFT_detector.detect(image_channels[2], keypointsR_SIFT);
	SIFT_detector.detect(image_gray, keypointsGRAY_SIFT);

	Mat image_keypoints_B;
	Mat image_keypoints_G;
	Mat image_keypoints_R;
	Mat image_keypoints_GRAY;

	drawKeypoints( image_channels[0], keypointsB_SIFT, image_keypoints_B, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( image_channels[1], keypointsG_SIFT, image_keypoints_G, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( image_channels[2], keypointsR_SIFT, image_keypoints_R, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( image_gray, keypointsGRAY_SIFT, image_keypoints_GRAY, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

	//-- Show detected (drawn) keypoints
	imshow("Keypoints B SIFT", image_keypoints_B );
	imshow("Keypoints G SIFT", image_keypoints_G );
	imshow("Keypoints R SIFT", image_keypoints_R );
	imshow("Keypoints GRAY SIFT", image_keypoints_GRAY);

	imwrite("SIFT_b.jpg", image_keypoints_B);
	imwrite("SIFT_g.jpg", image_keypoints_G);
	imwrite("SIFT_r.jpg", image_keypoints_R);
	imwrite("SIFT_gray.jpg", image_keypoints_GRAY);


	SURF SURF_detector;
	std::vector<KeyPoint> keypointsB_SURF, keypointsG_SURF, keypointsR_SURF;
	std::vector<KeyPoint> keypointsGRAY_SURF;
	SURF_detector.detect(image_channels[0], keypointsB_SURF);
	SURF_detector.detect(image_channels[1], keypointsG_SURF);
	SURF_detector.detect(image_channels[2], keypointsR_SURF);
	SURF_detector.detect(image_gray, keypointsGRAY_SURF);

	Mat image_keypoints_B_SURF;
	Mat image_keypoints_G_SURF;
	Mat image_keypoints_R_SURF;
	Mat image_keypoints_GRAY_SURF;

	drawKeypoints( image_channels[0], keypointsB_SURF, image_keypoints_B_SURF, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( image_channels[1], keypointsG_SURF, image_keypoints_G_SURF, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( image_channels[2], keypointsR_SURF, image_keypoints_R_SURF, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
	drawKeypoints( image_gray, keypointsGRAY_SURF, image_keypoints_GRAY_SURF, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

	imshow("Keypoints B SURF", image_keypoints_B_SURF );
	imshow("Keypoints G SURF", image_keypoints_G_SURF );
	imshow("Keypoints R SURF", image_keypoints_R_SURF );
	imshow("Keypoints GRAY SURF", image_keypoints_GRAY_SURF );

	imwrite("SURF_b.jpg", image_keypoints_B_SURF);
	imwrite("SURF_g.jpg", image_keypoints_G_SURF);
	imwrite("SURF_r.jpg", image_keypoints_R_SURF);
	imwrite("SURF_gray.jpg", image_keypoints_GRAY_SURF);

	waitKey(0);

	return 0;
}

#ifndef GLOBAL_H
#define GLOBAL_H
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace cv;

char P1A_IN1[] = "P1/res/Texture1.raw";
char P1A_IN2[] = "P1/res/Texture2.raw";
char P1A_IN3[] = "P1/res/Texture3.raw";
char P1A_IN4[] = "P1/res/Texture4.raw";
char P1A_IN5[] = "P1/res/Texture5.raw";
char P1A_IN6[] = "P1/res/Texture6.raw";
char P1A_IN7[] = "P1/res/Texture7.raw";
char P1A_IN8[] = "P1/res/Texture8.raw";
char P1A_IN9[] = "P1/res/Texture9.raw";
char P1A_IN10[] = "P1/res/Texture10.raw";
char P1A_IN11[] = "P1/res/Texture11.raw";
char P1A_IN12[] = "P1/res/Texture12.raw";

char P1B_IN1[] = "P1/res/comb_1.raw";
char P1B_IN2[] = "P1/res/comb_2.raw";

char P2A_IN1[] = "P2/res/jeep.jpg";
char P2A_IN2[] = "P2/res/bus.jpg";
char P2B_IN1[] = "P2/res/rav4_1.jpg";
char P2B_IN2[] = "P2/res/rav4_2.jpg";

char P3A_IN1[] = "P3/res/zebra.raw";

class Global {
  public:
  	Global();
  	char P1A_IN1[19];
  	char P1A_IN2[19];
  	char P1A_IN3[19];
  	char P1A_IN4[19];
  	char P1A_IN5[19];
  	char P1A_IN6[19];
  	char P1A_IN7[19];
  	char P1A_IN8[19];
  	char P1A_IN9[19];
  	char P1A_IN10[20];
  	char P1A_IN11[20];
  	char P1A_IN12[20];
  	//char* P1A_IN_ar[12];
  	char P1A_OUT;
	char P1B_OUT;
	char P1C_OUT;
	char P2A_OUT;
	char P2B_OUT;
	char P3A_OUT;
};

Global::Global() {
	//In file names

	char P1A_IN1[] = "P1/res/Texture1.raw";
  	char P1A_IN2[] = "P1/res/Texture2.raw";
  	char P1A_IN3[] = "P1/res/Texture3.raw";
  	char P1A_IN4[] = "P1/res/Texture4.raw";
  	char P1A_IN5[] = "P1/res/Texture5.raw";
  	char P1A_IN6[] = "P1/res/Texture6.raw";
  	char P1A_IN7[] = "P1/res/Texture7.raw";
  	char P1A_IN8[] = "P1/res/Texture8.raw";
  	char P1A_IN9[] = "P1/res/Texture9.raw";
  	char P1A_IN10[] = "P1/res/Texture10.raw";
  	char P1A_IN11[] = "P1/res/Texture11.raw";
  	char P1A_IN12[] = "P1/res/Texture12.raw";

	/*
	char P1A_IN[] = "P1/res/Texture";

	for(int i = 1; i <= 12; i++) {
		char str[20];
		strcpy(str, P1A_IN);
		if(i <= 9) {
			char num[2];
			num[0] = '0' + i;
			num[1] = '\0';
			strcat(str, num);
		} else {
			char num[3];
			num[0] = '1';
			num[1] = '0' + i-10;
			num[2] = '\0';
			strcat(str, num);
		}
		char raw_suff[] = ".raw";
		strcat(str, raw_suff);
		strcpy(P1A_IN_ar[i-1], str);
		std::cout << P1A_IN_ar[i-1] << std::endl;
	}
	*/

	//Out file names
	char P1A_OUT[] = "P1/out/P1A_out";
	char P1B_OUT[] = "P1/out/P1B_out";
	char P1C_OUT[] = "P1/out/P1C_out";
	char P2A_OUT[] = "P2/out/P2A_out";
	char P2B_OUT[] = "P2/out/P2B_out";
	char P3A_OUT[] = "P3/out/P3A_out_";

}

#endif
