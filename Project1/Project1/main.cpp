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


struct Knight
{
	int health;

	std::string choice;
	std::string name;
};


void battle(bool& defenderTurn, Knight& attacker, Knight& defender, int& minDmg, int& maxDmg) 
{
	int damageDisplay = randomValue(minDmg, maxDmg);
	bool validChoice = false;


	std::cout << std::endl;
	std::cout << attacker.name << " starts it off!\n";
	do
	{
		std::cout << std::endl;
		std::cin >> attacker.choice;
		if (attacker.choice == "attack" || attacker.choice == "block" || attacker.choice == "tackle")
		{
			validChoice = true;
			system("cls");
			std::cout << std::endl;
			std::cout << attacker.name << " readies their stance.\n";
		}
		else
		{
			system("cls");
			std::cout << std::endl;
			std::cout << "Invalid command, try again.\n";
			validChoice = false;
		}
	} while (!validChoice);

	do
	{
		std::cout << std::endl;
		std::cout << "It's " <<defender.name << " turn!\n";
		std::cout << std::endl;
		std::cin >> defender.choice;
		validChoice = true;
		if (defender.choice == attacker.choice)
		{
			std::cout << std::endl;
			std::cout << attacker.name << " and " << defender.name << " clashes equally in a flurry of steel!\n";
		}
		else if (defender.choice == "attack")
		{
			if (attacker.choice == "tackle")
			{
				std::cout << std::endl;
				std::cout << attacker.name << " sprints in for a full force tackle,\njust to lunge straight into " << defender.name << "'s sword!\n";
				damageDisplay;
				attacker.health -= damageDisplay;
				std::cout << std::endl;
				std::cout << defender.name << " impales " << attacker.name << " for " << damageDisplay << " damage.\n";
				std::cout << std::endl;
				if (attacker.health <= 0)
				{
					std::cout << attacker.name << " bleeds out on " << defender.name << "'s blade\n";
					std::cout << std::endl;
					std::cout << defender.name << " Wins!\n";
				}
				else 
				{
					std::cout << attacker.name << " survives with " << attacker.health << " HP.\n";
				}
			}
			if (attacker.choice == "block")
			{
				std::cout << std::endl;
				std::cout << defender.name << " attacks with a forward thrust.\n" << attacker.name << ", with quick reflexes, blocks the attack!\n";
				damageDisplay;
				defender.health -= damageDisplay;
				std::cout << std::endl;
				std::cout << defender.name << "'s sword pinged off of " << attacker.name << "'s shield,\nopening " << defender.name << " up for " << damageDisplay << " counterattack damage!\n";
				std::cout << std::endl;
				if (defender.health <= 0)
				{
					std::cout << attacker.name << " decapitates " << defender.name << " with a clean cut!\n";
					std::cout << std::endl;
					std::cout << attacker.name << " Wins!\n";
				}
				else
				{
					std::cout << defender.name << " survives with " << defender.health << " HP.\n";
				}
			}
		}
		else if (defender.choice == "block")
		{
			if (attacker.choice == "attack")
			{
				std::cout << std::endl;
				std::cout << attacker.name << " attacks with a forward thrust.\n" << defender.name << ", with quick reflexes, blocks the attack!\n";
				damageDisplay;
				attacker.health -= damageDisplay;
				std::cout << std::endl;
				std::cout << attacker.name << "'s sword pinged off of " << defender.name << "'s shield,\nopening " << attacker.name << " up for " << damageDisplay << " counterattack damage!\n";
				std::cout << std::endl;
				if (attacker.health <= 0)
				{
					std::cout << defender.name << " decapitates " << attacker.name << " with a clean cut!\n";
					std::cout << std::endl;
					std::cout << defender.name << " Wins!\n";
				}
				else
				{
					std::cout << attacker.name << " survives with " << attacker.health << " HP.\n";
				}
			}
			if (attacker.choice == "tackle")
			{
				std::cout << std::endl;
				std::cout << defender.name << " raises their shield in expectance of a bladed strike.\nInstead, " << attacker.name << " crashes into their shield with a forceful shoulder tackle!\n";
				damageDisplay;
				defender.health -= damageDisplay;
				std::cout << std::endl;
				std::cout << attacker.name << " follows up with a bone shattering shield bash for " << damageDisplay << " damage!" << std::endl;
				std::cout << std::endl;
				if (defender.health <= 0)
				{
					std::cout << attacker.name << " shatters " << defender.name << "'s skull with a crippling blow from their shield!\n";
					std::cout << std::endl;
					std::cout << attacker.name << " Wins!\n";
				}
				else
				{
					std::cout << defender.name << " survives with " << defender.health << " HP.\n";
				}
			}
		}
		else if (defender.choice == "tackle")
		{
			if (attacker.choice == "block")
			{
				std::cout << std::endl;
				std::cout << attacker.name << " raises their shield in expectance of a bladed strike.\nInstead, " << defender.name << " crashes into their shield with a forceful shoulder tackle!\n";
				damageDisplay;
				attacker.health -= damageDisplay;
				std::cout << std::endl;
				std::cout << defender.name << " follows up with a bone shattering shield bash for " << damageDisplay << " damage!" << std::endl;
				std::cout << std::endl;
				if (attacker.health <= 0)
				{
					std::cout << defender.name << " shatters " << attacker.name << "'s skull with a crippling blow from their shield!\n";
					std::cout << std::endl;
					std::cout << defender.name << " Wins!\n";
				}
				else
				{
					std::cout << attacker.name << " survives with " << attacker.health << " HP.\n";
				}
			}
			if (attacker.choice == "attack")
			{
				std::cout << std::endl;
				std::cout << defender.name << " sprints in for a full force tackle,\njust to lunge straight into " << attacker.name << "'s sword!\n";
				damageDisplay;
				defender.health -= damageDisplay;
				std::cout << std::endl;
				std::cout << attacker.name << " impales " << defender.name << " for " << damageDisplay << " damage.\n";
				std::cout << std::endl;
				if (defender.health <= 0)
				{
					std::cout << defender.name << " bleeds out on " << attacker.name << "'s blade\n";
					std::cout << std::endl;
					std::cout << attacker.name << " Wins!\n";
				}
				else 
				{
					std::cout << defender.name << " survives with " << defender.health << " HP.\n";
				}
			}
		}
		else
		{
			validChoice = false;
			system("cls");
			std::cout << std::endl;
			std::cout << "Invalid command, try again.\n";
		}
	} while (!validChoice);

	std::cout << std::endl;
	system("pause");
	system("cls");
	if (defenderTurn)
		defenderTurn = false;
	else
		defenderTurn = true;

}


void turnbasedKnights()
{
	srand((unsigned int)time(nullptr));
	//int randomValue = (rand() % (264 - 50)) + 50;

	Knight knight1;
	Knight knight2;
	bool defenderTurn = false;
	int setHealth = 10;
	int setMaxDamage = 6;
	int setMinDamage = 4;


	std::cout << std::endl;
	std::cout << "Knight 1 name : ";
	std::cin >> knight1.name;
	std::cout << std::endl;
	std::cout << "Knight 2 name : ";
	std::cin >> knight2.name;
	std::cout << std::endl;
	system("cls");

	knight1.health = setHealth;
	knight2.health = setHealth;

	while (knight1.health > 0 && knight2.health > 0)
	{
		if (!defenderTurn)
			battle(defenderTurn, knight1, knight2, setMinDamage, setMaxDamage);
		else
			battle(defenderTurn, knight2, knight1, setMinDamage, setMaxDamage);
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
	knightsBeatingEachOtherSim();

	system("pause");
	return 0;
}
