#include "idle_clicker_helper.h"

bool gameRunning = true;
bool alt = true;
int caps = 0;
int pigeons = 0;
int pigeonCost;
int alcoholic = 0;
int alcoholicCost;
int dDiver = 0;
int dDiverCost;
int recycling = 10;
int recyclingCost;




void update() 
{
	caps += pigeons;
	pigeonCost = pow(10, 1 + (pigeons * 0.05));
	caps += alcoholic * 11;
	alcoholicCost = pow(100, 1 + (alcoholic * 0.05));
	caps += dDiver * 120;
	dDiverCost = pow(1000, 1 + (dDiver * 0.05));
	caps += recycling * 1300;
	recyclingCost = pow(10000, 1 + (recycling * 0.05));
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
		std::cout << "You have " << recycling << " Recycling Centers\n";
	std::cout << "(4)Open a recycling center. It's like charity, for yourself! (" << recyclingCost << " Caps)\n";
	std::cout << std::endl;
}



void handleKey(char c)
{
	//std::cout << "You pressed " << c << std::endl;
	if (c == 'p')
	{
		/*std::cout << "Should quit\n";*/
		gameRunning = false;
	}

	if (c == 'q' && alt == true && c != 'w')
	{
		caps++;
		alt = false;
		draw();
	}
	else if (c == 'w' && alt == false && c != 'q') 
	{
		caps++;
		alt = true;
		draw();
	}

	if (c == '1')
	{
		if (caps >= pigeonCost)
		{

			caps -= pigeonCost;
			pigeons++;
			draw();
		}
		else
			std::cout << "Not enough Caps..\n";
	}
	if (c == '2')
	{
		if (caps >= alcoholicCost)
		{
			alcoholic++;
			draw();
			caps -= alcoholicCost;
		}
		else
			std::cout << "Not enough Caps..\n";
	}
	if (c == '3')
	{
		if (caps >= dDiverCost)
		{
			dDiver++;
			draw();
			caps -= dDiverCost;
		}
		else
			std::cout << "Not enough Caps..\n";
	}
	if (c == '4')
	{
		if (caps >= recyclingCost)
		{
			recycling++;
			draw();
			caps -= recyclingCost;
		}
		else
			std::cout << "Not enough Caps..\n";
	}
}



int main()
{
	AsyncKeyboard::setupKeyboard(handleKey);

	while (gameRunning) 
	{
		update();
		draw();
		std::this_thread::sleep_for(1s);
	}

	AsyncKeyboard::shutdown;

	return 0;
}