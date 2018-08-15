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

private:
	TreeNode<T>* m_RootNode;
	TreeNode<T>* m_Iterator;
	size_t m_TreeDepth;

	bool m_IsEmpty();
	auto m_BufferWidth(size_t height, size_t setWidth);
	auto m_SpacingWidth(size_t height, size_t setWidth);
};


template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	m_RootNode = nullptr;
	m_TreeDepth = 0;
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

	int depthCount = 0;
	m_Iterator = m_RootNode;

	while (true)
	{
		if (m_Iterator->getData() == value)
		{
			std::cout << "Tree already contains a '" << value << "'\n";
			return;
		}

		depthCount++;

		if (value < m_Iterator->getData())
			if (m_Iterator->getLeftNode() == nullptr)
			{
				TreeNode<T>* newNode = new TreeNode<T>(value);
				m_Iterator->setLeftEdge(newNode);
				break;
			}
			else
				m_Iterator = m_Iterator->getLeftNode();

		if (value > m_Iterator->getData())
			if (m_Iterator->getRightNode() == nullptr)
			{
				TreeNode<T>* newNode = new TreeNode<T>(value);
				m_Iterator->setRightEdge(newNode);
				break;
			}
			else
				m_Iterator = m_Iterator->getRightNode();
	}

	if (depthCount > m_TreeDepth)
		m_TreeDepth = depthCount;
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
		std::cout << "Here is an upside down tree\n";

	int heightCount = m_TreeDepth;
	size_t setWidth = 4;

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

