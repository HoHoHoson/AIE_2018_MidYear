#pragma once
#include "animals.h"

const int MAX_ANIMALS = 5;

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

private:
	Animals * h_FarmArray[MAX_ANIMALS];
	int h_CurrentNumber = 0;
	int h_Money = 5;
};
