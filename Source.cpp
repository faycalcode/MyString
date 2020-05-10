#include <iostream>
#include "MyString.h"

int main() {

	try {

		MyString s;

		std::cin >> s;


	}	
	catch (const char* e) {
		std::cout << "Error: " << e <<std::endl;
		return -1;
	}
	catch (const std::bad_alloc& e) {
		std::cout << "Allocation failed: " << e.what() << std::endl;
		return -1;
	}
	
	return 0;
}