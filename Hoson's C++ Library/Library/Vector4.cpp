#include "Vector4.h"

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
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

float Vector4::operator[](const int index) const
{
	assert(index >= 0 || index <= 3 && "Invalid Vector4 index");
	return data[index];
}

float Vector4::dot(const Vector4 & other) const
{
	float dotProduct = 0;

	for (size_t i = 0; i < 4; ++i)
		dotProduct += data[i] * other.data[i];

	return dotProduct;
}

Vector4 Vector4::cross(const Vector4 & other) const
{
	Vector4 temp;

	temp.x = (y * other.z - z * other.y);
	temp.y = (z * other.x - x * other.z);
	temp.z = (x * other.y - y * other.x);
	temp.w = 0;

	return temp;
}

float Vector4::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vector4 & Vector4::normalise()
{
	float mag = this->magnitude();

	if (mag == 0)
		return *this = { 0,0,0,0 };

	for (size_t i = 0; i < 3; ++i)
		data[i] = data[i] / mag;

	data[3] = 0;

	return *this;
}

bool Vector4::operator==(const Vector4 & other) const
{
	return (
		x == other.x &&
		y == other.y &&
		z == other.z &&
		w == other.w);
}

bool Vector4::operator!=(const Vector4 & other) const
{
	return !(*this == other);
}

Vector4 & Vector4::operator = (const Vector4 & copyFrom)
{
	x = copyFrom.x;
	y = copyFrom.y;
	z = copyFrom.z;
	w = copyFrom.w;

	return *this;
}

float Vector4::getRadians(const Vector4 & other) const
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

float Vector4::getDegrees(const Vector4 & other) const
{
	return (this->getRadians(other) / (M_PI / 180));
}

Vector4 Vector4::operator+(const Vector4 & other) const
{
	Vector4 temp;

	temp.x = x + other.x;
	temp.y = y + other.y;
	temp.z = z + other.z;
	temp.w = w + other.w;

	return temp;
}

Vector4 & Vector4::operator+=(const Vector4 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

Vector4 Vector4::operator-(const Vector4 & other) const
{
	Vector4 temp;
	temp.x = x - other.x;
	temp.y = y - other.y;
	temp.z = z - other.z;
	temp.w = w - other.w;

	return temp;
}

Vector4 & Vector4::operator-=(const Vector4 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

Vector4 Vector4::operator*(float scalar) const
{
	return scalar * *this;
}

Vector4 operator*(float scalar, const Vector4 & other)
{
	Vector4 temp;
	temp[0] = other[0] * scalar;
	temp[1] = other[1] * scalar;
	temp[2] = other[2] * scalar;
	temp[3] = other[3] * scalar;

	return temp;
}

Vector4 & Vector4::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;

	return *this;
}


