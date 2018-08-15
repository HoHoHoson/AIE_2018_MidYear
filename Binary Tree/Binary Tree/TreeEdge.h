#pragma once


template<typename T>
class TreeNode;

template<typename T>
struct TreeEdge
{
	TreeEdge()
	{
		m_Cost = 1.0f;
		m_ToNode = nullptr;
	}

	float m_Cost;
	TreeNode<T>* m_ToNode;
};