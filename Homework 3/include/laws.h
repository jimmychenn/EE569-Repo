#ifndef LAWS_H
#define LAWS_H
#include "global.h"
#include <vector>

class Laws{
  public:
  	Laws();
  	vector<Mat> filts;

  private:
  	//1D 5x5 Laws Filter kernels
  	Mat L5;
  	Mat E5;
  	Mat S5;
  	Mat W5;
  	Mat R5;

  	//2D 5x5 Laws Filter kernels
   	Mat LL5;
 	Mat LE5;
  	Mat LS5;
  	Mat LW5;
  	Mat LR5;
  	Mat EL5;
  	Mat EE5;
  	Mat ES5;
  	Mat EW5;
  	Mat ER5;
  	Mat SL5;
  	Mat SE5;
  	Mat SS5;
  	Mat SW5;
  	Mat SR5;
  	Mat WL5;
  	Mat WE5;
  	Mat WS5;
  	Mat WW5;
  	Mat WR5;
  	Mat RL5;
  	Mat RE5;
  	Mat RS5;
  	Mat RW5;
  	Mat RR5;
};

Laws::Laws() {
	L5.create(1,5, CV_64FC1);
	L5.at<double>(0,0) = 1;
	L5.at<double>(0,1) = 4;
	L5.at<double>(0,2) = 6;
	L5.at<double>(0,3) = 4;
	L5.at<double>(0,4) = 1;

	E5.create(1,5, CV_64FC1);
	E5.at<double>(0,0) = -1;
	E5.at<double>(0,1) = -2;
	E5.at<double>(0,2) = 0;
	E5.at<double>(0,3) = 2;
	E5.at<double>(0,4) = 1;

	S5.create(1,5, CV_64FC1);
	S5.at<double>(0,0) = -1;
	S5.at<double>(0,1) = 0;
	S5.at<double>(0,2) = 2;
	S5.at<double>(0,3) = 0;
	S5.at<double>(0,4) = -1;

	W5.create(1,5, CV_64FC1);
	W5.at<double>(0,0) = -1;
	W5.at<double>(0,1) = 2;
	W5.at<double>(0,2) = 0;
	W5.at<double>(0,3) = -2;
	W5.at<double>(0,4) = 1;

	R5.create(1,5, CV_64FC1);
	R5.at<double>(0,0) = 1;
	R5.at<double>(0,1) = -4;
	R5.at<double>(0,2) = 6;
	R5.at<double>(0,3) = -4;
	R5.at<double>(0,4) = 1;

	LL5 = L5.t()*L5;
	LE5 = L5.t()*E5;
	LS5 = L5.t()*S5;
	LW5 = L5.t()*W5;
	LR5 = L5.t()*R5;

	EL5 = E5.t()*L5;
	EE5 = E5.t()*E5;
	ES5 = E5.t()*S5;
	EW5 = E5.t()*W5;
	ER5 = E5.t()*R5;

	SL5 = S5.t()*L5;
	SE5 = S5.t()*E5;
	SS5 = S5.t()*S5;
	SW5 = S5.t()*W5;
	SR5 = S5.t()*R5;

	WL5 = W5.t()*L5;
	WE5 = W5.t()*E5;
	WS5 = W5.t()*S5;
	WW5 = W5.t()*W5;
	WR5 = W5.t()*R5;

	RL5 = R5.t()*L5;
	RE5 = R5.t()*E5;
	RS5 = R5.t()*S5;
	RW5 = R5.t()*W5;
	RR5 = R5.t()*R5;

	filts.push_back(LL5);
	filts.push_back(LE5);
	filts.push_back(LS5);
	filts.push_back(LW5);
	filts.push_back(LR5);
	
	filts.push_back(EL5);
	filts.push_back(EE5);
	filts.push_back(ES5);
	filts.push_back(EW5);
	filts.push_back(ER5);

	filts.push_back(SL5);
	filts.push_back(SE5);
	filts.push_back(SS5);
	filts.push_back(SW5);
	filts.push_back(SR5);

	filts.push_back(WL5);
	filts.push_back(WE5);
	filts.push_back(WS5);
	filts.push_back(WW5);
	filts.push_back(WR5);

	filts.push_back(RL5);
	filts.push_back(RE5);
	filts.push_back(RS5);
	filts.push_back(RW5);
	filts.push_back(RR5);
}


#endif