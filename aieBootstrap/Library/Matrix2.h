#pragma once

#include "Vector2.h"
#include <cmath>

class Matrix2
{
public:
	Matrix2();
	Matrix2(float Xx, float Xy, float Yx, float Yy);
	~Matrix2();

	operator float* ();
	Vector2& operator[](int index);
	Vector2 operator[](int index) const;

	Matrix2& operator=(const Matrix2& other);
	Matrix2& operator*=(const Matrix2& other);
	Matrix2 operator*(const Matrix2& other) const;

	Matrix2& setIdentity();
	Matrix2& rotate(float radian);
	Matrix2& setRotate(float radian);
	Matrix2& scale(float xScale = 1, float yScale = 1);

private:

	union
	{
		struct
		{
			Vector2 x;
			Vector2 y;
		};

		Vector2 matrix[1];
	};
};

Vector2 operator*(const Matrix2& m, const Vector2& v);
