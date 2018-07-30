#include <iostream>

int main()
{
	int arr[7] = { 2, 4, 7, 1, 6, 9, 4 };
	bool swapped = false;

	do
	{
		swapped = false;
		for (int i = 0; i < 6; ++i)
		{
			int temp;
			if (arr[i] > arr[i + 1])
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = true;
			}
		}
	} while (swapped);

	for (int i = 0; i < 6; ++i)
	{
		std::cout << arr[i] << std::endl;
	}

	system("pause");
	return 0;
}