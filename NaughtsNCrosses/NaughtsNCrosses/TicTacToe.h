#pragma once
#include <iostream>
#include <string>


class NaughtsNCrosses
{
public:
	NaughtsNCrosses();
	~NaughtsNCrosses();

	bool checkIfWin(unsigned int player);
	char toSymbol(unsigned int x);
	int toInt(char x);
	unsigned int getPlayer();
	void input();
	void switchTurn();
	void win();
	bool isCharValid(char c) const;

private:

	bool isIntValid(unsigned int i) const;
	bool isSlotEmpty(unsigned int x, unsigned int y) const;
	char playerToken;
	unsigned int player;
	int h_2DArray[3][3];
	void drawBoard();
	template<typename T>
	void readInput(const std::string & prefix, T & input);

};

template<typename T>
inline void NaughtsNCrosses::readInput(const std::string & prefix, T & input)
{
		std::cout << prefix;

		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> input;
}