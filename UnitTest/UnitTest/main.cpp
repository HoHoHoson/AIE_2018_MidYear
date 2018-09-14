#include "unittest.h"
#include <iostream>

int main() {

	if (runUnitTests() == false) {
		std::cout << "Unit test failed!" << std::endl;
		std::cout << "\n";
		system("pause");
		return -1;
	}
	std::cout << "All tests passed successfully." << std::endl;

	std::cout << "\n";
	system("pause");
	return 0;
}