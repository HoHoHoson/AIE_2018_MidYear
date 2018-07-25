
#include "dynamicArray.h"


DynamicArray::DynamicArray()
{
	h_MaxSize = 10;
	h_Array = new int[h_MaxSize];
}


DynamicArray::~DynamicArray() 
{
	delete[] h_Array;
}


bool DynamicArray::isFull() const
{
	return (h_CurrentSize >= h_MaxSize);
}


bool DynamicArray::isValid(unsigned int index) const
{
	return (index < h_CurrentSize);
}


int DynamicArray::getCurrentSize() const
{
	return h_CurrentSize;
}


int DynamicArray::getMaxSize() const
{
	return h_MaxSize;
}


int DynamicArray::getAt(unsigned int index) const
{
	return h_Array[index];
}


bool DynamicArray::canDownsize() const
{
	return (h_CurrentSize <= h_MaxSize / 2);
}


void DynamicArray::pushBack(int value)
{
	if (isFull())
		resizeArray(h_MaxSize * 2);

	h_Array[h_CurrentSize] = value;
	h_CurrentSize++;
}


void DynamicArray::popBack()
{
	assert (!(h_CurrentSize == 0) && "Array size can't become any smaller.");

	h_Array[h_CurrentSize] = NULL;
	h_CurrentSize--;

	if (canDownsize())
		resizeArray(h_MaxSize / 2);
	
}


void DynamicArray::insertAt(unsigned int index, int value)
{
	assert(isValid(index) && "Invalid array index.");

	if (isFull())
		resizeArray(h_MaxSize * 2);

	for (int i = h_CurrentSize; i > index; --i)
	{
		h_Array[i] = h_Array[i - 1];
	}

	h_Array[index] = value;
	h_CurrentSize++;
}


void DynamicArray::removeAt(unsigned int index)
{
	assert(isValid(index) && "Invalid array index.");

	for (int i = index; i < h_CurrentSize; ++i)
	{
		h_Array[i] = h_Array[i + 1];
	}
	h_CurrentSize--;
}


void DynamicArray::drawArray()
{
	for (int i = 0; i < h_CurrentSize; ++i)
	{
		std::cout << "Index: " << i << std::endl;
		std::cout << "Value: " << h_Array[i] << std::endl;
		std::cout << std::endl;
	}

}


void DynamicArray::resizeArray(unsigned int newMax)
{
	int* tempArray = new int[newMax];

	for (int i = 0; i < h_CurrentSize && i < newMax; ++i)
	{
		tempArray[i] = h_Array[i];
	}
	delete[] h_Array;
	h_Array = tempArray;

	h_MaxSize = newMax;
	if (h_MaxSize < h_CurrentSize)
		h_CurrentSize = h_MaxSize;
}