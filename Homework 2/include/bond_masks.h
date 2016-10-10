#ifndef BOND_MASKS_H
#define BOND_MASKS_H
#include <iostream>

//Bond = 1
three_d_int get_bond_mask_1(){
	three_d_int s1(boost::extents[3][3][4]);
	for(int k = 0; k < s1.shape()[2]; k++) {
		s1[1][1][k] = 1;
	}
	s1[0][2][0] = 1;
	s1[0][0][1] = 1;
	s1[2][0][2] = 1;
	s1[0][2][3] = 1;

	return s1;
}

three_d_int get_bond_mask_2() {
	three_d_int s2(boost::extents[3][3][4]);
	for(int k = 0; k < s2.shape()[2]; k++)
		s2[1][1][k] = 1;

	s2[1][2][0] = 1;
	s2[0][1][1] = 1;
	s2[1][0][2] = 1;
	s2[2][1][3] = 1;

	return s2;
}

three_d_int get_bond_mask_3() {
	three_d_int s3(boost::extents[3][3][8]);
	for(int k = 0; k < s3.shape()[2]; k++)
		s3[1][1][k] = 1;

	s3[0][2][0] = 1;
	s3[1][2][0] = 1;

	s3[0][1][1] = 1;
	s3[0][2][1] = 1;

	s3[0][0][2] = 1;
	s3[0][1][2] = 1;

	s3[0][0][3] = 1;
	s3[1][0][3] = 1;

	s3[1][0][4] = 1;
	s3[2][0][4] = 1;

	s3[2][0][5] = 1;
	s3[2][1][5] = 1;

	s3[2][1][6] = 1;
	s3[2][2][6] = 1;

	s3[1][2][7] = 1;
	s3[2][2][7] = 1;

	return s3;
}

three_d_int get_bond_mask_tk4() {
	three_d_int tk4(boost::extents[3][3][4]);
	for(int k = 0; k < tk4.shape()[2]; k++)
		tk4[1][1][k] = 1;

	tk4[0][1][0] = 1;
	tk4[1][2][0] = 1;
	tk4[1][0][1] = 1;
	tk4[0][1][1] = 1;
	tk4[1][0][2] = 1;
	tk4[2][1][2] = 1;
	tk4[1][2][3] = 1;
	tk4[2][1][3] = 1;

	return tk4;
}

three_d_int get_bond_mask_stk4() {
	three_d_int stk4(boost::extents[3][3][4]);
	for(int k = 0; k < stk4.shape()[2]; k++)
		stk4[1][1][k] = 1;

	stk4[0][2][0] = 1;
	stk4[1][2][0] = 1;
	stk4[2][2][0] = 1;
	stk4[0][0][1] = 1;
	stk4[0][1][1] = 1;
	stk4[0][2][1] = 1;
	stk4[0][0][2] = 1;
	stk4[1][0][2] = 1;
	stk4[2][0][2] = 1;
	stk4[2][0][3] = 1;
	stk4[2][1][3] = 1;
	stk4[2][2][3] = 1;

	return stk4;
}

three_d_int get_bond_mask_s5() {
	three_d_int st5(boost::extents[3][3][8]);
	for(int k = 0; k < st5.shape()[2]; k++)
		st5[1][1][k] = 1;

	st5[0][0][0] = 1;
	st5[0][1][0] = 1;
	st5[1][2][0] = 1;
	st5[0][1][1] = 1;
	st5[1][2][1] = 1;
	st5[2][2][1] = 1;
	st5[1][0][2] = 1;
	st5[0][1][2] = 1;
	st5[0][2][2] = 1;
	st5[0][2][3] = 1;
	st5[1][2][3] = 1;
	st5[2][1][3] = 1;
	st5[0][1][4] = 1;
	st5[0][2][4] = 1;
	st5[1][2][4] = 1;
	st5[0][0][5] = 1;
	st5[0][1][5] = 1;
	st5[1][0][5] = 1;
	st5[1][0][6] = 1;
	st5[2][0][6] = 1;
	st5[2][1][6] = 1;
	st5[2][1][7] = 1;
	st5[2][2][7] = 1;
	st5[1][2][7] = 1;
	return st5;
}

three_d_int get_bond_mask_st6() {
	three_d_int st6(boost::extents[3][3][2]);
	for(int k = 0; k < st6.shape()[2]; k++)
		st6[1][1][k] = 1;

	st6[0][0][0] = 1;
	st6[0][1][0] = 1;
	st6[1][2][0] = 1;
	st6[2][2][0] = 1;
	st6[0][1][1] = 1;
	st6[0][2][1] = 1;
	st6[1][0][1] = 1;
	st6[2][0][1] = 1;

	return st6;
}

three_d_int get_bond_mask_stk6() {
	three_d_int stk6(boost::extents[3][3][8]);
	for(int k = 0; k < stk6.shape()[2]; k++)
		stk6[1][1][k] = 1;

	stk6[0][0][0] = 1;
	stk6[0][1][0] = 1;
	stk6[0][2][0] = 1;
	stk6[1][2][0] = 1;
	stk6[0][1][1] = 1;
	stk6[0][2][1] = 1;
	stk6[1][2][1] = 1;
	stk6[2][2][1] = 1;
	stk6[0][0][2] = 1;
	stk6[0][1][2] = 1;
	stk6[0][2][2] = 1;
	stk6[1][0][2] = 1;
	stk6[0][0][3] = 1;
	stk6[0][1][3] = 1;
	stk6[1][0][3] = 1;
	stk6[2][0][3] = 1;
	stk6[0][0][4] = 1;
	stk6[1][0][4] = 1;
	stk6[2][0][4] = 1;
	stk6[2][1][4] = 1;
	stk6[1][0][5] = 1;
	stk6[2][0][5] = 1;
	stk6[2][1][5] = 1;
	stk6[2][2][5] = 1;
	stk6[2][0][6] = 1;
	stk6[2][1][6] = 1;
	stk6[2][2][6] = 1;
	stk6[1][2][6] = 1;
	stk6[0][2][7] = 1;
	stk6[1][2][7] = 1;
	stk6[2][1][7] = 1;
	stk6[2][2][7] = 1;
	return stk6;
}

