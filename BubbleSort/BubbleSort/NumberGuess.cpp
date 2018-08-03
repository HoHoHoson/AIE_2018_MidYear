#include "NumberGuess.h"


NumberGuess::NumberGuess()
{
	srand((unsigned int)time(nullptr));
	loadHighScores();
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
			aiMode();
			break;
		}
		case Scoreboard:
		{
			scoreBoard();
			break;
		}
		case Exit:
		{
			saveHighScores();
			quit = true;
		}
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
			"\nNUMBER GUESS\n\n"
			"\t(1) Play\n"
			"\t(2) Lotto Predictor\n"
			"\t(3) HighScores\n"
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
		std::cout << "\nChoose a number between " << h_Min << " - " << h_Max << "\n\n";

		if (isValid == false)
			std::cout << "Invalid value!\n";

		readInput("Target value > ", value);

		if (value > h_Min && value < h_Max)
			isValid = true;
		else
			isValid = false;
		system("cls");
	} while (!isValid);
	std::cout << "\nYou have rigged the lottery number to be " << value << std::endl;
}

void NumberGuess::game()
{
	unsigned int input;
	std::string temp;

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
		readInput(("\n\t" + std::to_string(h_Min) + " < n < " + std::to_string(h_Max) + "\nn" + std::to_string(h_Turns) + " > "), input);

		rangeSetter(input);
		if (input == h_TargetNumber)
		{
			std::cout << 
				"\n\tn = " << h_TargetNumber << 
				"\n\nYou guessed 'n' in " << h_Turns << " turns!\n";
			break;
		}
	} while (true);

	if (h_Turns < leaderBoard[9].playerTurns)
	{
		std::cout << "\nYou've made it onto the scoreboard!\n";
		leaderBoard[9].playerTurns = h_Turns;
		do
		{
			readInput("\nName (max.10 chars)\n", temp);
		} while (temp.length() > 10);
		leaderBoard[9].playerName = temp;
	}
	else
		pressEnterToContinue();
	gameState = Menu;
}

void NumberGuess::aiMode()
{
	system("cls");
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
		std::cout <<
			"\nLOTTERY PREDICTOR\n\n"
			"\t(1) Set a random number\n"
			"\t(2) Set your own number\n"
			"\t(3) Exit to menu\n> ";
		std::cin >> i;
		std::cin.get();

		switch (i)
		{
		case '1':
		{
			system("cls");
			h_TargetNumber = (rand() % h_Max + 1) - 1;
			std::cout << "\nThe lottery number is " << h_TargetNumber << "\n\n";
			validChoice = true;
			break;
		}
		case '2':
		{
			system("cls");
			setTarget(h_TargetNumber);
			validChoice = true;
			break;
		}
		case '3':
		{
			gameState = Menu;
			return;
		}
		default:
			validChoice = false;
		}
	} while (!validChoice);

	do
	{
		std::cout << "\n\t" + std::to_string(h_Min) + " < n < " + std::to_string(h_Max);
		value = (h_Max - h_Min) / 2 + h_Min;
		rangeSetter(value);
		h_Turns++;
		std::cout << "\nAI predicted " << value;

		if (value == h_TargetNumber)
		{
			std::cout <<
				"\n\n\tn = " << h_TargetNumber <<
				"\n\The AI guessed 'n' in " << h_Turns << " turns!\n";
		}
		pressEnterToContinue();
	} while (value != h_TargetNumber);

	std::cout << h_Turns;
}

void NumberGuess::rangeSetter(unsigned int input)
{
	if (input > h_TargetNumber && input < h_Max)
		h_Max = input;
	if (input < h_TargetNumber && input > h_Min)
		h_Min = input;
}




