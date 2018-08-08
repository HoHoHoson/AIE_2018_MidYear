#pragma once
#include <iostream>


template<typename T>
struct Node
{
	T data;
	Node* nextNode;
	Node* previousNode;
};


template<typename T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void pushFront(T value);
	void popFront();
	void pushBack(T value);
	void popBack();
	void getFirst();
	void getLast();
	void insertAt(unsigned int pos, T value);
	void eraseAt(unsigned int pos);
	void displayList();
	void removeAny(T value);
	void clearList();

private:
	
	Node<T>* head;
	Node<T>* tail;
	Node<T>* iterator;
	bool isEmpty() const;
	T data;
	unsigned int valueCount;
	void begin();
	bool end();
	void totalValues();
	void initialiseNode(Node<T>*& newNode, T& value);

};
