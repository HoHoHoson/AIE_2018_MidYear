#pragma once
#include <iostream>

class DynamicArray
{
public:
	DynamicArray();
	~DynamicArray();

	int getAmount() const;
	bool isFull() const;

	void pushBack(int value);
	void popBack(); //Removes the current last pushed value in the array

	int getAt(unsigned int index) const; // get the value at the given index

	void insertAt(unsigned int index, int value); 
	//Insert the given value at the given index
	/*
	eg:
	Before: 0, 1, 2, 3
	insertAt(2, 20);
	After : 0, 1, 20, 2, 3
	*/

	void removeAt(unsigned int index); 
	//Remove the value at the given index
	/*
	eg:
	Before: 0, 1, 2, 3
	removeAt(2);
	After: 0, 1, 3
	*/

	void drawArray();

private:
	void resizeArray(unsigned int newMaxAmount);
	bool isValidIndex(unsigned int index) const;
	unsigned int m_currentSize = 0;
	unsigned int m_maxSize;
	int* m_contents;

};
