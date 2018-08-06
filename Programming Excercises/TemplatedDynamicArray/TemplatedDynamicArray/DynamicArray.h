#pragma once
#include <iostream>
#include <ctime>
#include <random>


template<typename T>
class TDynamicArray
{
public:
	TDynamicArray();
	TDynamicArray(const TDynamicArray& copy);
	TDynamicArray(const TDynamicArray & original, const TDynamicArray & other);
	~TDynamicArray();
	
	TDynamicArray& operator=(const TDynamicArray& other);
	TDynamicArray& operator+(const TDynamicArray& other);
	void pushBack(const T value);
	void popBack();
	void insertAt(const size_t index, const T value);
	void removeAt(const size_t index);
	void resizeArray(size_t newMaxSize);
	void bubbleSort();
	void searchArray(const T value);
	void clearArray();
	void displayArray();

private:
	bool isFull();
	bool canDownsize();
	size_t h_currentSize = 0;
	size_t h_maxSize = 1;
	T* h_contents;
};


//Default Constructor
template<typename T>
TDynamicArray<T>::TDynamicArray()
{
	h_maxSize = 10;
	h_contents = new T[h_maxSize]; 
}


//Copy constructor
template<typename T>
TDynamicArray<T>::TDynamicArray(const TDynamicArray & copy)
{
	h_currentSize = copy.h_currentSize;
	h_maxSize = copy.h_maxSize;

	h_contents = new T[h_maxSize];
	for (size_t i = 0; i < h_currentSize; ++i)
	{
		h_contents[i] = copy.h_contents[i];
	}
	//OR
	//memcpy(h_Contents, copy.h_Contents, h_CurrentSize * sizeof[T]);
}

template<typename T>
TDynamicArray<T>::TDynamicArray(const TDynamicArray & original, const TDynamicArray & other)
{
	h_currentSize = original.h_currentSize + other.h_currentSize;
	h_maxSize = original.h_maxSize + other.h_maxSize;
	h_contents = new T[h_maxSize];

	for (size_t i = 0; i < original.h_currentSize; ++i)
	{
		h_contents[i] = original.h_contents[i];
	}
	for (size_t i = 0; i < other.h_currentSize; ++i)
	{
		h_contents[i + original.h_currentSize] = other.h_contents[i];
	}
}	


//Deconstructor
template<typename T>
TDynamicArray<T>::~TDynamicArray()
{
	delete[] h_contents;
}


//Assignment Operator
template<typename T>
TDynamicArray<T>& TDynamicArray<T>::operator=(const TDynamicArray<T>& other)
{
	h_currentSize = other.h_currentSize;
	h_maxSize = other.h_maxSize;

	//delete old data
	delete[] h_contents;
	h_contents = new T[h_maxSize];
	for (size_t i = 0; i < other.h_currentSize; ++i)
	{
		h_contents[i] = other.h_contents[i];
	}

	return *this;
}

template<typename T>
TDynamicArray<T> & TDynamicArray<T>::operator+(const TDynamicArray & other)
{
	h_maxSize += other.h_maxSize;

	T* tempArray = new T[h_maxSize];

	for (size_t i = 0; i < h_currentSize; ++i)
	{
		tempArray[i] = h_contents[i];
	}
	for (size_t i = 0; i < other.h_currentSize; ++i)
	{
		tempArray[i + h_currentSize] = other.h_contents[i];
	}

	h_currentSize += other.h_currentSize;

	delete [] h_contents;
	h_contents = new T[h_maxSize];
	
	for (size_t i = 0; i < h_currentSize; ++i)
	{
		h_contents[i] = tempArray[i];
	}
	delete[] tempArray;

	return *this;
}


template<typename T>
void TDynamicArray<T>::pushBack(const T value)
{
	if (isFull())
	{
		resizeArray(h_maxSize * 2);
	}
	h_contents[h_currentSize] = value;
	h_currentSize++;
}

template<typename T>
void TDynamicArray<T>::popBack()
{
	if (h_currentSize != 0)
	{
		h_contents[h_currentSize] = NULL;
		h_currentSize--;
		if (canDownsize())
		{
			resizeArray(h_maxSize / 2);
		}
	}
}

template<typename T>
void TDynamicArray<T>::insertAt(const size_t index, const T value)
{
	if (isFull())
		resizeArray(h_maxSize * 2);
	for (size_t i = h_currentSize; i > index; --i)
	{
		h_contents[i] = h_contents[i - 1];
	}
	h_contents[index] = value;
	h_currentSize++;
}

template<typename T>
void TDynamicArray<T>::removeAt(const size_t index)
{
	if (canDownsize())
		resizeArray(h_maxSize / 2);
	for (size_t i = index; i < h_currentSize; ++i)
	{
		h_contents[i] = h_contents[i + 1];
	}
	h_currentSize--;
}

template<typename T>
void TDynamicArray<T>::resizeArray(size_t newMaxSize)
{
	h_maxSize = newMaxSize;
	T* temp = new T[h_maxSize];
	for (size_t i = 0; i < h_currentSize || i < h_maxSize; ++i)
	{
		temp[i] = h_contents[i];
	}
	delete[] h_contents;
	h_contents = temp;
}

template<typename T>
void TDynamicArray<T>::bubbleSort()
{
	bool sorted;
	do
	{
		sorted = true;
		for (size_t i = 0; i < h_currentSize - 1; ++i)
		{
			if (h_contents[i] < h_contents[i + 1])
			{
				T temp = h_contents[i];
				h_contents[i] = h_contents[i + 1];
				h_contents[i + 1] = temp;
				sorted = false;
			}
		}
	} while (!sorted);
}

template<typename T>
void TDynamicArray<T>::searchArray(const T value)
{
	for (size_t i = 0; i < h_currentSize; ++i)
	{
		if (h_contents[i] == value)
		{
			std::cout << "Index " << i << " -> " << h_contents[i] << "\n" << std::endl;
		}
	}
}

template<typename T>
void TDynamicArray<T>::clearArray()
{
	for (size_t i = 0; i < h_currentSize; ++i)
	{
		h_contents[i] = NULL;
	}
	h_currentSize = 0;

	do
	{
		resizeArray(h_maxSize / 2);
	} while (canDownsize());
}

template<typename T>
void TDynamicArray<T>::displayArray()
{
	for (int i = 0; i < h_currentSize; ++i)
	{
		std::cout << "Index " << i << " -> " << h_contents[i] << "\n" << std::endl;
	}
}

template<typename T>
bool TDynamicArray<T>::isFull()
{
	return (h_currentSize >= h_maxSize);
}

template<typename T>
bool TDynamicArray<T>::canDownsize()
{
	return (h_currentSize <= h_maxSize / 2 && h_maxSize > 10);
}
