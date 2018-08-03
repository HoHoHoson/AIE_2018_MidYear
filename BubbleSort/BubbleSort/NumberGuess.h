#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <fstream>


struct HighScore
{
	std::string playerName = "---";
	unsigned int playerTurns = 9999;
};

class NumberGuess
{
public:
	NumberGuess();
	~NumberGuess();

	void startUp();

private:

	std::fstream h_SaveFile;
	unsigned int h_Min;
	unsigned int h_Max;
	unsigned int h_TargetNumber;
	unsigned int h_Turns;
	HighScore leaderBoard[10];

	enum h_state
	{
		Menu,
		Game,
		AI,
		Scoreboard,
		Exit
	};
	h_state gameState;

	void menuScreen();
	void game();
	void aiMode();
	void scoreBoard();
	void setTarget(unsigned int& value);
	void rangeSetter(unsigned int input);
	void saveHighScores();
	void loadHighScores();
	void pressEnterToContinue();

	template<typename T>
	void bubbleSorter(T* arr, int size);
	template<typename T>
	void readInput(const std::string & prefix, T& input);

};

template<typename T>
inline void NumberGuess::bubbleSorter(T * arr, int size)
{
	bool swapped;
	do
	{
		swapped = false;
		for (int i = 0; i < size - 1; ++i)
		{
			T temp;
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = true;
			}
		}
	} while (swapped);
}

inline bool operator>(HighScore& s1, HighScore& s2)
{
	if (s1.playerTurns > s2.playerTurns)
		return true;
	else
		return false;
}

template<typename T>
inline void NumberGuess::readInput(const std::string & prefix, T & input)
{
	do
	{
		std::cout << prefix;

		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> input;

	} while (std::cin.fail());
}

