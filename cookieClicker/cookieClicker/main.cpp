#include "idle_clicker_helper.h"

bool gameRunning = true;
bool alt = true;
bool gameMenu = true;
bool cooldown = false;
unsigned int caps = 0;
int pigeons = 1;
int pigeonCost;
int alcoholic = 1;
int alcoholicCost;
int dDiver = 1;
int dDiverCost;
int recycling = 1;
int recyclingCost;
int factory = 1;
int factoryCost;




void update() 
{
	caps += pigeons;
	pigeonCost = pow(10, 1 + (pigeons * 0.01));
	caps += alcoholic * 11;
	alcoholicCost = pow(100, 1 + (alcoholic * 0.01));
	caps += dDiver * 120;
	dDiverCost = pow(1000, 1 + (dDiver * 0.01));
	caps += recycling * 1350;
	recyclingCost = pow(10000, 1 + (recycling * 0.01));
	caps += factory * 15000;
	factoryCost = pow(100000, 1 + (factory * 0.01));
}



void draw()
{
	system("cls");
	std::cout << std::endl;
	std::cout << "You have " << caps << " bottle Caps!\n";
	std::cout << std::endl;
	std::cout << "Alternate between (Q) & (W) to scavange for Caps\n";
	std::cout << std::endl;
	std::cout << std::endl;
	if (pigeons != 0)
		std::cout << "You have " << pigeons << " Pigeons!\n";
	std::cout << "(1)Trained Pigeon that collects Caps for you. (" << pigeonCost << " Caps)" << std::endl;
	std::cout << std::endl;
	if (alcoholic != 0)
		std::cout << "You have " << alcoholic << " Fat Beer people!\n";
	std::cout << "(2)Alcoholics for Caps, profiting off of someones addiction. (" << alcoholicCost << " Caps)\n";
	std::cout << std::endl;
	if (dDiver != 0)
		std::cout << "You have " << dDiver << " Hobos, now with Jobs!\n";
	std::cout << "(3)Hiring people off the streets to swim in dumpsters. (" << dDiverCost << " Caps)\n";
	std::cout << std::endl;
	if (recycling != 0)
		std::cout << "You have " << recycling << " Recycling Centers!\n";
	std::cout << "(4)Open a recycling center. It's like charity, for yourself. (" << recyclingCost << " Caps)\n";
	std::cout << std::endl;
	if (factory != 0)
		std::cout << "You have " << factory << " Cap Factories!\n";
	std::cout << "(5)Cap printing plant. This isn't money so its perfectly legal. (" << factoryCost << " Caps)\n";
	std::cout << std::endl;
	std::cout << "(6)Access the buy menu.\n";
	std::cout << std::endl;
	std::cout << "(x)Quit Game";
}

void tooPoor() 
{
	cooldown = true;
	std::cout << "                                             Not enough Caps...\n";
}


void handleKey(char c)
{
	//std::cout << "You pressed " << c << std::endl;
	if (c == 'x' && gameMenu)
	{
		/*std::cout << "Should quit\n";*/
		gameRunning = false;
	}

	if (c == 'q' && alt == true && c != 'w' && gameMenu)
	{
		caps++;
		alt = false;
		draw();
	}
	else if (c == 'w' && alt == false && c != 'q' && gameMenu)
	{
		caps++;
		alt = true;
		draw();
	}

	if (c == '1' && gameMenu)
	{
		if (caps >= pigeonCost)
		{

			caps -= pigeonCost;
			pigeons++;
			draw();
		}
		else if (!cooldown)
			tooPoor();
	}
	if (c == '2' && gameMenu)
	{
		if (caps >= alcoholicCost)
		{
			alcoholic++;
			draw();
			caps -= alcoholicCost;
		}
		else if (!cooldown)
			tooPoor();                                       
	}
	if (c == '3' && gameMenu)
	{
		if (caps >= dDiverCost)
		{
			dDiver++;
			draw();
			caps -= dDiverCost;
		}
		else if (!cooldown)
			tooPoor();
	}
	if (c == '4' && gameMenu)
	{
		if (caps >= recyclingCost)
		{
			recycling++;
			draw();
			caps -= recyclingCost;
		}
		else if (!cooldown)
			tooPoor();
	}
	if (c == '5' && gameMenu)
	{
		if (caps >= factoryCost)
		{
			factory++;
			draw();
			caps -= factoryCost;
		}
		else if (!cooldown)
			tooPoor();
	}

}


int main()
{
	AsyncKeyboard::setupKeyboard(handleKey);

	while (gameRunning) 
	{
		update();
		draw();
		cooldown = false;
		std::this_thread::sleep_for(1s);
	}

	AsyncKeyboard::shutdown;

	return 0;
}