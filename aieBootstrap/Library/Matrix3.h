#pragma once

#include "Vector3.h"
#include <cmath>

class Matrix3
{
public:
	Matrix3();
	Matrix3(float Xx, float Xy, float Xz, float Yx, float Yy, float Yz, float Zx, float Zy, float Zz);
	~Matrix3();

	operator float*();
	Vector3& operator[](int index);
	Vector3 operator[](int index) const;

	Matrix3& operator=(const Matrix3& other);
	Matrix3& operator*=(const Matrix3& other);
	Matrix3 operator*(const Matrix3& other) const;

	Matrix3& setIdentity();
	Matrix3& rotateX(float radian);
	Matrix3& rotateY(float radian);
	Matrix3& rotateZ(float radian);
	Matrix3& setRotateX(float radian);
	Matrix3& setRotateY(float radian);
	Matrix3& setRotateZ(float radian);
	Matrix3& scale(float xScale = 1, float yScale = 1, float zScale = 1);
	Matrix3& translate(float xTranslate = 0, float yTranslate = 0, float zTranslate = 0);

private:

	union
	{
		struct
		{
			Vector3 x;
			Vector3 y;
			Vector3 z;
		};

		Vector3 matrix[2];
	};
};

Vector3 operator* (const Matrix3& m, const Vector3& v);