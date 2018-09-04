#include "Matrix4.h"

Matrix4::Matrix4()
{
	for (size_t v = 0; v < 4; ++v)
	{
		for (size_t axis = 0; axis < 4; ++axis)
		{
			if (v == axis)
				matrix[v].data[axis] = 1;
			else
				matrix[v].data[axis] = 0;
		}
	}
}

Matrix4::Matrix4(
	float Xx, float Xy, float Xz, float Xw, 
	float Yx, float Yy, float Yz, float Yw, 
	float Zx, float Zy, float Zz, float Zw, 
	float Tx, float Ty, float Tz, float Tw)
{
	x.x = Xx; x.y = Xy; x.z = Xz; x.w = Xw; 
	y.x = Yx; y.y = Yy; y.z = Yz; y.w = Yw;
	z.x = Zx; z.y = Zy; z.z = Zz; z.w = Zw;
	t.x = Tx; t.y = Ty; t.z = Tz; t.w = Tw;
}

Matrix4::~Matrix4()
{
}

Matrix4::operator float*()
{
	return (float*)matrix;
}

Vector4 & Matrix4::operator[](const int & index)
{
	return matrix[index];
}

Matrix4 & Matrix4::operator=(Matrix4 & other)
{
	float* copyTo = *this;
	float* copyFrom = other;

	for (size_t i = 0; i < 15; ++i)
		copyTo[i] = copyFrom[i];

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 & other)
{
	Matrix4 result;
	Vector4 temp;

	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t axis = 0; axis < 4; ++axis)
			temp[axis] = matrix[axis][row];
		for (size_t column = 0; column < 4; ++column)
			result[column][row] = temp.dot(other.matrix[column]);
	}

	return result;
}

Matrix4 & Matrix4::operator*=(const Matrix4 & other)
{
	return (*this = (Matrix4&)(*this * other));
}

Matrix4& Matrix4::rotateX(float radian)
{
	Matrix4 temp(
		1, 0, 0, 0,
		0, cosf(radian), sinf(radian), 0,
		0, -sinf(radian), cosf(radian), 0,
		0, 0, 0, 1);

	return (*this *= temp);
}

Matrix4 & Matrix4::rotateY(float radian)
{
	Matrix4 temp(
		cosf(radian), 0, -sinf(radian), 0,
		0, 1, 0, 0,
		sinf(radian), 0, cosf(radian), 0,
		0, 0, 0, 1);

	return (*this *= temp);
}

Matrix4 & Matrix4::rotateZ(float radian)
{
	Matrix4 temp(
		cosf(radian), sinf(radian), 0, 0,
		-sinf(radian), cosf(radian), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return (*this *= temp);
}

Matrix4 & Matrix4::setRotateX(float radian)
{
	Matrix4 temp(
		1, 0, 0, 0,
		0, cosf(radian), sinf(radian), 0,
		0, -sinf(radian), cosf(radian), 0,
		0, 0, 0, 1);

	return (*this = temp);
}

Matrix4 & Matrix4::setRotateY(float radian)
{
	Matrix4 temp(
		cosf(radian), 0, -sinf(radian), 0,
		0, 1, 0, 0,
		sinf(radian), 0, cosf(radian), 0,
		0, 0, 0, 1);

	return (*this = temp);
}

Matrix4 & Matrix4::setRotateZ(float radian)
{
	Matrix4 temp(
		cosf(radian), sinf(radian), 0, 0,
		-sinf(radian), cosf(radian), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return (*this = temp);
}

Vector4 operator*(const Matrix4 & m, const Vector4 & v)
{
	Vector4 result;
	Vector4 temp;

	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t column = 0; column < 4; ++column)
			temp[column] = m.matrix[column].data[row];

		result[row] = temp.dot(v);
	}

	return result;
}
