#include "NumberGuess.h"


NumberGuess::NumberGuess()
{
	srand((unsigned int)time(nullptr));
	gameState = Menu;
	h_Min = 0;
	h_Max = 100;
}

NumberGuess::~NumberGuess()
{

}

void NumberGuess::startUp()
{
	bool quit = false;

	do
	{
		switch (gameState)
		{
		case Menu:
		{
			menuScreen();
			break;
		}
		case Game:
		{
			game();
			break;
		}
		case Exit:
			quit = true;
		}
	} while (!quit);
}

void NumberGuess::menuScreen()
{
	unsigned int choice;

	do
	{
		system("cls");
		std::cout <<
			"Number Guess\n\n"
			"\t(1) Play\n"
			"\t(2) Lotto Predictor(WiP)\n"
			"\t(3) HighScores(WiP)\n"
			"\t(4) Exit Game\n";
		readInput("> ", choice);
	} while (choice == 0 || choice > 4);

	switch (choice)
	{
	case 1:
	{
		gameState = Game;
	}
	case 2:
	{

	}
	case 3:
	{

	}
	case 4:
	{
		gameState = Exit;
	}
	}
}

void NumberGuess::setMax()
{
	std::cout << "Set the max range: ";
	std::cin >> h_Max;
}

void NumberGuess::game()
{
	system("cls");
	h_TargetNumber = (rand() % h_Max + 1) - 1;
	bool win = false;
	int input;
	while (!win)
	{
		readInput("input: ", input);
		if (input > h_TargetNumber && input < h_Max)
			h_Max = input;
		if (input < h_TargetNumber && input > h_Min)
			h_Min = input;
		if (input == h_TargetNumber)
		{
			std::cout << "You are a weener\n";
			break;
		}
		std::cout << h_Min << "  " << h_Max << std::endl;
	}
}

struct HighScores
{
	std::string name;
	unsigned int score;
};

bool operator>(HighScores& score1, HighScores& score2)
{
	return (score1.score > score2.score);
}


