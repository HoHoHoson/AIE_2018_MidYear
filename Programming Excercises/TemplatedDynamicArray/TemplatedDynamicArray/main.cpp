#include "DynamicArray.h"


int main()
{
	srand((unsigned int)time(nullptr));

	using std::cout;
	using std::endl;

	TDynamicArray<float> arr;
	TDynamicArray<float> meHaarty;

	cout << "\nPushing back 15 random values (ranging from 1-20) into the 'arr' Array\n\n";
	for (int i = 0; i < 15; ++i)
	{
		arr.pushBack(rand() % 20 + 1);
	}
	arr.displayArray();
	cout << "\n\n";

	cout << "\nInserted '6.6' into Index 9\n\n";
	arr.insertAt(9, 6.6);
	arr.displayArray();
	cout << "\n\n";

	cout << "\nRemoved the value at Index 6\n\n";
	arr.removeAt(6);
	arr.displayArray();
	cout << "\n\n";

	cout << "\nCreated a second Array 'meHaarty' with 10 random values (ranging from 1-20)\n\n";
	for (int i = 0; i < 10; ++i)
	{
		meHaarty.pushBack(rand() % 20 + 1);
	}
	meHaarty.displayArray();
	cout << "\n\n";

	cout << "\nCombined 'meHaarty' onto 'arr'\n\n";
	arr + meHaarty;
	arr.displayArray();
	cout << "\n\n";

	cout << "\nPopped back 'arrMeHaarty'\n\n";
	arr.popBack();
	arr.displayArray();
	cout << "\n\n";

	cout << "\nSearch for any '20' in 'arrMeHaarty'\n\n";
	arr.searchArray(20);
	cout << "\n\n";

	cout << "\nBubbleSort 'arrMeHaarty'\n\n";
	arr.bubbleSort();
	arr.displayArray();
	cout << "\n\n";

	cout << "\nCompletely cleared 'arrMeHaarty'\n\n";
	arr.clearArray();
	arr.displayArray();
	cout << "\n\n";


	system("pause");
	return 0;
}