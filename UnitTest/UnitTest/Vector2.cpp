#include "Vector2.h"
#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>


Vector2::Vector2()
{
	x = 0;
	y = 0;
}

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

float& Vector2::operator[](int index)
{
	assert(index == 1 || index == 0 && "Invalid Vector2 index");
	return data[index];
}

float Vector2::magnitude()
{
	return sqrt(x * x + y * y);
}

float Vector2::dot(const Vector2 & other)
{
	float dotProduct = 0;

	for (size_t i = 0; i < 2; ++i)
		dotProduct += data[i] * other.data[i];

	return dotProduct;
}

float Vector2::getRadians(const Vector2 & other)
{
	float radian;
	Vector2 v2a = *this;
	Vector2 v2b = other;

	if (v2a.magnitude() != 1)
		v2a.normalise();
	if (v2b.magnitude() != 1)
		v2b.normalise();

	if (v2a.dot(Vector2(-v2b.y, v2b.x)) >= 0)
		radian = acos(v2a.dot(v2b));
	else
		radian = -acos(v2a.dot(v2b));

	return radian;
}

float Vector2::getDegrees(const Vector2& other)
{
	return (this->getRadians(other) / (M_PI / 180));
}

Vector2 & Vector2::normalise()
{
	float mag = this->magnitude();

	for (size_t i = 0; i < 2; ++i)
		data[i] = data[i] / mag;

	return *this;
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
	return Vector2();
}

Vector2 & Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}