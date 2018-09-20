#pragma once

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>

class BitSet
{
public:
	BitSet();
	~BitSet();

	void setBit(const unsigned int& value);

	void printValues()
	{
		std::cout << "\n[Print as Binary]\n";

		for (int i = 7; i >= 0; --i)
		{
			const int mask = 0x01 << i;
			int its = *m_BitSet.at(0);
			if ((i & mask) == mask)
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

private:

	std::vector<int*> m_BitSet;
	const int m_BitsPerSet = 32;

	unsigned int m_MaxSize;
	unsigned int m_Size;
	
	void shouldExpand(const unsigned int& value);
};