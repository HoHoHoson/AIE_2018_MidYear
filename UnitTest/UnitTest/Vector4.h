#pragma once


class Vector4
{
public:
	Vector4(float x = 0, float y = 0, float z = 0, float w = 0);
	~Vector4();

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

	operator float* ();
	float& operator[](int index);

	float dot(const Vector4& other);
	Vector4 cross(const Vector4& other);
	float magnitude();
	Vector4& normalise();

	Vector4& operator=(const Vector4& copyFrom);
	Vector4 operator+(const Vector4& other);
	Vector4& operator+=(const Vector4& other);
	Vector4 operator-(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4 operator*(float scalar);
	Vector4& operator*=(float scalar);
	Vector4 operator/(float scalar);
	Vector4& operator/=(float scalar);

	float getRadians(const Vector4& other);
	float getDegrees(const Vector4& other);

private:

};

Vector4 operator*(float scalar, const Vector4& other);
Vector4 operator/(float scalar, const Vector4& other);