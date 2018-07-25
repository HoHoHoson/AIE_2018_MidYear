
#pragma once
#include <iostream>
#include <cassert>


class DynamicArray
{
public:

	DynamicArray();
	~DynamicArray();
	bool isFull() const;
	bool isValid(unsigned int index) const;
	int getCurrentSize() const;
	int getMaxSize() const;
	int getAt(unsigned int index) const;
	void pushBack(int value);
	void popBack();
	void insertAt(unsigned int index, int value);
	void removeAt(unsigned int index);
	void drawArray();

private:

	bool canDownsize() const;
	int* h_Array;
	unsigned int h_MaxSize;
	unsigned int h_CurrentSize;
	void resizeArray(unsigned int newMax);

};