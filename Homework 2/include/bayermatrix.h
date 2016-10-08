#ifndef BAYERMATRIX_H
#define BAYERMATRIX_H
#include "global.h"

filter getI2() {
	filter I2(boost::extents[2][2]);
	I2[0][0] = 0; I2[0][1] = 2; I2[1][0] = 3; I2[1][1] = 1;
	return I2;
}

filter getT2() {
	filter T2(boost::extents[2][2]);
	T2[0][0] = 32; T2[0][1] = 159; T2[1][0] = 223; T2[1][1] = 96;
	return T2;
}

filter getT4() {
	filter T4(boost::extents[4][4]);
	T4[0][0] = 8;
	T4[0][1] = 135;
	T4[0][2] = 40;
	T4[0][3] = 167;
	T4[1][0] = 199;
	T4[1][1] = 72;
	T4[1][2] = 231;
	T4[1][3] = 104;
	T4[2][0] = 56;
	T4[2][1] = 183;
	T4[2][2] = 24;
	T4[2][3] = 151;
	T4[3][0] = 247;
	T4[3][1] = 120;
	T4[3][2] = 215;
	T4[3][3] = 88;
	return T4;
}

filter getA4() {
	filter A4(boost::extents[4][4]);
	A4[0][0] = 231;
	A4[0][1] = 167;
	A4[0][2] = 183;
	A4[0][3] = 247;
	A4[1][0] = 151;
	A4[1][1] = 56;
	A4[1][2] = 8;
	A4[1][3] = 72;
	A4[2][0] = 135;
	A4[2][1] = 40;
	A4[2][2] = 24;
	A4[2][3] = 88;
	A4[3][0] = 215;
	A4[3][1] = 120;
	A4[3][2] = 104;
	A4[3][3] = 199;
	return A4;
}

filter getT8() {
	filter T8(boost::extents[8][8]);
	T8[0][0] = 2;
	T8[0][1] = 129;
	T8[0][2] = 34;
	T8[0][3] = 161;
	T8[0][4] = 10;
	T8[0][5] = 137;
	T8[0][6] = 42;
	T8[0][7] = 169;
	T8[1][0] = 193;
	T8[1][1] = 66;
	T8[1][2] = 225;
	T8[1][3] = 98;
	T8[1][4] = 201;
	T8[1][5] = 74;
	T8[1][6] = 233;
	T8[1][7] = 106;
	T8[2][0] = 50;
	T8[2][1] = 177;
	T8[2][2] = 18;
	T8[2][3] = 145;
	T8[2][4] = 58;
	T8[2][5] = 185;
	T8[2][6] = 26;
	T8[2][7] = 153;
	T8[3][0] = 241;
	T8[3][1] = 114;
	T8[3][2] = 209;
	T8[3][3] = 82;
	T8[3][4] = 249;
	T8[3][5] = 122;
	T8[3][6] = 217;
	T8[3][7] = 90;
	T8[4][0] = 14;
	T8[4][1] = 141;
	T8[4][2] = 46;
	T8[4][3] = 173;
	T8[4][4] = 6;
	T8[4][5] = 133;
	T8[4][6] = 38;
	T8[4][7] = 165;
	T8[5][0] = 205;
	T8[5][1] = 78;
	T8[5][2] = 237;
	T8[5][3] = 10;
	T8[5][4] = 197;
	T8[5][5] = 70;
	T8[5][6] = 229;
	T8[5][7] = 102;
	T8[6][0] = 62;
	T8[6][1] = 189;
	T8[6][2] = 30;
	T8[6][3] = 157;
	T8[6][4] = 54;
	T8[6][5] = 181;
	T8[6][6] = 22;
	T8[6][7] = 149;
	T8[7][0] = 253;
	T8[7][1] = 126;
	T8[7][2] = 221;
	T8[7][3] = 94;
	T8[7][4] = 245;
	T8[7][5] = 118;
	T8[7][6] = 213;
	T8[7][7] = 86;
	return T8;
}

//for digital quarter toning
filter getT4_1() {
	filter T4(boost::extents[4][4]);
	T4[0][0] = 3;
	T4[0][1] = 45;
	T4[0][2] = 13;
	T4[0][3] = 56;
	T4[1][0] = 66;
	T4[1][1] = 24;
	T4[1][2] = 77;
	T4[1][3] = 35;
	T4[2][0] = 19;
	T4[2][1] = 61;
	T4[2][2] = 8;
	T4[2][3] = 50;
	T4[3][0] = 82;
	T4[3][1] = 40;
	T4[3][2] = 72;
	T4[3][3] = 29;
	return T4;
}

filter getT4_2() {
	filter T4(boost::extents[4][4]);
	T4[0][0] = 5;
	T4[0][1] = 90;
	T4[0][2] = 27;
	T4[0][3] = 112;
	T4[1][0] = 132;
	T4[1][1] = 48;
	T4[1][2] = 154;
	T4[1][3] = 69;
	T4[2][0] = 37;
	T4[2][1] = 122;
	T4[2][2] = 16;
	T4[2][3] = 101;
	T4[3][0] = 165;
	T4[3][1] = 80;
	T4[3][2] = 143;
	T4[3][3] = 58;
	return T4;
}

#endif