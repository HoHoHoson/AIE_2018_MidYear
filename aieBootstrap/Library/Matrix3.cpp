#include "Matrix3.h"

Matrix3::Matrix3()
{
	for (size_t v = 0; v < 3; ++v)
	{
		for (size_t axis = 0; axis < 3; ++axis)
		{
			if (v == axis)
				matrix[v][axis] = 1;
			else
				matrix[v][axis] = 0;
		}
	}
}

Matrix3::Matrix3(float Xx, float Xy, float Xz, float Yx, float Yy, float Yz, float Zx, float Zy, float Zz)
{
	x[0] = Xx; x[1] = Xy; x[2] = Xz; 
	y[0] = Yx; y[1] = Yy; y[2] = Yz; 
	z[0] = Zx; z[1] = Zy; z[2] = Zz;
}

Matrix3::~Matrix3()
{
}

Matrix3::operator float*()
{
	return (float*)matrix;
}

Vector3 & Matrix3::operator[](int index)
{
	assert(index >= 0 && index <= 2 && "Invalid Matrix3 index");
	return matrix[index];
}

Vector3 Matrix3::operator[](int index) const
{
	assert(index >= 0 && index <= 2 && "Invalid Matrix3 index");
	return matrix[index];
}

Matrix3 & Matrix3::operator=(const Matrix3 & other)
{
	Matrix3 temp = other;
	float* copyTo = *this;
	float* copyFrom = temp;

	for (size_t i = 0; i < 9; ++i)
		copyTo[i] = copyFrom[i];

	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3 & other) const
{
	Matrix3 value;
	Vector3 temp;

	for (size_t row = 0; row < 3; ++row)
	{
		for (size_t axis = 0; axis < 3; ++axis)
			temp[axis] = matrix[axis][row];
		for (size_t column = 0; column < 3; column++)
			value[column][row] = temp.dot(other.matrix[column]);
	}

	return value;
}

Matrix3 & Matrix3::operator*=(const Matrix3 & other)
{
	return (*this = (Matrix3&)(*this * other));
}

Matrix3 & Matrix3::setIdentity()
{
	for (size_t v = 0; v < 3; ++v)
	{
		for (size_t axis = 0; axis < 3; ++axis)
		{
			if (v == axis)
				matrix[v][axis] = 1;
			else
				matrix[v][axis] = 0;
		}
	}

	return *this;
}

Matrix3& Matrix3::rotateX(float radian)
{
	Matrix3 temp(
		1, 0, 0,
		0, cosf(radian), sinf(radian),
		0, -sinf(radian), cosf(radian));

	return (*this *= temp);
}

Matrix3 & Matrix3::rotateY(float radian)
{
	Matrix3 temp(
		cosf(radian), 0, -sinf(radian),
		0, 1, 0,
		sinf(radian), 0, cosf(radian));

	return (*this *= temp);
}

Matrix3 & Matrix3::rotateZ(float radian)
{
	Matrix3 temp(
		cosf(radian), sinf(radian), 0,
		-sinf(radian), cosf(radian), 0,
		0, 0, 1);

	return (*this *= temp);
}

Matrix3 & Matrix3::setRotateX(float radian)
{
	Matrix3 temp(
		1, 0, 0,
		0, cosf(radian), sinf(radian),
		0, -sinf(radian), cosf(radian));

	return (*this = temp);
}

Matrix3 & Matrix3::setRotateY(float radian)
{
	Matrix3 temp(
		cosf(radian), 0, -sinf(radian),
		0, 1, 0,
		sinf(radian), 0, cosf(radian));

	return (*this = temp);
}

Matrix3 & Matrix3::setRotateZ(float radian)
{
	Matrix3 temp(
		cosf(radian), sinf(radian), 0,
		-sinf(radian), cosf(radian), 0,
		0, 0, 1);

	return (*this = temp);
}

Matrix3 & Matrix3::scale(float xScale, float yScale, float zScale)
{
	matrix[0][0] *= xScale;
	matrix[1][1] *= yScale;
	matrix[2][2] *= zScale;
	return *this;
}

Matrix3 & Matrix3::translate(float xTranslate, float yTranslate, float zTranslate)
{
	matrix[2][0] += xTranslate;
	matrix[2][1] += yTranslate;
	matrix[2][2] += zTranslate;
	return *this;
}

Vector3 operator*(const Matrix3 & m, const Vector3 & v)
{
	Vector3 result;
	Vector3 temp;

	for (size_t row = 0; row < 3; ++row)
	{
		for (size_t column = 0; column < 3; ++column)
			temp[column] = m[column][row];

		result[row] = temp.dot(v);
	}

	return result;
}
