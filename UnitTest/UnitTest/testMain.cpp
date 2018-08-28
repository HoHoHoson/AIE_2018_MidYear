#include "Vector3.h"
#include "Vector4.h"
#include "Vector2.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

int main() 
{
	Vector4 v1(3, 3, 3, 3);
	v1.normalise();
	Vector4 v2 = v1;
	float* draw = v2.data;
	Vector2 v2a(2, 1);
	Vector2 v2b(2, 2);
	Vector4 v3a(1, 0, 0);
	Vector4 v3b(0, 1, 0);

	for (size_t i = 0; i < 1; ++i)
		std::cout << v2a.getDegrees(v2b) << std::endl;

	system("pause");
	return 0;
}