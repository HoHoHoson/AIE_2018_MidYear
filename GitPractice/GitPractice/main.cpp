#include <string>
#include <iostream>

std::string adj;
std::string verb;
std::string noun;

void enter()
{
	std::cout << "Enter an adjective";
	std::cin >> adj;

	std::cout << "Enter a verb";
	std::cin >> verb;

	std::cout << "Enter a noun";
	std::cin >> noun;
}

int main() 
{
	enter();
	std::cout << "The quick, " << adj << " fox " << verb << "s over the lazy " << noun << std::endl;
	system("pause");
}