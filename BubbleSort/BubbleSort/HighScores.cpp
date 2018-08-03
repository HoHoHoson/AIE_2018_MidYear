#include "NumberGuess.h"


struct HighScoreData
{
	HighScoreData() {}
	HighScoreData(const HighScore& data)
	{
		strcpy_s(storedName, 255, data.playerName.data());
		storedTurns = data.playerTurns;
	}

	char storedName[256];
	unsigned int storedTurns;
};

void NumberGuess::scoreBoard()
{
	bubbleSorter(leaderBoard, 10);

	system("cls");
	std::cout << 
		"\nHIGH SCORES\n\n";
	std::cout << std::setw(5) << std::left << "\tPOS";
	std::cout << std::setw(15) << std::left << "NAME";
	std::cout << std::setw(15) << std::left << "TURNS\n";
	std::cout << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		std::cout << std::setw(5) << std::left << "\t" + std::to_string(i + 1) + ". ";
		std::cout << std::setw(15) << std::left << leaderBoard[i].playerName;
		std::cout << std::setw(15) << std::left << leaderBoard[i].playerTurns;

		std::cout << std::endl;
	}

	pressEnterToContinue();
	gameState = Menu;
}

void NumberGuess::saveHighScores()
{
	h_SaveFile.open("scoreboard.dat", std::ios::binary | std::ios::out);

	if (h_SaveFile.good())
	{
		for (int i = 0; i < 10; ++i)
		{
			HighScoreData writeData(leaderBoard[i]);

			h_SaveFile.write((char*)&writeData, sizeof(HighScoreData));
		}
	}

	h_SaveFile.close();
}

void NumberGuess::loadHighScores()
{
	h_SaveFile.open("scoreboard.dat", std::ios::binary | std::ios::in);

	if (h_SaveFile.good())
	{
		for (int i = 0; i < 10; ++i)
		{
			HighScoreData readData;

			h_SaveFile.read((char*)&readData, sizeof(HighScoreData));

			leaderBoard[i].playerName = readData.storedName;
			leaderBoard[i].playerTurns = readData.storedTurns;
		}
	}

	h_SaveFile.close();
}

