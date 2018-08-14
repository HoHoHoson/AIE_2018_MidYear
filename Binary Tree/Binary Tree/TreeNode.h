#pragma once
#include <vector>
#include "TreeEdge.h"


template<typename T>
class TreeNode
{
public:
	TreeNode(T value);
	TreeNode();

	T getData();
	void setData(T value);
	void addEdge(TreeNode<T>* connectedNode, float cost = 1.0f);
	void listEdges();

private:
	T m_data;
	TreeEdge<T>* m_Lefty;
	TreeEdge<T>* m_Righty;

	std::vector<TreeEdge<T>*> m_edgeArray;
};


template<typename T>
inline TreeNode<T>::TreeNode(T value)
{
	m_data = value;
	m_Lefty = nullptr;
	m_Righty = nullptr;
}

template<typename T>
inline TreeNode<T>::TreeNode()
{
	for (auto& eachEdge : m_edgeArray)
	{
		delete eachEdge;
	}
}

template<typename T>
inline T TreeNode<T>::getData()
{
	return m_data;
}

template<typename T>
inline void TreeNode<T>::setData(T value)
{
	m_data = value;
}

template<typename T>
inline void TreeNode<T>::addEdge(TreeNode<T>* toNode, float cost)
{
	TreeEdge<T>* newEdge = new TreeEdge<T>(toNode, cost);
	m_edgeArray.push_back(newEdge);
}

template<typename T>
inline void TreeNode<T>::listEdges()
{
	std::cout << "Links " << std::setw(3) << "> ";
	if (m_edgeArray.size() != 0)
	{
		for (auto eachEdge : m_edgeArray)
		{
			auto temp = eachEdge->m_toNode;
			std::cout << temp->getData() << "   ";
		}
	}
	else
		std::cout << "None";
}
