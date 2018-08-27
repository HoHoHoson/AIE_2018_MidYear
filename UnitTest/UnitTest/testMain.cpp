#include "Vector3.h"
#include "Vector4.h"
#include "Vector2.h"
#include <iostream>

int main() 
{
	Vector2 v1(0);
	float* vOne = v1;
	Vector2 v2(1, 1);
	Vector2 v3(9, 9);
	v1 = v3 / 9;

	for (size_t i = 0; i < 2; ++i)
		std::cout << vOne[i] << std::endl;


	system("pause");
	return 0;
}