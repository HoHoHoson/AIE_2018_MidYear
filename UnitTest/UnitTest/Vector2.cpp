#include "Vector2.h"
#include <cassert>


Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{
}

Vector2::operator float*()
{
	return data;
}

Vector2 & Vector2::operator = (const Vector2 & copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;

	return *this;
}

Vector2 Vector2::operator+(const Vector2 & other)
{
	Vector2 temp;

	temp.x = x + other.x;
	temp.y = y + other.y;

	return temp;
}

Vector2 & Vector2::operator+=(const Vector2 & other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2 & other)
{
	Vector2 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;

	return temp;
}

Vector2 & Vector2::operator-=(const Vector2 & other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2 Vector2::operator*(float scalar)
{
	return scalar * *this;
}

Vector2 operator*(float scalar, const Vector2 & other)
{
	Vector2 temp;
	temp.x = other.x * scalar;
	temp.y = other.y * scalar;

	return temp;
}

Vector2 & Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2 Vector2::operator/(float scalar)
{
	Vector2 temp;
	temp.x = x / scalar;
	temp.y = y / scalar;

	return temp;
}

Vector2 operator/(float scalar, const Vector2 & other)
{
	assert(false && "Can't divide a float by a vector");
	return NULL;
}

Vector2 & Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}