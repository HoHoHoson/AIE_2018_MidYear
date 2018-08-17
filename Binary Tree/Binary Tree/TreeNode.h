#pragma once
#include "TreeEdge.h"


template<typename T>
class TreeNode
{
public:
	TreeNode(T value);
	TreeNode();

	T getData();
	TreeNode<T>* getLeftNode();
	TreeNode<T>* getRightNode();
	void setData(T value);
	void setLeftEdge(TreeNode<T>* toNode, float cost = 1.0f);
	void setRightEdge(TreeNode<T>* toNode, float cost = 1.0f);
	void listEdges();

private:
	T m_Data;
	TreeEdge<T> m_Lefty;
	TreeEdge<T> m_Righty;
};


template<typename T>
inline TreeNode<T>::TreeNode(T value)
{
	m_Data = value;
}

template<typename T>
inline TreeNode<T>::TreeNode()
{
	for (auto& eachEdge : m_EdgeArray)
	{
		delete eachEdge;
	}
}

template<typename T>
inline T TreeNode<T>::getData()
{
	return m_Data;
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::getLeftNode()
{
	return m_Lefty.m_ToNode;
}

template<typename T>
inline void TreeNode<T>::setLeftEdge(TreeNode<T>* toNode, float cost)
{
	m_Lefty.m_ToNode = toNode;
	m_Lefty.m_Cost = cost;
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::getRightNode()
{
	return m_Righty.m_ToNode;
}

template<typename T>
inline void TreeNode<T>::setRightEdge(TreeNode<T>* toNode, float cost)
{
	m_Righty.m_ToNode = toNode;
	m_Righty.m_Cost = cost;
}

template<typename T>
inline void TreeNode<T>::setData(T value)
{
	m_Data = value;
}

template<typename T>
inline void TreeNode<T>::listEdges()
{
	std::cout << "Links " << std::setw(3) << "> ";
	if (m_EdgeArray.size() != 0)
	{
		for (auto eachEdge : m_EdgeArray)
		{
			auto temp = eachEdge->m_toNode;
			std::cout << temp->getData() << "   ";
		}
	}
	else
		std::cout << "None";
}
