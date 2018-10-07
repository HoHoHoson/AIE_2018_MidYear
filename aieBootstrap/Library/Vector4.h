#pragma once

#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>

class Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	~Vector4();

	operator float* ();
	float& operator[](int index);
	float operator[](int index)	const;

	float magnitude()					const;
	float dot(const Vector4& other)		const;
	Vector4 cross(const Vector4& other) const;
	Vector4& normalise();

	bool operator== (const Vector4& other) const;
	bool operator!= (const Vector4& other) const;
	Vector4& operator=(const Vector4& copyFrom);
	Vector4& operator+=(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4& operator*=(float scalar);
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator*(float scalar)	const;

	float getRadians(const Vector4& other)	const;
	float getDegrees(const Vector4& other)	const;

private:

	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float data[3];
	};
};

Vector4 operator*(float scalar, const Vector4& other);
