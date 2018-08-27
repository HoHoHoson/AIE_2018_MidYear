#include "Vector4.h"
#include <cassert>


Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::~Vector4()
{
}

Vector4::operator float*()
{
	return data;
}

Vector4 & Vector4::operator = (const Vector4 & copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;
	w = copyFrom.w;

	return *this;
}

Vector4 Vector4::operator+(const Vector4 & other)
{
	Vector4 temp;

	temp.x = x + other.x;
	temp.y = y + other.y;
	temp.z = z + other.z;

	if (w == 0 && other.w == 1)
		assert(false && "A vector can't be changed by a pointer");

	return temp;
}

Vector4 & Vector4::operator+=(const Vector4 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	if (w == 0 && other.w == 1)
		assert(false && "A vector can't be changed by a pointer");

	return *this;
}

Vector4 Vector4::operator-(const Vector4 & other)
{
	Vector4 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;

	if (w == 0 && other.w == 1)
		assert(false && "A vector can't be changed by a pointer");

	return temp;
}

Vector4 & Vector4::operator-=(const Vector4 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	if (w == 0 && other.w == 1)
		assert(false && "A vector can't be changed by a pointer");

	return *this;
}

Vector4 Vector4::operator*(float scalar)
{
	return scalar * *this;
}

Vector4 operator*(float scalar, const Vector4 & other)
{
	Vector4 temp;
	temp.x = other.x * scalar;
	temp.y = other.y * scalar;
	temp.z = other.z * scalar;

	return temp;
}

Vector4 & Vector4::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector4 Vector4::operator/(float scalar)
{
	Vector4 temp;
	temp.x = x / scalar;
	temp.y = y / scalar;
	temp.z = z / scalar;

	return temp;
}

Vector4 operator/(float scalar, const Vector4 & other)
{
	assert(false && "Can't divide a float by a vector");
	return NULL;
}

Vector4 & Vector4::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}


