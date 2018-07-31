#include "a.h"

Position::Position()
{
	x = 0;
	y = 0;
}

void Position::getValues()
{
	std::cout << "(" << x << ", " << y << ")\n";
	std::cout << std::endl;
}

bool Position::operator==(const Position& pos) const
{
	return (x == pos.x && y == pos.y);
}

bool Position::operator!=(const Position& pos) const
{
	return !(x == pos.x && y == pos.y);
}

Position Position::operator=(const Position& pos)
{
	x = pos.x;
	y = pos.y;
	return *this;
}

Position Position::operator+(const Position& pos2)
{
	x += pos2.x;
	y += pos2.y;
	return *this;
}

Position Position::operator-(const Position& pos2) 
{
	x -= pos2.x;
	y -= pos2.y;
	return *this;
}

Position Position::operator+=(const int iVar)
{
	x += iVar;
	y += iVar;
	return *this;
}

Position Position::operator-=(const int iVar)
{
	x -= iVar;
	y -= iVar;
	return *this;
}
