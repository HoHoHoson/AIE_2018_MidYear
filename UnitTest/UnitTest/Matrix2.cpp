#include "Matrix2.h"

Matrix2::Matrix2()
{
	for (size_t v2 = 0; v2 < 2; ++v2)
	{
		for (size_t axis = 0; axis < 2; ++axis)
		{
			if (v2 == axis)
				matrix[v2].data[axis] = 1;
			else
				matrix[v2].data[axis] = 0;
		}
	}
}

Matrix2::Matrix2(float x1, float y1, float x2, float y2)
{
	x.x = x1; x.y = y1; y.x = x2; y.y = y2;
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
	return matrix[index];
}

Matrix2 & Matrix2::operator=(Matrix2 & other)
{
	float* copyTo = *this;
	float* copyFrom = other;

	for (size_t i = 0; i < 4; ++i)
		copyTo[i] = copyFrom[i];

	return *this;
}

Matrix2 Matrix2::operator*(const Matrix2 & other)
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
	*this = *this * other;
	return *this;
}

Matrix2 & Matrix2::setRotate(float radian)
{
	Matrix2 temp(cosf(radian), sinf(radian), -sinf(radian), cosf(radian));
	return (*this *= temp);
}

Vector2 operator*(const Matrix2 & m, const Vector2 & v)
{
	Vector2 result;
	Vector2 temp;

	for (size_t row = 0; row < 2; ++row)
	{
		for (size_t column = 0; column < 2; ++column)
			temp[column] = m.matrix[column].data[row];

		result[row] = temp.dot(v);
	}

	return result;
}
