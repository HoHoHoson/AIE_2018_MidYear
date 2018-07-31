#include <iostream>

int main()
{
	int a;
	int b;
	int c;
	float f1;
	float f2;
	float f3;
	char input;

	std::cout << "What should A be equal to?\n";
	std::cin >> a;
	std::cout << "A = " << a << std::endl;
	std::cout << std::endl;
	std::cout << "Now, what should B be equal to?\n";
	std::cin >> b;
	std::cout << "B = " << b << std::endl;
	std::cout << std::endl;
	c = a + b;
	std::cout << "If C = A + B, it should equal to.. " << c << std::endl;
	std::cout << std::endl;
	c *= 2;
	std::cout << "Doubling C would put out: " << c << std::endl;
	std::cout << std::endl;
	c *= c;
	std::cout << "Now square it! " << c << std::endl;
	std::cout << std::endl;
	std::cout << "Lets try a decimal: \n";
	std::cin >> f1;
	std::cout << "Decimal #1 = " << f1 << std::endl;
	std::cout << std::endl;
	std::cout << "Give another decimal: \n";
	std::cin >> f2;
	std::cout << "Decimal #2 = " << f2 << std::endl;
	std::cout << std::endl;
	f3 = f1 + f2;
	std::cout << "The two decimals should equal to.. " << f3 << std::endl;
	std::cout << std::endl;
	std::cout << "Input anything to continue: \n";
	std::cin >> input;


	return 0;
}