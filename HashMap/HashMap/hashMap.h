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
static unsigned int calculateHash(const T& value)
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


	void addValue(const keyType& key, const valueType& value)
	{
		unsigned int hash = calculateHash(key);
		hash = hash % size;
		pair p;
		p.key = key;
		p.value = value;
		m_Data[hash].push_back(p);
	}


	void removeValue(keyType key)
	{
		unsigned int hash = calculateHash(key);
		hash = hash % size;

		assert(!m_Data[hash].empty() && "Can't find specified key");

		auto it = m_Data[hash].begin();
		do
		{
			if (it->key == key)
			{
				//moves the iterator forward (++i built in) after deleting the object. Therefore, DON'T CALL ++i again or you'll skip some objects!
				it = m_Data[hash].erase(it);

				std::cout << "\n'" << key << "' has been removed\n";
			}
			else
				++it;

		} while (it != m_Data[hash].end());
	}


	void clearAll()
	{
		for (size_t i = 0; i < size; ++i)
		{
			if (!m_Data[i].empty())
				m_Data[i].clear();
		}
	}


	void display()
	{
		bool isEmpty = true;

		std::cout << "\nDISPLAY HASH TABLE\n";

		for (auto i : m_Data)
			if (!i.empty())
			{
				isEmpty = false;
				for (auto pair : i)
					std::cout << "{" << pair.key << "} = " << pair.value << std::endl;	
			}
		if (isEmpty)
			std::cout << "Hash table is empty :(\n";
	}


	hashMap operator[](keyType key)
	{
		unsigned int hash = calculateHash(key);
		hash = hash % size;

		for (auto read : this->m_Data[hash])
		{
			std::cout << "\n[" << read.key << "] = " << read.value << std::endl;
		}

		return *this;
	}

private:
	std::list<pair> m_Data[size];
};


template<>
static unsigned int calculateHash(const std::string& value)
{
	return calculateHash(value.data(), value.size());
}

template<>
static unsigned int calculateHash(const int& value)
{
	return calculateHash((const char*)&value, sizeof(int));
}