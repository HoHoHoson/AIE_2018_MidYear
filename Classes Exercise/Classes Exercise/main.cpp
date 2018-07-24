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
	bool alive[zedNum];
	Zombie zed[zedNum];
	AltZed bob;

	do
	{
	for (int i = 0; i < zedNum; i++)
	{
		if (zed[i].getHealth() <= 0 && alive[i])
		{
			alive[i] = false;
			dedZed++;
			std::cout << "Zed" << i << " died!\n";
		}
		else if (alive[i])
		{
		randDmg = (rand() % (10 + 1)) + 5;
		zed[i].z_initialise(randDmg, "bill");
		std::cout << "Zed" << i << " on " << zed[i].getHealth() << " HP dealt " << zed[i].getDamage() << " damage to Bob" << std::endl;
		totalDmg += randDmg;
		}
	}
	if (zedNum != dedZed)
	{
		bob.damage(totalDmg);
		if (bob.getHealth() < 0)
			bob.setHealth();
		std::cout << "Bob is on " << bob.getHealth() << " HP" << std::endl;
		zed[rand() % (zedNum)].damage(rand() % (30) + 11);
	}
	else
		std::cout << "All Zeds were eradicated!\n";
	if (bob.getHealth() <= 0)
		std::cout << "Bob died!\n";
	totalDmg = 0;
	} while (zedNum != dedZed && bob.getHealth() > 0);
	
}


int main()
{
	update();

	system("pause");
	return 0;
}