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

void NumberGuess::pressEnterToContinue()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
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
		case AI:
		{
			break;
		}
		case Scoreboard:
		{
			scoreBoard();
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
			"\nNumber Guess\n\n"
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
		break;
	}
	case 2:
	{
		gameState = AI;
		break;
	}
	case 3:
	{
		gameState = Scoreboard;
		break;
	}
	case 4:
		gameState = Exit;
	}
}

void NumberGuess::setTarget(unsigned int& value)
{
	bool isValid = true;
	do
	{
		if (isValid == false)
			std::cout << "Invalid value!\n";

		readInput("Set the target value: ", value);

		if (value > h_Min && value < h_Max)
			isValid = true;
		else
			isValid = false;
		system("cls");
	} while (!isValid);
	std::cout << "You have chosen: " << value << std::endl;
}

void NumberGuess::game()
{
	unsigned int input;
	h_Turns = 0;
	h_Max = 100;
	h_Min = 0;

	system("cls");
	h_TargetNumber = (rand() % h_Max + 1) - 1;
	std::cout <<
		"\nA random number 'n' between " << h_Min << " - " << h_Max << " has been chosen!\n\n";

	do
	{
		h_Turns++;
		readInput(("\t" + std::to_string(h_Min) + " < n < " + std::to_string(h_Max) + "\nn" + std::to_string(h_Turns) + " > "), input);

		if (input > h_TargetNumber && input < h_Max)
			h_Max = input;
		if (input < h_TargetNumber && input > h_Min)
			h_Min = input;
		if (input == h_TargetNumber)
		{
			std::cout << 
				"\tn = " << h_TargetNumber << 
				"\n\nYou guessed 'n' in " << h_Turns << " turns!\n";
			std::cin.get();
			break;
		}
	} while (true);

	pressEnterToContinue();
	gameState = Menu;
}

void NumberGuess::aiMode()
{
	char i;
	bool validChoice = false;
	unsigned int value;

	h_Max = 100;
	h_Min = 0;
	h_Turns = 0;

	do
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> i;
		std::cin.get();

		switch (i)
		{
		case '1':
		{
			value = (rand() % h_Max + 1) - 1;
			validChoice = true;
			break;
		}
		case '2':
		{
			setTarget(value);
			validChoice = true;
			break;
		}
		default:
			validChoice = false;
		}
	} while (!validChoice);
}

struct HighScores
{
	std::string name;
	unsigned int score;
};

bool operator<(HighScores& score1, HighScores& score2)
{
	return (score1.score < score2.score);
}

void NumberGuess::scoreBoard()
{
	bool reSort;
	HighScores leaderBoard[10];

	system("cls");
	std::cout << "\nHighScores\n\n";

	for (int i = 0; i < 10; ++i)
	{
		leaderBoard[i].name = "bill no." + std::to_string(i);
		leaderBoard[i].score = rand() % 21;
	}

	bubbleSorter(leaderBoard, 10);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << std::setw(5) << std::left << "\t" + std::to_string(i + 1) + ". ";
		std::cout << std::setw(15) << std::left << leaderBoard[i].name; 
		std::cout << std::setw(15) << std::left << leaderBoard[i].score;

		std::cout << std::endl;
	}

	pressEnterToContinue();
	gameState = Menu;
}



