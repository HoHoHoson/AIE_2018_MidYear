#pragma once

#include"Vector4.h"
#include <cmath>

class Matrix4
{
public:
	Matrix4();
	Matrix4(
		float Xx, float Xy, float Xz, float Xw, 
		float Yx, float Yy, float Yz, float Yw, 
		float Zx, float Zy, float Zz, float Zw, 
		float Tx, float Ty, float Tz, float Tw);
	~Matrix4();

	operator float*();
	Vector4& operator[](int index);
	Vector4 operator[](int index) const;

	Matrix4& operator=(const Matrix4& other);
	Matrix4& operator*=(const Matrix4& other);
	Matrix4 operator*(const Matrix4& other) const;

	Matrix4& rotateX(float radian);
	Matrix4& rotateY(float radian);
	Matrix4& rotateZ(float radian);
	Matrix4& setRotateX(float radian);
	Matrix4& setRotateY(float radian);
	Matrix4& setRotateZ(float radian);
	Matrix4& scale(float xScale = 1, float yScale = 1, float zScale = 1, float wScale = 1);
	Matrix4& translate(float xTranslate = 0, float yTranslate = 0, float zTranslate = 0, float wTranslate = 0);

private:

	union
	{
		struct
		{
			Vector4 x;
			Vector4 y;
			Vector4 z;
			Vector4 t;
		};
		Vector4 matrix[3];
	};
};

static Vector4 operator*(const Matrix4& m, const Vector4& v);