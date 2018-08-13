#include "LinkedList.h"


template<typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	iterator = nullptr;
	valueCount = 0;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
}

template<typename T>
void LinkedList<T>::begin()
{
	iterator = head;
}

template<typename T>
bool LinkedList<T>::end()
{
	return (iterator == nullptr);
}

template<typename T>
void LinkedList<T>::pushFront(T value)
{
	Node<T>* newNode = new Node<T>;
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

template<typename T>
void LinkedList<T>::popFront()
{
	Node<T>* deleteThis = head;
	head = head->nextNode;
	head->previousNode = nullptr;
	delete deleteThis;
	begin();
	valueCount--;
}

template<typename T>
void LinkedList<T>::pushBack(T value)
{
	Node<T>* newNode = new Node<T>;
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

template<typename T>
void LinkedList<T>::popBack()
{
	Node<T>* deleteThis = tail;
	tail = tail->previousNode;
	tail->nextNode = nullptr;
	delete deleteThis;
	valueCount--;
}

template<typename T>
void LinkedList<T>::getFirst()
{
	std::cout << "\nHead Value = " << head->data << std::endl;
}

template<typename T>
void LinkedList<T>::getLast()
{
	std::cout << "\nTail Value = " << tail->data << std::endl;
}

template<typename T>
void LinkedList<T>::insertAt(unsigned int pos, T value)
{
	if (pos == 1)
	{
		pushFront(value);
		return;
	}

	Node<T>* newNode = new Node<T>;
	initialiseNode(newNode, value);
	Node<T>* temp = nullptr;

	begin();
	for (size_t i = 1; i < pos; ++i)
	{
		if (i == pos - 1)
		{
			temp = iterator;
			newNode->previousNode = temp;
		}
		iterator = iterator->nextNode;
	}
	newNode->nextNode = iterator;
	temp->nextNode = newNode;
	iterator->previousNode = newNode;

	valueCount++;
}

template<typename T>
void LinkedList<T>::eraseAt(unsigned int pos)
{
	if (pos == 1)
	{
		popFront();
		return;
	}
	if (pos == valueCount)
	{
		popBack();
		return;
	}

	Node<T>* deleteThis = nullptr;

	begin();
	for (size_t i = 1; i < pos; ++i)
	{
		if (i == pos - 1)
		{
			deleteThis = iterator->nextNode;
			iterator->nextNode = deleteThis->nextNode;
		}
		iterator = iterator->nextNode;
	}
	iterator->previousNode = deleteThis->previousNode;
	delete deleteThis;

	valueCount--;
}

template<typename T>
void LinkedList<T>::totalValues()
{
	std::cout << "\n\tObjects Stored: " << valueCount << std::endl;
}

template<typename T>
void LinkedList<T>::displayList()
{
	Node<T>* temp = head;
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

template<typename T>
void LinkedList<T>::removeAny(T value)
{
	Node<T>* temp;

	begin();
	while (!end())
	{
		temp = nullptr;

		if (head->data == value)
		{
			popFront();
			break;
		}
		if (tail->data == value)
		{
			popBack();
			break;
		}

		if (iterator->data == value)
		{
			temp = iterator->previousNode;
			temp->nextNode = iterator->nextNode;
			temp = iterator->nextNode;
			temp->previousNode = iterator->previousNode;
			temp = iterator;
			valueCount--;
		}

		iterator = iterator->nextNode;

		if (temp != nullptr)
			delete temp;
	}
}

template<typename T>
void LinkedList<T>::clearList()
{
	Node<T>* temp;
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

template<typename T>
bool LinkedList<T>::isEmpty() const
{
	return (head == nullptr && tail == nullptr);
}

template<typename T>
void LinkedList<T>::initialiseNode(Node<T>*& newNode, T& value)
{
	newNode->data = value;
	newNode->nextNode = nullptr;
	newNode->previousNode = nullptr;
}


//Add a new "template class LinkedList< TYPE >;" for every new type of Linked List
template class LinkedList<int>;
template class LinkedList<float>;