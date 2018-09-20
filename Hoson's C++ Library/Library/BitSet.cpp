#include "BitSet.h"

BitSet::BitSet()
{
	int i = 0;
	m_BitSet.push_back(&i);
	m_MaxSize = m_BitsPerSet;
	m_Size = 0;
}

BitSet::~BitSet()
{
}

void BitSet::setBit(const unsigned int & value)
{
	shouldExpand(value);
	unsigned int setNum = value / m_BitsPerSet;
	const unsigned int bitMask = 0x01 << (value % m_BitsPerSet);

	m_BitSet.at(setNum) & bitMask;
}

void BitSet::shouldExpand(const unsigned int& value)
{
	while (value > m_MaxSize)
	{
		m_BitSet.push_back(new int);
		m_MaxSize += m_BitsPerSet;
	}
}
