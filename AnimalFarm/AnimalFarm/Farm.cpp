#include "Farm.h"

Farm::Farm()
{
	
}

Farm::~Farm()
{
	for (int i = 0; i < h_CurrentNumber; ++i)
	{
		delete h_FarmArray[i];
	}
}

void Farm::listAnimal()
{
	int numChickens = 0;
	int numChickpeas = 0;
	int numChickdees = 0;

	for (int i = 0; i < h_CurrentNumber; ++i)
	{
		std::string type = h_FarmArray[i]->getType();
		if (type == "Chicken")
			numChickens++;
		if (type == "Chickpea")
			numChickpeas++;
		if (type == "Chickadee")
			numChickdees++;
	}

	std::cout << "You have " << numChickens << " Chickens\n";
	std::cout << "You have " << numChickpeas << " Chickpeas\n";
	std::cout << "You have " << numChickdees << " Chickadees\n";
}

void Farm::addAnimal(Animals * animal)
{

	if (h_CurrentNumber >= MAX_ANIMALS)
	{
		std::cout << "Not enough space.\n";
		delete animal;
		return;
	}
	if (h_Money == 0)
		std::cout << "Too poor.\n";

	h_FarmArray[h_CurrentNumber] = animal;
	h_CurrentNumber++;
	h_Money--;
	std::cout << animal->getType() << " added." << std::endl;
}

void Farm::playSounds()
{
	if (h_CurrentNumber == 0)
	{
		std::cout << "All you hear is sweet silence.\n";
		return;
	}
	for (int i = 0; i < h_CurrentNumber; ++i)
	{
		h_FarmArray[i]->playSound();
	}
}

void Farm::drawMenu()
{
	std::cout << "You have " << h_Money << " coins!\n";
	std::cout << "Farm has (" << h_CurrentNumber << "/" << MAX_ANIMALS << ") Animals" << std::endl;
	std::cout << std::endl;
	std::cout << "\t1. Chicken\n";
	std::cout << "\t2. Chickpea\n";
	std::cout << "\t3. Chickadee\n";
	std::cout << "\t4. Play animal sounds\n";
	std::cout << "\t5. Count number of animals\n";
	std::cout << "\t6. Murderize\n";
}

void Farm::slaughter()
{
	if (h_CurrentNumber == 0)
	{
		std::cout << "You don't have any unfortunate animals.\n";
		return;
	}
	int temp = h_CurrentNumber;
	int earned = 0;
	for (int i = 0; i < temp; i++)
	{
		h_Money += 2;
		earned += 2;
		h_CurrentNumber--;
	}
	std::cout << "You hear the screams of tiny voices.\n";
	std::cout << "Earned " << earned << " bloody coins!\n";
}
