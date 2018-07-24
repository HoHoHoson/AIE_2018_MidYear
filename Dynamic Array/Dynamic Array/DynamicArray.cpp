#include "DynamicArray.h"
#include <cassert>

DynamicArray::DynamicArray()
{
	m_maxSize = 10;
	m_contents = new int[m_maxSize];

}

DynamicArray::~DynamicArray()
{
	delete[] m_contents;
}

bool DynamicArray::isFull() const
{
	return (m_currentSize >= m_maxSize);
}

void DynamicArray::pushBack(int value)
{
	if (isFull())
	{
		resizeArray(m_maxSize * 2);
	}

	m_contents[m_currentSize] = value;
	m_currentSize++;

}

void DynamicArray::popBack()
{
	if (m_currentSize > 0)
	{
		m_currentSize--;
	}
}

int DynamicArray::getAt(unsigned int index) const
{
	assert(isValidIndex(index) && "Invalid index provided");
	return m_contents[index];
}

void DynamicArray::insertAt(unsigned int index, int value)
{
	assert(isValidIndex(index) && "Invalid index provided");

	if (isFull())
	{
		resizeArray(m_maxSize * 2);
	}

	for (unsigned int i = m_currentSize; i > index; --i)
	{
		m_contents[i] = m_contents[i - 1];
	}

	m_contents[index] = value;
}

void DynamicArray::removeAt(unsigned int index)
{
	assert(isValidIndex(index) && "Invalid index provided");

	for (unsigned int i = index; i < m_currentSize; ++i)
	{
		m_contents[i] = m_contents[i + 1];
	}

	m_currentSize--;


}


void DynamicArray::resizeArray(unsigned int newMaxAmount)
{
	int* newArray = new int[newMaxAmount];

	for (unsigned int i = 0; i < m_currentSize && i < newMaxAmount; i++)
	{
		newArray[i] = m_contents[i];
	}

	delete[] m_contents;
	m_contents = newArray;

	m_maxSize = newMaxAmount;
	if (m_currentSize > m_maxSize)
	{
		m_currentSize = m_maxSize;
	}
}


bool DynamicArray::isValidIndex(unsigned int index) const
{
	return (index < m_currentSize);
}

int DynamicArray::getAmount() const
{
	return m_currentSize;
}

void DynamicArray::drawArray()
{
	for (int i = 0; i < m_currentSize; ++i)
	{
		std::cout << m_contents[i] << std::endl;
	}
	std::cout << getAt(2);
}
