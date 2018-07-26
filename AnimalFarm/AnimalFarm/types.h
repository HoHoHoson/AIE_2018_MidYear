#pragma once
#include "animals.h"

class Chickpea : public Animals
{
public:
	std::string getType() override;
	void playSound();
	
};


class Chicken : public Animals
{
public:
	std::string getType() override;
	void playSound();
};


class Chickadee : public Animals
{
public:
	std::string getType() override;
	void playSound();
};