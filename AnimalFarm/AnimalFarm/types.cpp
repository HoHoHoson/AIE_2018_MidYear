#pragma once
#include "types.h"

void Chickpea::playSound() 
{
	std::cout << "The Chickpea says, Chickapeea\n";
}

std::string Chickpea::getType()
{
	return "Chickpea";
}

std::string Chicken::getType()
{
	return "Chicken";
}

void Chicken::playSound()
{
	std::cout << "The Chicken says, Cluck\n";
}

std::string Chickadee::getType()
{
	return "Chickadee";
}

void Chickadee::playSound()
{
	std::cout << "The Chickadee says, Chicka Dee Dee Deeee\n";
}
