#pragma once
#include "animals.h"

class Chickpea : public Animals
{
public:
	std::string getType() override;
	std::string acapella() override;
	void playSound();
};


class Chicken : public Animals
{
public:
	std::string getType() override;
	std::string acapella() override;
	void playSound();
};


class Chickadee : public Animals
{
public:
	std::string getType() override;
	std::string acapella() override;
	void playSound();
};