#pragma once
#include <iostream>

class Position
{
public:
	Position();

	void getValues();
	bool operator==(const Position& pos) const;
	bool operator!=(const Position& pos) const;
	Position operator=(const Position& pos);
	Position operator+(const Position& pos2);
	Position operator-(const Position& pos2);
	Position operator+=(const int iVar);
	Position operator-=(const int iVar);

private:

	float x;
	float y;

};