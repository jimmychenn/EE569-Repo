#ifndef MORPH_H
#define MORPH_H
#include "global.h"
#include "bond_masks.h"
#include "uncond_masks.h"
#include <iostream>

int get_bond(filter);
bool first_stage_mask(filter, int);
bool getM(filter);
bool hit_or_miss_masking(filter, three_d_int);

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
			// std::cout << j << "," << i << std::endl;
			//print(neighborhood);
			if(getM(neighborhood)){
				// std::cout << "M is true" << std::endl;
				M_matrix[i][j][0] = 255;
			}
			else {
				// std::cout << "M is false" << std::endl;
				M_matrix[i][j][0] = 0;
			}
			// std::cout << (int) M_matrix[i][j][0] << std::endl;
			//std::cout << (int) image[i][j][0] << " ";
		}
		// std::cout << std::endl;
	}
	//std::cout << height << " " << width << std::endl;
	return M_matrix;
}
/*
filter create_binary_M(image_type image) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	filter M_matrix(boost::extents[height][width]);
	for(int i = 1; i < height - 1; i++) {
		for(int j = 1; j < width - 1; j++) {
			filter neighborhood(boost::extents[3][3]);
			for(int u = -1; u <= 1; u++) {
				for(int v = -1; v <= 1; v++) {
					neighborhood[u+1][v+1] = image[i+u][j+v][0]/255;
				}
			}
			if(getM(neighborhood)){
				M_matrix[i][j] = 0;
			}
			else {
				M_matrix[i][j] = 1;
			}
		}
	}
	return M_matrix;
}
*/
image_type shrink(image_type image, image_type M_matrix) {
	int height = image.shape()[0];
	int width = image.shape()[1];
	image_type image_morph(boost::extents[height][width][1]);
	//three_d_int uncond_masks = get_unconditional_masks();
	for(int i = 1; i < height - 1; i++) {
		for(int j = 1; j < width - 1; j++) {
			filter M_neighborhood(boost::extents[3][3]);
			three_d_int image_neighborhood(boost::extents[3][3][1]);
			if(M_matrix[i][j][0] == 255) {
				
				image_morph[i][j][0] = 0;

				/*
				//std::cout << j << "," << i << std::endl;
				for(int u = -1; u <= 1; u++) {
					for(int v = -1; v <= 1; v++) {
						M_neighborhood[u+1][v+1] = M_matrix[i+u][j+v][0]/255;
						image_neighborhood[u+1][v+1][0] = image[i+u][j+v][0]/255;
					}
				}
				std::cout << j << " " << i << std::endl;
				print(M_neighborhood);
				if(hit_or_miss_masking(M_neighborhood, image_neighborhood)) {
					image_morph[i][j][0] = 0;
					std::cout << "hit!" << std::endl;
				}
				else {
					image_morph[i][j][0] = image[i][j][0];
					std::cout << "miss!" << std::endl;
					//print(uncond_masks);
				}
				std::cout << std::endl;
				*/
			} else {
				image_morph[i][j][0] = image[i][j][0];
			}
		}
	}
	//print(M_matrix);
	return image_morph;
}

bool getM(filter image_n) {
	int bond = get_bond(image_n);
	if(bond == 0) {
		//std::cout << "Bond is 0 or 12" << std::endl;
		return false;
	} else {
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

		if(bond == 12) {
			bond = 0;
		}
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
		bool checkABC = false;
		bool ABC = false;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				//std::cout << "mask:" << bond_mask[i][j][k] << " image:" << image_n[i][j] << std::endl;
				if(bond_mask[i][j][k] == 2) { //2 = don't care
					//std::cout << "don't care" << std::endl;
					continue;
				}
				else if(bond_mask[i][j][k] == 3) {
					//std::cout << "ABC" << std::endl;
					checkABC = true;
					ABC |= image_n[i][j];
				}
				else if(bond_mask[i][j][k] == image_n[i][j])
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
			if(checkABC) {
				if(!ABC) {
					//std::cout << "ABC set to false" << std::endl;
					return false;
				}
			}
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