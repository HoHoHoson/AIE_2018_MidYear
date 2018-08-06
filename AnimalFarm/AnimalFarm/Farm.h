#pragma once
#include "animals.h"

const int BASE_ANIMALS = 5;

class Farm
{
public:
	Farm();
	~Farm();

	void listAnimal();
	void addAnimal(Animals* animal);
	void playSounds();
	void drawMenu();
	void slaughter();
	void operator + (Animals* animal);
	void expandFarm();

private:
	Animals **h_FarmArray = new Animals*[BASE_ANIMALS];
	int h_CurrentNumber = 0;
	int h_Money = 5;
	int h_FarmCost = 5;
	int h_MaxAnimals;
};
