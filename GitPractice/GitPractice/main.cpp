#include <string>
#include <iostream>
#include <random>
#include <ctime>

std::string adj;
std::string verb;
std::string noun;

void enterWords()
{
	std::cout << "Enter an adjective";
	std::cin >> adj;

	std::cout << "Enter a verb";
	std::cin >> verb;

	std::cout << "Enter a noun";
	std::cin >> noun;

	std::cout << "The quick, " << adj << " fox " << verb << "s over the lazy " << noun << std::endl;

}
void numberSwap() {

	int a = 0;
	int b = 0;

	std::cout << "Insert two numbers: ";
	std::cin >> a >> b;

	std::cout << "\nA: " << a << "\tB: " << b << "\nThe numbers will now magically switch places!" << std::endl;
	std::swap(a, b);

	std::cout << "\nA: " << a << "\tB: " << b << "\nIsn't that amazing!!" << std::endl;
}

void guessNumber() {

	int randomValue = rand() % 60 + 1;


	//This is a simple guess the number game..also helps to teach binary search
	bool foundAnswer = false;
	int answer = -1;
	while (!foundAnswer)
	{
		std::cout << "Enter any number: " << std::endl;
		std::cin >> answer;

		if (answer < randomValue)
		{
			std::cout << "Higher, try again!\n";
		}
		else if (answer > randomValue)
		{
			std::cout << "Lower, try again!\n";
		}
		else
		{
			foundAnswer = true;
			std::cout << "Just right!\n";
		}
	}
}


void main() 
{
	int lollipop = 0;
	enterWords();
	numberSwap();
	guessNumber();
	system("pause");
}
