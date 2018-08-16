#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "TreeNode.h"
#include "TreeEdge.h"

using std::left;


template<typename T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	void addNode(T value);
	void drawTree();
	void removeNode(T value);
	void clear();

private:
	TreeNode<T>* m_RootNode;
	TreeNode<T>* m_Iterator;
	size_t m_TreeDepth;
	size_t m_IteratorDepth;

	bool m_IsEmpty();
	auto m_BufferWidth(size_t height, size_t setWidth);
	auto m_SpacingWidth(size_t height, size_t setWidth);

	void begin();
	void setIterator(T value);
};


template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	m_RootNode = nullptr;
	m_TreeDepth = 0;
	begin();
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
}

template<typename T>
inline void BinaryTree<T>::addNode(T value)
{
	if (m_IsEmpty())
	{
		m_RootNode = new TreeNode<T>(value);
		return;
	}

	setIterator(value);

	if (m_Iterator->getData() == value)
		std::cout << "Tree already contains a '" << value << "'\n";
	else if (value < m_Iterator->getData())
	{
		m_Iterator->setLeftEdge(new TreeNode<T>(value));
		m_IteratorDepth++;
	}
	else if (value > m_Iterator->getData())
	{
		m_Iterator->setRightEdge(new TreeNode<T>(value));
		m_IteratorDepth++;
	}

	if (m_IteratorDepth > m_TreeDepth)
		m_TreeDepth = m_IteratorDepth;
}

template<typename T>
inline void BinaryTree<T>::drawTree()
{
	if (m_IsEmpty())
	{
		std::cout << "There is nothing to draw, the tree is empty\n";
		return;
	}
	else
		std::cout << "\nHere is an upside down tree graph\n\n";

	int heightCount = m_TreeDepth;
	size_t setWidth = 2;

	std::vector<TreeNode<T>*> readArray;
	std::vector<TreeNode<T>*> tempArray;

	readArray.push_back(m_RootNode);

	do
	{
		std::cout << m_BufferWidth(heightCount, setWidth) << " ";

		for (auto node : readArray)
		{
			if (node == nullptr)
			{
				std::cout << m_SpacingWidth(heightCount, setWidth) << " ";
				tempArray.push_back(nullptr);
				tempArray.push_back(nullptr);
			}
			else
			{
				std::cout << m_SpacingWidth(heightCount, setWidth) << left << node->getData();

				if (node->getLeftNode() == nullptr)
					tempArray.push_back(nullptr);
				else
					tempArray.push_back(node->getLeftNode());

				if (node->getRightNode() == nullptr)
					tempArray.push_back(nullptr);
				else
					tempArray.push_back(node->getRightNode());
			}
		}
		readArray.clear();

		for (auto copy : tempArray)
			readArray.push_back(copy);
		tempArray.clear();

		heightCount--;
		std::cout << "\n"<< std::endl;

	} while (heightCount >= 0);
}

template<typename T>
inline bool BinaryTree<T>::m_IsEmpty()
{
	return (m_RootNode == nullptr);
}

template<typename T>
inline auto BinaryTree<T>::m_BufferWidth(size_t height, size_t setWidth)
{
	float multiplier = 1.0f;
	int temp = height - 1;
	
	for (int i = 0; i < height; ++i)
	{
		multiplier += 0.5f * pow(2, temp);
		temp--;
	}

	return std::setw(setWidth * multiplier);
}

template<typename T>
inline auto BinaryTree<T>::m_SpacingWidth(size_t height, size_t setWidth)
{
	return std::setw(setWidth * pow(2, height));
}

template<typename T>
inline void BinaryTree<T>::begin()
{
	m_Iterator = m_RootNode;
	m_IteratorDepth = 0;
}

template<typename T>
inline void BinaryTree<T>::setIterator(T value)
{
	begin();

	while (true)
	{
		if (m_Iterator->getData() == value)
			return;

		if (value < m_Iterator->getData())
			if (m_Iterator->getLeftNode() == nullptr)
				break;
			else
			{
				m_Iterator = m_Iterator->getLeftNode();
				m_IteratorDepth++;
			}

		else if (value > m_Iterator->getData())
			if (m_Iterator->getRightNode() == nullptr)
				break;			
			else
			{
				m_Iterator = m_Iterator->getRightNode();
				m_IteratorDepth++;
			}
	}
}

