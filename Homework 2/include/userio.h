#ifndef USERIO_H
#define USERIO_H
#include <iostream>

int userInput() {
	while(true) {
		std::cout << "Problem 1b" << std::endl;
		std::cout << "Enter H (Hillary) or T (Trump)" << std::endl;
		char q;
		std::cin >> q;
		if(q == 'H') {
			return 1;
		} else if(q == 'T') {
			return 2;
		} else {
			std::cout << "Neither H or T is entered" << std::endl;
			std::cout << "Exiting..." << std::endl;
			return 0;
		}
	}
}

#endif