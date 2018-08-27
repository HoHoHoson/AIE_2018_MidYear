#pragma once


class Vector4
{
public:
	Vector4(float x = 0, float y = 0, float z = 0, float w = 0);
	~Vector4();

	// the anonymous union lets you access the variables through the array "data" due to the struct grouping all the variables into a single struct variable
	// and everything inside the union shares the same bits of memory
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float data[4];
	};

	// math operators that most Vector classes have 
	operator float* ();
	Vector4& operator=(const Vector4& copyFrom);
	Vector4 operator+(const Vector4& other);
	Vector4& operator+=(const Vector4& other);
	Vector4 operator-(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4 operator*(float scalar);
	Vector4& operator*=(float scalar);
	Vector4 operator/(float scalar);
	Vector4& operator/=(float scalar);

private:

};

Vector4 operator*(float scalar, const Vector4& other);
Vector4 operator/(float scalar, const Vector4& other);