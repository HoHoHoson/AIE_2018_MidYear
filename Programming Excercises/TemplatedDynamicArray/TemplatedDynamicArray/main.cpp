#include "DynamicArray.h"


int main()
{
	TDynamicArray<int> tArr;
	TDynamicArray<int> baaar;
	srand((unsigned int)time(nullptr));

	for (int i = 0; i < 15; ++i)
	{
		tArr.pushBack(rand() % 20 + 1);
	}
	for (int i = 0; i < 10; ++i)
	{
		baaar.pushBack(rand() % 20 + 1);
	}
	//tArr.insertAt(0, 69);
	//tArr.removeAt(0);
	//tArr.clearArray();
	//tArr.bubbleSort();
	//tArr.searchArray(20);
	std::cout << "tArr Array\n";
	tArr.displayArray();
	std::cout << "baaar Array\n";
	baaar.displayArray();

	std::cout << "tArr + baaar\n";
	//TDynamicArray<int> plus(tArr, baaar);
	tArr + baaar;
	tArr.displayArray();

	system("pause");
	return 0;
}