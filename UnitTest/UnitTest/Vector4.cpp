#include "Vector4.h"
#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>


Vector4::Vector4()
{
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 0;
}

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

float& Vector4::operator[](int index)
{
	assert(index >= 0 || index <= 3 && "Invalid Vector4 index");
	return data[index];
}

float Vector4::dot(const Vector4 & other)
{
	float dotProduct = 0;

	for (size_t i = 0; i < 4; ++i)
		dotProduct += data[i] * other.data[i];

	return dotProduct;
}

Vector4 Vector4::cross(const Vector4 & other)
{
	Vector4 temp;

	temp.x = (y * other.z - z * other.y);
	temp.y = (z * other.x - x * other.z);
	temp.z = (x * other.y - y * other.x);

	return temp;
}

float Vector4::getRadians(const Vector4 & other)
{
	float radian;
	Vector4 v4a = *this;
	Vector4 v4b = other;

	if (v4a.magnitude() != 1)
		v4a.normalise();
	if (v4b.magnitude() != 1)
		v4b.normalise();

	if (v4a.cross(v4b).data[2] >= 0)
		radian = -acos(v4a.dot(v4b));
	else
		radian = acos(v4a.dot(v4b));

	return radian;
}

float Vector4::getDegrees(const Vector4 & other)
{
	return (this->getRadians(other) / (M_PI / 180));
}

float Vector4::magnitude()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Vector4 & Vector4::normalise()
{
	float mag = this->magnitude();

	for (size_t i = 0; i < 4; ++i)
		data[i] = data[i] / mag;

	return *this;
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
	return Vector4();
}

Vector4 & Vector4::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}


