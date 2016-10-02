#ifndef USERIO_H
#define USERIO_H
#include <iostream>

int userInput() {
	while(true) {
		std::cout << "Problem 1" << std::endl;
		std::cout << "Enter problem part a, b, or c" << std::endl;
		char q;
		std::cin >> q;
		if(q == 'a') {
			return 1;
		} else if(q == 'b') {
			return 2;
		} else if(q == 'c') {
			return 3;
		} else {
			return 0;
		}


	}
}

#endif