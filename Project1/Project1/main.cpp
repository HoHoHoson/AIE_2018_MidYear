#include <iostream>
#include <random>
#include <ctime>
#include <string>


void calculator()
{
	float n1;
	float n2;
	float n3 = 0;
	char operation;
	bool off = false;

	std::cout << "Enter first number: ";
	std::cin >> n1;

	std::cout << "Enter second number: ";
	std::cin >> n2;

	std::cout << "Enter an operator: ";
	std::cin >> operation;

	switch (operation)
	{
	case '+':
	{
		n3 = n1 + n2;
		break;
	}
	case '-':
	{
		n3 = n1 - n2;
		break;
	}
	case '*':
	{
		n3 = n1 * n2;
		break;
	}
	case '/':
	{
		n3 = n1 / n2;
		break;
	}
	default:
	{
		std::cout << "Error\n";
		break;
	}
	}

	if (n3 != 0)
	{
		std::cout << n3 << std::endl;
	}
	std::cout << "Input anything to exit\n";
	std::cin >> operation;
}


int doAttack(int currentHealth, int amountOfDamage,int multiplier)
{
	int totalDamage = amountOfDamage * multiplier;

	int finalHealth = currentHealth - totalDamage;
	if (finalHealth < 0)
		finalHealth = 0;

	return finalHealth;
}


int randomValue(int min, int max)
{
	int range = max - min;

	if (min == max)
		return min;
	else if (min > max)
	{
		range = min - max;
	}

	int randomValue = rand() % (range + 1);
	randomValue += min;

	return randomValue;
}



void battle(std::string attacker, std::string defender, int &knightHealth) 
{
	int damage;
	int dmg = 20;
	char choice;

	std::cin >> choice;

	switch (choice)
	{
	case'1':
	{
		std::cout << attacker << " readies their stance.\n";
		damage = randomValue(0, dmg);
		knightHealth -= damage;
		std::cout << attacker << " Attacks for " << damage << " damage." << std::endl;
		if (knightHealth <= 0)
		{
			knightHealth = 0;
			std::cout << defender << " Died\n";
			break;
		}
		else
			std::cout << defender << " survives with " << knightHealth << " health.\n";
		break;
	}
	case'2':
	{
		std::cout << attacker << " readies their stance.\n";
		break;
	}
	case'3':
	{
		std::cout << attacker << " readies their stance.\n";
		break;
	}
	default:
		std::cout << "pkiap\n";
		break;
	}
}


void turnbasedKnights()
{
	srand((unsigned int)time(nullptr));
	//int randomValue = (rand() % (264 - 50)) + 50;

	int k1Health = 100;
	int k1Dmg = 20;
	int k2Health = 100;
	int k2Dmg = 20;
	int dmg;
	std::string Knight2 = "Knight2";
	std::string Knight1 = "Knight1";


	while (k1Health != 0 && k2Health != 0)
	{
		battle(Knight2, Knight1, k1Health);
		/*dmg = randomValue(0, k2Dmg);
		k1Health -= dmg;
		std::cout << "Knight2 Attacks for " << dmg << " damage." << std::endl;
		if (k1Health <= 0)
		{
		k1Health = 0;
		std::cout << "Knight1 Died\n";
		break;
		}
		else
		std::cout << "Knight1 survives with " << k1Health << " health.\n";

		std::cout << std::endl;

		dmg = randomValue(0, k1Dmg);
		k2Health -= dmg;
		std::cout << "Knight1 Attacks for " << dmg << " damage."  << std::endl;
		if (k2Health <= 0)
		{
		k2Health = 0;
		std::cout << "Knight2 Died\n";
		}
		else
		std::cout << "Knight2 survives with " << k2Health << " health.\n";*/

		std::cout << std::endl;
	}
}

void knightsBeatingEachOtherSim()
{
	const int setHealth = 100;
	const int knightNum = 10;
	bool winner = false;
	bool alive[knightNum];
	int knightHealth[knightNum];
	int deadKnight = 0;
	int previousKnight = 7;
	int dmg;
	srand((unsigned int)time(nullptr));
	
	for (int i = 0; i < knightNum; i++) 
	{
		knightHealth[i] = setHealth;
		alive[i] = true;
	}

	do
	{
		for (int i = 0; i < knightNum; i++)
		{
			if (alive[i] == false){}
			else if (deadKnight == knightNum - 1) 
			{
				winner = true;
				std::cout << std::endl;
				std::cout << "Knight " << i << " Wins!" << std::endl;
				std::cout << std::endl;
			}
			else if (alive[i] == true)
			{
				dmg = randomValue(0, 10);
				knightHealth[i] -= dmg;
				std::cout << std::endl;
				std::cout << "Knight " << i << "'s ass was beat by Knight " << previousKnight << " for " << dmg << " damage" << std::endl;
				if (knightHealth[i] <= 0)
				{
					alive[i] = false;
					deadKnight++;
					std::cout << "Knight " << i << " Died!\n";
				}
				else
				{
					previousKnight = i;
					std::cout << "Knight " << i << " is left with " << knightHealth[i] << " HP\n";
				}
			}
		}
	} while (!winner);
}

int main()
{
	turnbasedKnights();

	system("pause");
	return 0;
}