three_d_int get_bond_mask_stk7() {
	three_d_int stk7(boost::extents[3][3][4]);
	for(int k = 0; k < stk7.shape()[2]; k++)
		stk7[1][1][k] = 1;

	stk7[0][0][0] = 1;
	stk7[0][1][0] = 1;
	stk7[0][2][0] = 1;
	stk7[1][2][0] = 1;
	stk7[2][2][0] = 1;
	stk7[0][0][1] = 1;
	stk7[0][1][1] = 1;
	stk7[0][2][1] = 1;
	stk7[1][0][1] = 1;
	stk7[2][0][1] = 1;
	stk7[0][0][2] = 1;
	stk7[1][0][2] = 1;
	stk7[2][0][2] = 1;
	stk7[2][1][2] = 1;
	stk7[2][2][2] = 1;
	stk7[2][0][3] = 1;
	stk7[2][1][3] = 1;
	stk7[2][2][3] = 1;
	stk7[1][2][3] = 1;
	stk7[0][2][3] = 1;

	return stk7;
}

three_d_int get_bond_mask_stk8() {
	three_d_int stk8(boost::extents[3][3][4]);
	for(int k = 0; k < stk8.shape()[2]; k++)
		stk8[1][1][k] = 1;

	stk8[0][1][0] = 1;
	stk8[0][2][0] = 1;
	stk8[1][2][0] = 1;
	stk8[2][2][0] = 1;
	stk8[2][1][0] = 1;
	stk8[0][0][1] = 1;
	stk8[0][1][1] = 1;
	stk8[0][2][1] = 1;
	stk8[1][0][1] = 1;
	stk8[1][2][1] = 1;
	stk8[0][0][2] = 1;
	stk8[1][0][2] = 1;
	stk8[2][0][2] = 1;
	stk8[0][1][2] = 1;
	stk8[2][1][2] = 1;
	stk8[1][0][3] = 1;
	stk8[2][0][3] = 1;
	stk8[2][1][3] = 1;
	stk8[2][2][3] = 1;
	stk8[1][2][3] = 1;

	return stk8;
}

three_d_int get_bond_mask_stk9() {
	three_d_int stk9(boost::extents[3][3][8]);
	for(int k = 0; k < stk9.shape()[2]; k++)
		for(int i = 0; i < stk9.shape()[1]; i++)
			for(int j = 0; j < stk9.shape()[0]; j++)
				stk9[i][j][k] = 1;

	stk9[1][0][0] = 0;
	stk9[2][0][0] = 0;
	stk9[0][0][1] = 0;
	stk9[1][0][1] = 0;
	stk9[2][1][2] = 0;
	stk9[2][2][2] = 0;
	stk9[2][0][3] = 0;
	stk9[2][1][3] = 0;
	stk9[1][2][4] = 0;
	stk9[2][2][4] = 0;
	stk9[0][2][5] = 0;
	stk9[1][2][5] = 0;
	stk9[0][1][6] = 0;
	stk9[0][2][6] = 0;
	stk9[0][0][7] = 0;
	stk9[0][1][7] = 0;

	return stk9;
}

three_d_int get_bond_mask_stk10() {
	three_d_int stk10(boost::extents[3][3][4]);
	for(int k = 0; k < stk10.shape()[2]; k++)
		for(int i = 0; i < stk10.shape()[1]; i++)
			for(int j = 0; j < stk10.shape()[0]; j++)
				stk10[i][j][k] = 1;

	stk10[1][0][0] = 0;
	stk10[2][1][1] = 0;
	stk10[1][2][2] = 0;
	stk10[0][1][3] = 0;

	return stk10;
}

three_d_int get_bond_mask_k11() {
	three_d_int k11(boost::extents[3][3][4]);
	for(int k = 0; k < k11.shape()[2]; k++)
		for(int i = 0; i < k11.shape()[1]; i++)
			for(int j = 0; j < k11.shape()[0]; j++)
				k11[i][j][k] = 1;

	k11[2][0][0] = 0;
	k11[2][2][1] = 0;
	k11[0][2][2] = 0;
	k11[0][0][3] = 0;

	return k11;
}

//for testing purposes
void print(three_d_int mask) {
	for(int k = 0; k < mask.shape()[2]; k++) {
		std::cout << k << std::endl;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				std::cout << mask[i][j][k] << " ";
			}
			std::cout << std::endl;
		}
		three_d_int mask_temp = mask;
		std::cout << std::endl;
	}
}

void print(image_type image) {
	for(int i = 0; i < image.shape()[0]; i++) {
		for(int j = 0; j < image.shape()[1]; j++) {
			for(int k = 0; k < image.shape()[2]; k++) {
				std::cout << (int) image[i][j][k] << " ";
			}
		}
		std::cout << std::endl;
	}
}

void print(filter filt) {
	for(int i = 0; i < filt.shape()[0]; i++) {
		for(int j = 0; j < filt.shape()[1]; j++) {
			std::cout << filt[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#endif