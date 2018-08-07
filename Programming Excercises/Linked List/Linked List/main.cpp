#include "LinkedList.h"


int main()
{
	LinkedList myList;

	for (size_t i = 0; i < 5; ++i)
	{
		myList.pushFront(i);
		myList.pushBack(i);
	}
	myList.displayList();
	myList.insertTo(4, 69);
	myList.displayList();


	std::cout << "\n";
	system("pause");
	return 0;
}