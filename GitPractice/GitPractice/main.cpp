#include <iostream>

int main() 
{
	int a = 0;
	int b = 0;

	std::cout << "Insert two numbers: ";
	std::cin >> a >> b;

	std::cout << "\nA: " << a << "\tB: " << b << "\nThe numbers will now magically switch places!" << std::endl;
	std::swap(a, b);

	std::cout << "\nA: " << a << "\tB: " << b << "\nIsn't that amazing!!" << std::endl;

	return 0;
}