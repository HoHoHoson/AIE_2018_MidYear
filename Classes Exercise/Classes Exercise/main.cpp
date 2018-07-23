#include <random>
#include <ctime>
#include "zombie.h"
#include "altZed.h"


void update()
{
	const int zedNum = 5;
	int dedZed = 0;
	int randDmg;
	int totalDmg = 0;
	srand((unsigned int)time(nullptr));
	Zombie zed[zedNum];
	AltZed bob;

	for (int i = 0; i < zedNum - dedZed; i++)
	{
		randDmg = (rand() % (10 + 1)) + 5;
		zed[i].z_initialise(randDmg, "bill");
		std::cout << zed[i].getDamage() << std::endl;
		totalDmg += randDmg;
	}
	bob.damage(totalDmg);
	std::cout << bob.getHealth() << std::endl;
}


int main()
{
	update();

	system("pause");
	return 0;
}