#include "DynamicArray.h"

int main()
{
	DynamicArray ray;



	for (int i = 0; i < (7)+1; i++)
	{
		ray.pushBack(i);
	}
	ray.drawArray();

	system("pause");
	return 0;
}