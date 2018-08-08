#include "LinkedList.h"


int main()
{
	LinkedList<float> myList;

	std::cout << "[Push both Back/Front with the values 0-4]\n";
	for (size_t i = 0; i < 5; ++i)
	{
		myList.pushFront(i);
		myList.pushBack(i);
	}
	myList.displayList();

	std::cout << "\n[Inserted '69.5' at the 10th position]\n";
	myList.insertAt(10, 69.5f);
	myList.displayList();

	std::cout << "\n[Removed the 11th value]\n";
	myList.eraseAt(11);
	myList.displayList();

	std::cout << "\n[Removed all values that are equal to 0]\n";
	myList.removeAny(0);
	myList.displayList();

	std::cout << "\n[Get both the first and last value]\n";
	myList.getFirst();
	myList.getLast();

	std::cout << "\n[Popped both the front and back off]\n";
	myList.popFront();
	myList.popBack();
	myList.displayList();

	std::cout << "\n[Cleared the linked list]\n";
	myList.clearList();
	myList.displayList();


	std::cout << "\n";
	system("pause");
	return 0;
}