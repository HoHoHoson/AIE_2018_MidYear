#include <string>
#include <iostream>

std::string adj;
std::string verb;
std::string noun;

int a = 0;
int b = 0;

void enter()
{
	std::cout << "Enter an adjective";
	std::cin >> adj;
	

	std::cout << "Enter a verb";
	std::cin >> verb;

	std::cout << "Enter a noun";
	std::cin >> noun;

}
void numberSwap(){
std::cout << "Insert two numbers: ";
std::cin >> a >> b;

std::cout << "\nA: " << a << "\tB: " << b << "\nThe numbers will now magically switch places!" << std::endl;
std::swap(a, b);

std::cout << "\nA: " << a << "\tB: " << b << "\nIsn't that amazing!!" << std::endl;
}

void main() 
{
	enter();
	std::cout << "The quick, " << adj << " fox " << verb << "s over the lazy " << noun << std::endl;
	numberSwap();
	system("pause");
}
