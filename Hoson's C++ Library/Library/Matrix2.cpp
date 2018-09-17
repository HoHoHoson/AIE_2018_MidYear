#include "Matrix2.h"

Matrix2::Matrix2()
{
	for (size_t v2 = 0; v2 < 2; ++v2)
	{
		for (size_t axis = 0; axis < 2; ++axis)
		{
			if (v2 == axis)
				matrix[v2][axis] = 1;
			else
				matrix[v2][axis] = 0;
		}
	}
}

Matrix2::Matrix2(float Xx, float Xy, float Yx, float Yy)
{
	x[0] = Xx; x[1] = Xy; y[0] = Yx; y[1] = Yy;
}

Matrix2::~Matrix2()
{
}

Matrix2::operator float*()
{
	return (float*)matrix;
}

Vector2& Matrix2::operator[](int index)
{
	assert(index == 0 || index == 1 && "Invalid Matrix2 index");
	return matrix[index];
}

Vector2 Matrix2::operator[](int index) const
{
	assert(index == 0 || index == 1 && "Invalid Matrix2 index");
	return matrix[index];
}

Matrix2 & Matrix2::operator=(const Matrix2 & other)
{
	Matrix2 temp = other;
	float* copyTo = *this;
	float* copyFrom = temp;

	for (size_t i = 0; i < 4; ++i)
		copyTo[i] = copyFrom[i];

	return *this;
}

Matrix2 Matrix2::operator*(const Matrix2 & other) const
{
	Matrix2 value;
	Vector2 temp;

	for (size_t row = 0; row < 2; ++row)
	{
		for (size_t axis = 0; axis < 2; ++axis)
			temp[axis] = matrix[axis][row];
		for (size_t column = 0;  column < 2;  column++)
			value[column][row] = temp.dot(other.matrix[column]);
	}

	return value;
}

Matrix2& Matrix2::operator*=(const Matrix2 & other)
{
	return (*this = (Matrix2&)(*this * other));
}

Matrix2 & Matrix2::setIdentity()
{
	for (size_t v2 = 0; v2 < 2; ++v2)
	{
		for (size_t axis = 0; axis < 2; ++axis)
		{
			if (v2 == axis)
				matrix[v2][axis] = 1;
			else
				matrix[v2][axis] = 0;
		}
	}

	return *this;
}

Matrix2& Matrix2::rotate(float radian)
{
	Matrix2 temp(cosf(radian), sinf(radian), -sinf(radian), cosf(radian));
	return (*this *= temp);
}

Matrix2 & Matrix2::setRotate(float radian)
{
	(Matrix2&)*this = (Matrix2&)rotate(radian);
	return *this;
}

Matrix2 & Matrix2::scale(float xScale, float yScale)
{
	matrix[0][0] *= xScale;
	matrix[1][1] *= yScale;
	return *this;
}

Vector2 operator*(const Matrix2 & m, const Vector2 & v)
{
	Vector2 result;
	Vector2 temp;

	for (size_t row = 0; row < 2; ++row)
	{
		for (size_t column = 0; column < 2; ++column)
			temp[column] = m[column][row];

		result[row] = temp.dot(v);
	}

	return result;
}
