#ifndef ERRORDIFFUSION_H
#define ERRORDIFFUSION_H
#include "global.h"

double_filter getFloydSteinberg() {
	double_filter FS(boost::extents[3][3]);
	FS[0][0] = 0;
	FS[0][1] = 0;
	FS[0][2] = 0;
	FS[1][0] = 0;
	FS[1][1] = 0;
	FS[1][2] = 0.4375;
	FS[2][0] = 0.1875;
	FS[2][1] = 0.3125;
	FS[2][2] = 0.0625;
	return FS;
}

double_filter getJJN() {
	double_filter JJN(boost::extents[5][5]);
	JJN[0][0] = 0;
	JJN[0][1] = 0;
	JJN[0][2] = 0;
	JJN[0][3] = 0;
	JJN[0][4] = 0;
	JJN[1][0] = 0;
	JJN[1][1] = 0;
	JJN[1][2] = 0;
	JJN[1][3] = 0;
	JJN[1][4] = 0;
	JJN[2][0] = 0;
	JJN[2][1] = 0;
	JJN[2][2] = 0;
	JJN[2][3] = 0.14583333;
	JJN[2][4] = 0.10416666;
	JJN[3][0] = 0.0625;
	JJN[3][1] = 0.10416666;
	JJN[3][2] = 0.14583333;
	JJN[3][3] = 0.10416666;
	JJN[3][4] = 0.0625;
	JJN[4][0] = 0.02083333;
	JJN[4][1] = 0.0625;
	JJN[4][2] = 0.10416666;
	JJN[4][3] = 0.0625;
	JJN[4][4] = 0.02083333;
	return JJN;
}

double_filter getStucki() {
	double_filter Stucki(boost::extents[5][5]);
	Stucki[0][0] = 0;
	Stucki[0][1] = 0;
	Stucki[0][2] = 0;
	Stucki[0][3] = 0;
	Stucki[0][4] = 0;
	Stucki[1][0] = 0;
	Stucki[1][1] = 0;
	Stucki[1][2] = 0;
	Stucki[1][3] = 0;
	Stucki[1][4] = 0;
	Stucki[2][0] = 0;
	Stucki[2][1] = 0;
	Stucki[2][2] = 0;
	Stucki[2][3] = 8.0 / 42.0;
	Stucki[2][4] = 4.0 / 42.0;
	Stucki[3][0] = 2.0 / 42.0;
	Stucki[3][1] = 4.0 / 42.0;
	Stucki[3][2] = 8.0 / 42.0;
	Stucki[3][3] = 4.0 / 42.0;
	Stucki[3][4] = 2.0 / 42.0;
	Stucki[4][0] = 1.0 / 42.0;
	Stucki[4][1] = 2.0 / 42.0;
	Stucki[4][2] = 4.0 / 42.0;
	Stucki[4][3] = 2.0 / 42.0;
	Stucki[4][4] = 1.0 / 42.0;
	return Stucki;
}

#endif