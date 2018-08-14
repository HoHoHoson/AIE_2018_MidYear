#pragma once


template<typename T>
class TreeNode;

template<typename T>
struct TreeEdge
{
	TreeEdge(TreeNode<T>* connectedNode, float cost)
	{
		m_cost = cost;
		m_toNode = connectedNode;
	}

	float m_cost;
	TreeNode<T>* m_toNode;
};