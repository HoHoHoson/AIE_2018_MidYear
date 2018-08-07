#include "LinkedList.h"

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	iterator = nullptr;
	valueCount = 0;
}

LinkedList::~LinkedList()
{
}

void LinkedList::begin()
{
	iterator = head;
}

bool LinkedList::end()
{
	return (iterator == nullptr);
}

void LinkedList::pushFront(int value)
{
	Node* newNode = new Node;
	initialiseNode(newNode, value);

	if (isEmpty())
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		head->previousNode = newNode;
		newNode->nextNode = head;
		head = newNode;
	}
	valueCount++;
}

void LinkedList::popFront()
{
	Node* deleteThis = head;
	head = head->nextNode;
	head->previousNode = nullptr;
	delete deleteThis;
	valueCount--;
}

void LinkedList::pushBack(int value)
{
	Node* newNode = new Node;
	initialiseNode(newNode, value);

	if (isEmpty())
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->nextNode = newNode;
		newNode->previousNode = tail;
		tail = newNode;
	}
	valueCount++;
}

void LinkedList::popBack()
{
	Node* deleteThis = tail;
	tail = tail->previousNode;
	tail->nextNode = nullptr;
	delete deleteThis;
	valueCount--;
}

void LinkedList::getFirst()
{
	std::cout << "\nHead Value = " << head->data << std::endl;
}

void LinkedList::getLast()
{
	std::cout << "\nTail Value = " << tail->data << std::endl;
}

void LinkedList::insertTo(unsigned int pos, int value)
{
	Node* newNode = new Node;
	initialiseNode(newNode, value);

	begin();
	for (size_t i = 1; i < pos; ++i)
	{
		if (i == pos - 1)
		{
			newNode->previousNode = iterator;
			iterator->nextNode = newNode;
		}
		iterator = iterator->nextNode;
	}
	newNode->nextNode = iterator;
	iterator->previousNode = newNode;
}

void LinkedList::totalValues()
{
	std::cout << "\n\tObjects Stored: " << valueCount << std::endl;
}

void LinkedList::displayList()
{
	Node* temp = head;
	std::cout << "\n\t";
	while (temp != nullptr)
	{
		if (temp->nextNode == nullptr)
			std::cout << temp->data;
		else
			std::cout << temp->data << " | ";
		
		temp = temp->nextNode;
	}
	std::cout << "\n";
	totalValues();
}

void LinkedList::clearList()
{
	Node* temp;
	while (!isEmpty())
	{
		temp = head;
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
		}
		else
			head = head->nextNode;
		delete temp;
	}
	valueCount = 0;
}

bool LinkedList::isEmpty() const
{
	return (head == nullptr || tail == nullptr);
}

void LinkedList::initialiseNode(Node*& newNode, int& value)
{
	newNode->data = value;
	newNode->nextNode = nullptr;
	newNode->previousNode = nullptr;
}
