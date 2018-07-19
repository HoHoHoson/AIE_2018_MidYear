#include <iostream>
#include <random>
#include <ctime>


int main()
{
	srand((unsigned int)time(nullptr));


	

	int a = 0;
	int b = 0;

	std::cout << "Insert two numbers: ";
	std::cin >> a >> b;

	std::cout << "\nA: " << a << "\tB: " << b << "\nThe numbers will now magically switch places!" << std::endl;
	std::swap(a, b);

	std::cout << "\nA: " << a << "\tB: " << b << "\nIsn't that amazing!!" << std::endl;

int randomValue = rand() % 10 + 1;

	bool foundAnswer = 0;
	int answer = -1;
	while (!foundAnswer)
	{
		std::cout << "Enter a number: " << std::endl;
		std::cin >> answer;

		if (answer < randomValue)
		{
			std::cout << "Too low, try again!\n";
		}
		else if (answer > randomValue)
		{
			std::cout << "Too high, try again!\n";
		}
		else
		{
			foundAnswer = true;
			std::cout << "Just right!\n";

		}
	}
	system("pause");
	return 0;
}