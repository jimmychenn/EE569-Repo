#ifndef MORPH_H
#define MORPH_H
#include "global.h"
#include "bond_masks.h"
#include <iostream>

int get_bond(filter);
bool first_stage_mask(filter, int);
bool getM(filter);

image_type create_M(image_type image) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	image_type M_matrix(boost::extents[height][width][1]);
	for(int i = 1; i < height - 1; i++) {
		for(int j = 1; j < width - 1; j++) {
			filter neighborhood(boost::extents[3][3]);
			for(int u = -1; u <= 1; u++) {
				for(int v = -1; v <= 1; v++) {
					neighborhood[u+1][v+1] = image[i+u][j+v][0]/255;
				}
			}
			if(getM(neighborhood)){
				M_matrix[i][j][0] = 0;				
			}
			else {
				M_matrix[i][j][0] = 255;				
			}
		}
	}
	return M_matrix;
}

bool getM(filter image_n) {
	int bond = get_bond(image_n);
	if(bond == 0) {
		//std::cout << " HELLO" << std::endl;
		return false;
	} else {
		//std::cout << " HI" << std::endl;
		return first_stage_mask(image_n, bond);
	}
}

int get_bond(filter image_n) {
	//should be a 3x3 pixel segment
	int bond = 0;
	if(image_n[1][1] == 1) {
		if(image_n[0][1] == 1)
			bond += 2;
		if(image_n[2][1] == 1)
			bond += 2;
		if(image_n[1][0] == 1)
			bond += 2;
		if(image_n[1][2] == 1)
			bond += 2;
		if(image_n[0][0] == 1)
			bond += 1;
		if(image_n[0][2] == 1)
			bond += 1;
		if(image_n[2][0] == 1)
			bond += 1;
		if(image_n[2][2] == 1)
			bond += 1;

		if(bond == 12)
			bond = 0;
	}
	return bond;
}

int get_bond(three_d_int image_n) {
	//should be a 3x3 pixel segment
	int bond = 0;
	if(image_n[1][1][0] == 1) {
		if(image_n[0][1][0] == 1)
			bond += 2;
		if(image_n[2][1][0] == 1)
			bond += 2;
		if(image_n[1][0][0] == 1)
			bond += 2;
		if(image_n[1][2][0] == 1)
			bond += 2;
		if(image_n[0][0][0] == 1)
			bond += 1;
		if(image_n[0][2][0] == 1)
			bond += 1;
		if(image_n[2][0][0] == 1)
			bond += 1;
		if(image_n[2][2][0] == 1)
			bond += 1;

		if(bond == 12)
			bond = 0;
	}
	return bond;
}

bool hit_or_miss_masking(filter image_n, three_d_int bond_mask) {
	for(int k = 0; k < bond_mask.shape()[2]; k++) {
		bool flag = true;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				//std::cout << "mask:" << bond_mask[i][j][k] << " image:" << image_n[i][j] << std::endl;
				if(bond_mask[i][j][k] == image_n[i][j])
					continue;
				else {
					//break out of both for loops
					flag = false;
					i = 3;
					j = 3;
				}
			}
		}
		if(flag) {
			return true;
		}
	}
	return false;
}

bool first_stage_mask(filter image_n, int bond) {
	if(bond == 1) {
		three_d_int bond_mask = get_bond_mask_1();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 2) {
		three_d_int bond_mask = get_bond_mask_2();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 3) {
		three_d_int bond_mask = get_bond_mask_3();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 4) {
		three_d_int bond_mask = get_bond_mask_stk4();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 5) {
		three_d_int bond_mask = get_bond_mask_s5();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 6) {
		three_d_int bond_mask = get_bond_mask_st6();
		if(hit_or_miss_masking(image_n, bond_mask))
			return hit_or_miss_masking(image_n, get_bond_mask_stk6());
	}
	if(bond == 7) {
		three_d_int bond_mask = get_bond_mask_stk7();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 8) {
		three_d_int bond_mask = get_bond_mask_stk8();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 9) {
		three_d_int bond_mask = get_bond_mask_stk9();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	if(bond == 10) {
		three_d_int bond_mask = get_bond_mask_stk10();
		return hit_or_miss_masking(image_n, bond_mask);
	}
	return true;
}





#endif