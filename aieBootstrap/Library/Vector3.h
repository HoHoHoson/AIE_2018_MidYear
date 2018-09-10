#pragma once

#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	// ways for accessing the data
	operator float* ();
	float& operator[](int index);
	float operator[](int index)			const;

	// typical Vector functions
	float magnitude()					const;
	float dot(const Vector3& other)		const;
	Vector3 cross(const Vector3& other) const;
	Vector3& normalise();

	// math operators that most Vector classes have 
	Vector3& operator=(const Vector3& copyFrom);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scalar);
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(float scalar)	const;

	float getRadians(const Vector3& other)	const;
	float getDegrees(const Vector3& other)	const;

private:

	// the anonymous union lets you access the variables through the array "data" due to the struct grouping all the variables into a single struct variable
	// and everything inside the union shares the same bits of memory
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		float data[2];
	};
};

// for the people who likes making our lives harder
static Vector3 operator*(float scalar, const Vector3& other);
