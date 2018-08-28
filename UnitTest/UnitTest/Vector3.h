#pragma once


class Vector3
{
public:
	Vector3(float x = 0, float y = 0, float z = 0);
	~Vector3();

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

	// ways for accessing the data
	operator float* ();
	float& operator[](int index);

	// typical Vector functions
	float dot(const Vector3& other);
	Vector3 cross(const Vector3& other);
	float magnitude();
	Vector3& normalise();

	// math operators that most Vector classes have 
	Vector3& operator=(const Vector3& copyFrom);
	Vector3 operator+(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3 operator*(float scalar);
	Vector3& operator*=(float scalar);
	Vector3 operator/(float scalar);
	Vector3& operator/=(float scalar);

	float getRadians(const Vector3& other);
	float getDegrees(const Vector3& other);

private:

};

// for the people who likes making our lives harder
Vector3 operator*(float scalar, const Vector3& other);
// throws an assert for any stupid people that flips the numerator and denominator
Vector3 operator/(float scalar, const Vector3& other);
