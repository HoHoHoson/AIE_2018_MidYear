#include "Vector3.h"
#include "Vector4.h"
#include "Vector2.h"
#include "Matrix2.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

int main() 
{
	Matrix2 m2a(0.7, 0.7, -0.7, 0.7);
	Matrix2 m2b(2, 0, 0, -1);
	Matrix2 m2c;
	Vector2 v2a(1, 1);
	Vector2 test;

	m2c = m2a * m2b;
	test = m2b * v2a;

	// this code is for drawing matrices to the console
	float* draw = m2c;
	size_t numOfVectors = 2;
	size_t sizeOfVectors = 2;
	for (size_t i = 0; i < sizeOfVectors; ++i)
	{
		for (size_t j = 0; j < numOfVectors; ++j)
			std::cout << "  " << draw[i + j * sizeOfVectors] << "  ";
		std::cout << "\n";
	}


	std::cout << "\n";
	system("pause");
	return 0;
}