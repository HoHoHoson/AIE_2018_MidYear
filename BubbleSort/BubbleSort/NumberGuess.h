#pragma once
#include <iostream>
#include <string>
#include <time.h>


class NumberGuess
{
public:
	NumberGuess();
	~NumberGuess();

	void startUp();
	void menuScreen();
	void setMax();
	void game();

	template<typename T>
	void bubbleSorter(T* arr, int size);
	template<typename T>
	void readInput(const std::string & prefix, T& input);

private:

	unsigned int h_Min;
	unsigned int h_Max;
	unsigned int h_TargetNumber;
	enum h_state
	{
		Menu,
		Game,
		Scoreboard,
		Exit
	};
	h_state gameState;
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
			int temp;
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

