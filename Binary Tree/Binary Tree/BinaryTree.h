#pragma once
#include <iostream>
#include <iomanip>
#include "TreeNode.h"
#include "TreeEdge.h"


template<typename T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	void addNode(T value);
	void linkNodes(size_t fromNode, size_t toNode, float cost = 1.0f);
	void drawTree();

private:
	TreeNode<T>* m_rootNode;
	TreeNode<T>* m_iterator;
	size_t m_treeDepth;

	bool isEmpty();

	std::vector<TreeNode<T>*> m_nodeList;

};


template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	m_rootNode = nullptr;
	m_treeDepth = 0;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
}

template<typename T>
inline void BinaryTree<T>::addNode(T value)
{
	if (isEmpty())
	{
		m_rootNode = newNode;
		return;
	}

	int depthCount = 0;
	m_iterator = m_rootNode;
	while (true)
	{
		if (m_iterator->m_data == value)
		{
			std::cout << "Tree already contains a '" << value << "'";
			return;
		}

		depthCount++;
		if (value < m_iterator->m_data)
			if (m_iterator->m_Lefty == nullptr)
			{
				m_iterator->m_Lefty = new TreeNode<T>(value);
				break;
			}
			else
				m_iterator = m_iterator->m_Lefty;

		if (value > m_iterator->m_data)
			if (m_iterator->m_Righty == nullptr)
			{
				m_iterator->m_Righty = new TreeNode<T>(value);
				break;
			}
			else
				m_iterator = m_iterator->m_Righty;
	}

	if (depthCount > m_treeDepth)
		m_treeDepth = depthCount;
}

template<typename T>
inline void BinaryTree<T>::linkNodes(size_t fromNode, size_t toNode, float cost)
{
	m_nodeList.at(fromNode)->addEdge(m_nodeList.at(toNode), cost);
}

template<typename T>
inline void BinaryTree<T>::drawTree()
{
	size_t counter = 0;
	std::cout << "List Nodes\n\n";
	for (auto& eachNode : m_nodeList)
	{
		std::cout << "Node " << counter << std::setw(3) << " > " << eachNode->getData() << std::endl;
		counter++;
		eachNode->listEdges();
		std::cout << "\n\n";
	}
}

template<typename T>
inline bool BinaryTree<T>::isEmpty()
{
	return (m_rootNode == nullptr);
}

