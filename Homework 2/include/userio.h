#ifndef USERIO_H
#define USERIO_H
#include <iostream>

int userInputq1b() {
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

int userInputq1c() {
	while(true) {
		std::cout << "Problem 1c" << std::endl;
		std::cout << "Enter 1 (Tartans) or 2 (Trojans)" << std::endl;
		char q;
		std::cin >> q;
		if(q == '1') {
			return 1;
		} else if(q == '2') {
			return 2;
		} else {
			std::cout << "Neither H or T is entered" << std::endl;
			std::cout << "Exiting..." << std::endl;
			return 0;
		}
	}
}

//*TODO*//
int userInputq2a() {
	while(true) {
		std::cout << "Problem 2a" << std::endl;
		std::cout << "Enter 1 (Tartans) or 2 (Trojans)" << std::endl;
		char q;
		std::cin >> q;
		if(q == '1') {
			return 1;
		} else if(q == '2') {
			return 2;
		} else {
			std::cout << "Neither H or T is entered" << std::endl;
			std::cout << "Exiting..." << std::endl;
			return 0;
		}
	}
}

#endif