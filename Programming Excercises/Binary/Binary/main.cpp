#include <iostream>
#include <cassert>
#include <cmath>


void printValues(char bitField)
{
	std::cout << "\n[Print as Binary]\n";

	for (int i = 7; i >= 0; --i)
	{
		const char mask = 0x01 << i;
		if ((bitField & mask) == mask)
			std::cout << "1";
		else
			std::cout << "0";
	}

	std::cout << "\n";
}

bool isRightMostBitSet(char bitField)
{
	const char mask = 0x01 << 7;

	if ((bitField & mask) == mask)
		return true;
	else
		return false;
}

bool isLeftMostBitSet(char bitField)
{
	const char mask = 0x01;

	if ((bitField & mask) == mask)
		return true;
	else
		return false;
}

bool isBitSet(char bitField, size_t index)
{
	assert(index >= 0 && index <= 7 && "Invalid bit field index");
	const char mask = 0x01 << index;

	if ((bitField & mask) == mask)
		return true;
	else
		return false;
}

int getRightMostSetBit(char bitField)
{
	int value;

	for (size_t i = 0; i < 8; ++i)
	{
		const char mask = 0x01 << i;
		if ((bitField & mask) == mask)
		{
			value = pow(2, i);
			break;
		}
		else
			value = -1;
	}

	return value;
}

bool isPowerof2(char bitField)
{
	size_t counter = 0;

	for (size_t i = 0; i < 8; ++i)
	{
		const char mask = 0x01 << i;
		if ((bitField & mask) == mask)
			counter++;
	}

	if (counter == 1)
		return true;
	else
		return false;
}

int main()
{
	char bitField = 64;

	printValues(bitField);
	std::cout << getRightMostSetBit(bitField) << std::endl;
	if (isPowerof2(bitField))
		std::cout << "Done\n";


	std::cout << "\n";
	system("pause");
	return 0;
}