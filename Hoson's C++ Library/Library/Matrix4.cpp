#include "Matrix4.h"

Matrix4::Matrix4()
{
	for (size_t v = 0; v < 4; ++v)
	{
		for (size_t axis = 0; axis < 4; ++axis)
		{
			if (v == axis)
				matrix[v][axis] = 1;
			else
				matrix[v][axis] = 0;
		}
	}
}

Matrix4::Matrix4(
	float Xx, float Xy, float Xz, float Xw, 
	float Yx, float Yy, float Yz, float Yw, 
	float Zx, float Zy, float Zz, float Zw, 
	float Tx, float Ty, float Tz, float Tw)
{
	x[0] = Xx; x[1] = Xy; x[2] = Xz; x[3] = Xw; 
	y[0] = Yx; y[1] = Yy; y[2] = Yz; y[3] = Yw;
	z[0] = Zx; z[1] = Zy; z[2] = Zz; z[3] = Zw;
	t[0] = Tx; t[1] = Ty; t[2] = Tz; t[3] = Tw;
}

Matrix4::~Matrix4()
{
}

Matrix4::operator float*()
{
	return (float*)matrix;
}

Vector4 & Matrix4::operator[](int index)
{
	assert(index >= 0 && index <= 3 && "Invalid Matrix4 index");
	return matrix[index];
}

Vector4 Matrix4::operator[](int index) const
{
	assert(index >= 0 && index <= 3 && "Invalid Matrix4 index");
	return matrix[index];
}

Matrix4 & Matrix4::operator=(const Matrix4 & other)
{
	Matrix4 temp = other;
	float* copyTo = *this;
	float* copyFrom = temp;

	for (size_t i = 0; i < 15; ++i)
		copyTo[i] = copyFrom[i];

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4 & other) const
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

Matrix4 & Matrix4::scale(float xScale, float yScale, float zScale, float wScale)
{
	matrix[0][0] *= xScale;
	matrix[1][1] *= yScale;
	matrix[2][2] *= zScale;
	matrix[3][3] *= wScale;
	return *this;
}

Matrix4 & Matrix4::translate(float xTranslate, float yTranslate, float zTranslate, float wTranslate)
{
	matrix[3][0] += xTranslate;
	matrix[3][1] += yTranslate;
	matrix[3][2] += zTranslate;
	matrix[3][3] += wTranslate;
	return *this;
}

Vector4 operator*(const Matrix4 & m, const Vector4 & v)
{
	Vector4 result;
	Vector4 temp;

	for (size_t row = 0; row < 4; ++row)
	{
		for (size_t column = 0; column < 4; ++column)
			temp[column] = m[column][row];

		result[row] = temp.dot(v);
	}

	return result;
}
