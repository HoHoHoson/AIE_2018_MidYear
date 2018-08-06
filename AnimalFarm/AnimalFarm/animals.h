#pragma once
#include <iostream>
#include <iomanip>
#include <string>


class Animals
{
public:
	~Animals() = default;

	virtual std::string getType() = 0;
	virtual std::string acapella() = 0;
	virtual void playSound() = 0;

protected:
};

