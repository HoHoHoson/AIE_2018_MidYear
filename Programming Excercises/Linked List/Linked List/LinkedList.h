#pragma once
#include <iostream>

struct Node
{
	int data;
	Node* nextNode;
	Node* previousNode;
};


class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	void begin();
	bool end();
	void pushFront(int value);
	void popFront();
	void pushBack(int value);
	void popBack();
	void getFirst();
	void getLast();
	void insertTo(unsigned int pos, int value);
	void eraseAt(unsigned int pos);
	void totalValues();
	void displayList();
	void removeAny(int value);
	void clearList();

private:
	
	Node* head;
	Node* tail;
	Node* iterator;
	bool isEmpty() const;
	int data;
	unsigned int valueCount;
	void initialiseNode(Node*& newNode, int& value);

};
