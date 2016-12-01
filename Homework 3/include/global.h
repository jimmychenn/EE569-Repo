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
