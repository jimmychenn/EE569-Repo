#ifndef CON_COM_LABEL_H
#define CON_COM_LABEL_H
#include "global.h"
#include "bond_masks.h"
#include <map>
#include <vector>


class con_com_label {
  public:
  	con_com_label(image_type image);
  	int getNumOfObjects() { return numOfObjects;}
  	filter getLabelMatrix() { return label_matrix;}
  	void printMap();
  	std::map<int,int> getSizes() { return label_sizes;}

  private:
  	image_type _image;
  	filter label_matrix;
  	std::map<int,int> label_equivalence;
  	std::map<int,int> label_totals;
  	std::map<int,int> label_sizes;

  	int numOfObjects;
  	int label_num;
  	int image_height;
  	int image_width;
  	int bytes;

  	void initialize(image_type image);
  	void label(image_type image);
  	void count();
  	bool newLabel(int x, int y);
  	int getLowestLabel(int x, int y);
  	std::map<int,int> getMap(image_type) { return label_equivalence;};
};
// Connected Component Labelling algorithm


con_com_label::con_com_label(image_type image) {
	initialize(image);
	label(image);
	count();

}

void con_com_label::count() {
	int count = 0;
	int sum = 0;
	int curr_label;
	for(std::map<int,int>::iterator it = label_equivalence.begin(); it != label_equivalence.end(); it++) {
		if(it->first == it->second) {
			sum = label_totals[it->first];
			curr_label = count+1;
			label_sizes[curr_label] = sum;
			count++;			
		} else{
			sum += label_totals[it->first];
			label_sizes[curr_label] = sum;
		}
	}
	numOfObjects = count;
}

void con_com_label::printMap() {
	for(std::map<int,int>::iterator it = label_equivalence.begin(); it != label_equivalence.end(); it++) {
		// std::cout << "Label: " << it->first << " equivalent to:" << it->second << std::endl;
	}
	// std::cout << std::endl;
	for(std::map<int,int>::iterator it = label_totals.begin(); it != label_totals.end(); it++) {
		// std::cout << "Label: " << it->first << " has this many occurences:" << it->second << std::endl;
	}
	for(std::map<int,int>::iterator it = label_sizes.begin(); it != label_sizes.end(); it++) {
		// std::cout << "Object number: " << it->first << " is of this size:" << it->second << std::endl;
	}
}


void con_com_label::initialize(image_type image){
	image_height = image.shape()[0];
	image_width = image.shape()[1];
	bytes = image.shape()[2];
	label_num = 1;
	_image.resize(boost::extents[image_height][image_width][1]);
	_image = image;
	label_matrix.resize(boost::extents[image_height][image_width]);
	for(int i = 0; i < image_height; i++) {
		for(int j = 0; j < image_width; j++) {
				label_matrix[i][j] = -1;
		}
	}
	// print(label_matrix);
}

void con_com_label::label(image_type image) {
	for(int i = 0; i < image_height; i++) {
		for(int j = 0; j < image_width; j++) {
			if(image[i][j][0] != 0) {
				// std::cout << j << " " << i << std::endl;
				// std::cout << "Before:" << label_matrix[i][j];
				if(newLabel(j,i)) {
					label_matrix[i][j] = label_num;
					label_equivalence[label_num] = label_num;
					label_totals[label_num] = 1;
					label_num++;
				} else {
					label_matrix[i][j] = getLowestLabel(j,i);
					label_totals.find(label_matrix[i][j])->second++;
				}
				// std::cout << " After:" << label_matrix[i][j] << std::endl;
			}
		}
	}
}

bool con_com_label::newLabel(int x, int y) {
	if(x != 0 && y != 0 && x != image_width - 1 && y != image_height - 1) {
		if(_image[y-1][x][0] == 0 && _image[y-1][x-1][0] == 0 && _image[y-1][x+1][0] == 0 
				&& _image[y][x-1][0] == 0) {
			return true;
		}
	}
	return false;
}

int con_com_label::getLowestLabel(int x, int y) {
	int label = -1;
	if(x != 0 && y != 0 && x != image_width - 1 && y != image_height - 1) {
		int neighbor_labels[4];
		neighbor_labels[0] = label_matrix[y-1][x];
		neighbor_labels[1] = label_matrix[y-1][x-1];
		neighbor_labels[2] = label_matrix[y-1][x+1];
		neighbor_labels[3] = label_matrix[y][x-1];

		//lots of logic to consider for cases when there are multiple labels in the neighborhood.
		for(int i = 0; i < 4; i++) {
			if(neighbor_labels[i] != -1) {
				if(label == -1) {
					label = neighbor_labels[i];
				} else {
					if(label != neighbor_labels[i]) {
						if(label > neighbor_labels[i]) {
							label_equivalence.find(label)->second = neighbor_labels[i];
							label = neighbor_labels[i];
						}
						else if(label < neighbor_labels[i]) {
							label_equivalence.find(neighbor_labels[i])->second = label;
						}
					}
				}
			}
		}
	}
	return label;
}


#endif