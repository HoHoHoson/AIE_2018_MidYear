
#include "dynamicArray.h"


int main()
{
	DynamicArray ray;

	for (int i = 0; i < 12; ++i)
	{
		ray.pushBack(i);
	}

	ray.removeAt(1);
	ray.insertAt(3, 33);

	ray.drawArray();
	std::cout << "Number of values: " << ray.getCurrentSize() << std::endl;
	std::cout << "Max Array Capacity: " << ray.getMaxSize() << std::endl;
	std::cout << "Get value at index 3: " << ray.getAt(3) << std::endl;

	std::cout << std::endl;
	system("pause");
	return 0;
}