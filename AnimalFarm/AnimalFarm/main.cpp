
#include "Farm.h"
#include "types.h"

int main()
{
	int choice;
	Farm myFarm;
	myFarm.drawMenu();


	while (true)
	{
		std::cin >> choice;
		system("cls");

		switch (choice)
		{
		case 2:
		{
			myFarm.addAnimal(new Chickpea);
			break;
		}
		case 1:
		{
			myFarm.operator+(new Chicken);
			//myFarm.addAnimal(new Chicken);
			break;
		}
		case 3:
		{
			myFarm.addAnimal(new Chickadee);
			break;
		}
		case 4:
		{
			myFarm.playSounds();
			break;
		}
		case 5:
		{
			myFarm.listAnimal();
			break;
		}
		case 6:
		{
			myFarm.slaughter();
		}
		}
		std::cout << std::endl;
		myFarm.drawMenu();
	}

	system("pause");
	return 0;
}
