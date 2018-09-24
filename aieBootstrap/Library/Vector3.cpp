#include "Vector3.h"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

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

float& Vector3::operator[](int index)
{
	assert(index >= 0 && index <= 2 && "Invalid Vector3 index");
	return data[index];
}

float Vector3::operator[](const int index) const
{
	assert(index >= 0 && index <= 2 && "Invalid Vector3 index");
	return data[index];
}

float Vector3::dot(const Vector3 & other) const
{
	float dotProduct = 0;

	for (size_t i = 0; i < 3; ++i)
		dotProduct += data[i] * other.data[i];

	return dotProduct;
}

Vector3 Vector3::cross(const Vector3 & other) const
{
	Vector3 temp;

	temp.x = (y * other.z - z * other.y);
	temp.y = (z * other.x - x * other.z);
	temp.z = (x * other.y - y * other.x);

	return temp;
}

float Vector3::getRadians(const Vector3 & other) const
{
	float radian;
	Vector3 v3a = *this;
	Vector3 v3b = other;

	if (v3a.magnitude() != 1)
		v3a.normalise();
	if (v3b.magnitude() != 1)
		v3b.normalise();

	if (v3a.cross(v3b).data[2] >= 0)
		radian = -acos(v3a.dot(v3b));
	else
		radian = acos(v3a.dot(v3b));

	return radian;
}

float Vector3::getDegrees(const Vector3 & other) const
{
	return (this->getRadians(other) / (M_PI / 180));
}

float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 & Vector3::normalise()
{
	float mag = this->magnitude();

	if (mag == 0)
		return *this = { 0,0,0 };

	for (size_t i = 0; i < 3; ++i)
		data[i] = data[i] / mag;

	return *this;
}

Vector3 & Vector3::operator = (const Vector3 & copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;

	return *this;
}

Vector3 Vector3::operator+(const Vector3 & other) const
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

Vector3 Vector3::operator-(const Vector3 & other) const
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
Vector3 Vector3::operator*(float scalar) const
{
	return scalar * *this;
}

Vector3 operator*(float scalar, const Vector3 & other)
{
	Vector3 temp;
	temp[0] = other[0] * scalar;
	temp[1] = other[1] * scalar;
	temp[2] = other[2] * scalar;

	return temp;
}

Vector3 & Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3 operator/(float scalar, const Vector3 & other)
{
	assert(false && "Can't divide a float by a vector");
	return Vector3();
}



