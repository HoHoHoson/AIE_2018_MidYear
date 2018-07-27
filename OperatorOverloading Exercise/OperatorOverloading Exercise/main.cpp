#include "a.h"

int main()
{
	Position pos;
	Position pos2;

	pos += 3;
	pos2 += 2;
	pos + pos2;
	pos2 = pos;
	pos -= 1;
	pos2 -= 3;
	pos - pos2;

	std::cout << "Coordinate 1: "; pos.getValues();
	std::cout << "Coordinate 2: "; pos2.getValues();
	std::cout << "Is pos equal to pos2: ";
	if (pos == pos2)
		std::cout << "True\n";
	else
		std::cout << "False\n";
	std::cout << "Is pos NOT equal to pos2: ";
	if (pos != pos2)
		std::cout << "True\n";
	else
		std::cout << "False\n";


	std::cout << std::endl;
	system("pause");
	return 0;
}