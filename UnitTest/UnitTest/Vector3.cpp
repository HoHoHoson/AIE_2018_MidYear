#include "Vector3.h"
#include <cassert>


// defined a constructor for Vector3
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}

Vector3::operator float*()
{
	return data;
}

//float& Vector3::operator[](int index)
//{
//	return (data[index]);
//}

Vector3 & Vector3::operator = (const Vector3 & copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;

	return *this;
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	Vector3 temp;

	temp.x = x + other.x;
	temp.y = y + other.y;
	temp.z = z + other.z;

	return temp;
}

Vector3 & Vector3::operator+=(const Vector3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	
	return *this;
}

Vector3 Vector3::operator-(const Vector3 & other)
{
	Vector3 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;
	
	return temp;
}

Vector3 & Vector3::operator-=(const Vector3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

// this function calls the other multiplication function, just cause I'm lazy
Vector3 Vector3::operator*(float scalar)
{
	return scalar * *this;
}

Vector3 operator*(float scalar, const Vector3 & other)
{
	Vector3 temp;
	temp.x = other.x * scalar;
	temp.y = other.y * scalar;
	temp.z = other.z * scalar;

	return temp;
}

Vector3 & Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3 Vector3::operator/(float scalar)
{
	Vector3 temp;
	temp.x = x / scalar;
	temp.y = y / scalar;
	temp.z = z / scalar;

	return temp;
}

Vector3 operator/(float scalar, const Vector3 & other)
{
	assert(false && "Can't divide a float by a vector");
	return NULL;
}

Vector3 & Vector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}


