#pragma once
#include <list>
#include <string>
#include <cassert>


static unsigned int calculateHash(const char* data, unsigned int size = 0)
{
	unsigned int hash = 0;

	for (unsigned int i = 0; i < size; ++i)
	{
		hash = (hash * 1313) + data[i];
	}

	hash = hash & 0X7FFFFFFF;

	return hash;
}

template<typename T>
unsigned int calculateHash(const T& value)
{
	assert(false && "No hash function for this type");
	return 0;
}


template<int size, typename keyType, typename valueType>
class hashMap
{
	struct pair
	{
		keyType key;
		valueType value;
	};

public:
	void addValue(keyType key, valueType value)
	{
		unsigned int hash = calculateHash(key);
		hash = hash % size;
		pair p;
		p.key = key;
		p.value = value;
		m_Data[hash].push_back(p);
	}

private:
	/*unsigned int calculateHash(keyType key)
	{
		unsigned int hash = 0;

		unsigned char* data = (unsigned char*)&key;
		unsigned int dataSize = sizeof(keyType);

		return hash;
	}*/
	std::list<pair> m_Data[size];
};


template<>
unsigned int calculateHash(const std::string& value)
{
	return calculateHash(value.data(), value.size());
}

template<>
unsigned int calculateHash(const int& value)
{
	return calculateHash((const char*)&value, sizeof(int));
}