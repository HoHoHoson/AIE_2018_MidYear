#pragma once
#include "Vector2.h"
#include <cmath>

class Matrix2
{
public:
	Matrix2();
	Matrix2(float x1, float y1, float x2, float y2);
	~Matrix2();

	union 
	{
		struct
		{
			Vector2 x;
			Vector2 y;
		};

		Vector2 matrix[1];
	};

	operator float* ();
	Vector2& operator[](int index);

	Matrix2& operator=(Matrix2& other);
	Matrix2 operator*(const Matrix2& other);
	Matrix2& operator*=(const Matrix2& other);

	Matrix2& setRotate(float radian);

private:

};

Vector2 operator*(const Matrix2& m, const Vector2& v);
