#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
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
	void removeNode(T value);
	void searchFor(T value);
	void clear();
	void drawTree();

private:
	TreeNode<T>* m_RootNode;
	TreeNode<T>* m_Iterator;
	size_t m_TreeDepth;
	size_t m_IteratorDepth;
	bool m_ItWentLeft;

	bool m_IsEmpty();
	auto m_BufferWidth(size_t height, size_t setWidth);
	auto m_SpacingWidth(size_t height, size_t setWidth);

	void begin();
	TreeNode<T>* setupIterators(T value);
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

	setupIterators(value);

	if (m_Iterator->getData() == value)
		std::cout << "\nTree already contains a '" << value << "'\n";
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
		std::cout << "\nThere is nothing to draw, the tree is empty\n";
		return;
	}
	else
		std::cout << "\nDISPLAY TREE\n\n";

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
inline void BinaryTree<T>::removeNode(T value)
{
	TreeNode<T>* previousNode = setupIterators(value);

	if (m_IsEmpty())
	{
		std::cout << "\nYou can't delete nothing!\n";
		return;
	}
	if (m_Iterator->getData() != value)
	{
		std::cout << "\nCan't delete '" << value << "' due to it not existing\n";
		return;
	}

	if (m_Iterator->getLeftNode() == nullptr && m_Iterator->getRightNode() == nullptr)
	{
		delete m_Iterator;
		if (m_ItWentLeft)
			previousNode->setLeftEdge(nullptr);
		else
			previousNode->setRightEdge(nullptr);
	}
	else if (m_Iterator->getLeftNode() != nullptr && m_Iterator->getRightNode() != nullptr)
	{
		previousNode = m_Iterator;
		m_Iterator = m_Iterator->getRightNode();

		while (m_Iterator->getLeftNode() != nullptr)
		{
			m_Iterator = m_Iterator->getLeftNode();
		} 

		int temp = m_Iterator->getData();
		removeNode(m_Iterator->getData());
		previousNode->setData(temp);
	}
	else
	{
		if (m_ItWentLeft && m_Iterator->getRightNode() == nullptr)
			previousNode->setLeftEdge(m_Iterator->getLeftNode());
		else if (m_ItWentLeft && m_Iterator->getLeftNode() == nullptr)
			previousNode->setLeftEdge(m_Iterator->getRightNode());
		else if (m_Iterator->getRightNode() == nullptr)
			previousNode->setRightEdge(m_Iterator->getLeftNode());
		else
			previousNode->setRightEdge(m_Iterator->getRightNode());

		delete m_Iterator;
	}
}

template<typename T>
inline void BinaryTree<T>::searchFor(T value)
{
	TreeNode<T>* previous = setupIterators(value);

	if (m_Iterator->getData() != value)
	{
		std::cout << "\nThe object '" << value << "' doesn't exist!\n";
		return;
	}

	std::cout << "\nNode[" << value << "]\n";

	std::cout << "\nParent:\n";
	if (previous == m_Iterator)
		std::cout << "ROOT NODE\n";
	else if (m_ItWentLeft)
		std::cout << "LEFT node of {" << previous->getData() << "}\n";
	else
		std::cout << "RIGHT node of {" << previous->getData() << "}\n";

	std::cout << "\nChildren:\n";
		if (m_Iterator->getLeftNode() == nullptr && m_Iterator->getRightNode() == nullptr)
			std::cout << "LEAF NODE\n";
		else
		{
			if (m_Iterator->getLeftNode() != nullptr)
				std::cout << "Left {" << m_Iterator->getLeftNode()->getData() << "}\n";
			else
				std::cout << "Left {NONE}\n";

			if (m_Iterator->getRightNode() != nullptr)
				std::cout << "Right {" << m_Iterator->getRightNode()->getData() << "}\n";
			else
				std::cout << "Right {NONE}\n";
		}

}

template<typename T>
inline void BinaryTree<T>::clear()
{
	bool wentLeft = true;
	TreeNode<T>* prev = nullptr;

	while (!m_IsEmpty())
	{
		begin();
		
		while (true)
		{
			if (m_Iterator->getLeftNode() != nullptr)
			{
				prev = m_Iterator;
				m_Iterator = m_Iterator->getLeftNode();
				wentLeft = true;
			}
			else if (m_Iterator->getRightNode() != nullptr)
			{
				prev = m_Iterator;
				m_Iterator = m_Iterator->getRightNode();
				wentLeft = false;
			}
			else
			{
				if (m_Iterator == m_RootNode)
					m_RootNode = nullptr;

				delete m_Iterator;

				if (wentLeft && !m_IsEmpty())
					prev->setLeftEdge(nullptr);
				else
					prev->setRightEdge(nullptr);
				break;
			}
		}
	}
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
	m_ItWentLeft = true;
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::setupIterators(T value)
{
	begin();

	TreeNode<T>* prev = m_Iterator;

	while (true)
	{
		if (m_Iterator->getData() == value)
			break;

		if (value < m_Iterator->getData())
			if (m_Iterator->getLeftNode() == nullptr)
				break;
			else
			{
				m_ItWentLeft = true;
				prev = m_Iterator;
				m_Iterator = m_Iterator->getLeftNode();
				m_IteratorDepth++;
			}

		else if (value > m_Iterator->getData())
			if (m_Iterator->getRightNode() == nullptr)
				break;			
			else
			{
				m_ItWentLeft = false;
				prev = m_Iterator;
				m_Iterator = m_Iterator->getRightNode();
				m_IteratorDepth++;
			}
	}
	
	return prev;
}

