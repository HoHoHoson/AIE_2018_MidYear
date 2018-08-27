#pragma once


class Vector2
{
public:
	Vector2(float x = 0, float y = 0);
	~Vector2();

	union
	{
		struct
		{
			float x;
			float y;
		};

		float data[2];
	};

	operator float* ();
	Vector2& operator=(const Vector2& copyFrom);
	Vector2 operator+(const Vector2& other);
	Vector2& operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2 operator*(float scalar);
	Vector2& operator*=(float scalar);
	Vector2 operator/(float scalar);
	Vector2& operator/=(float scalar);

private:

};

Vector2 operator*(float scalar, const Vector2& other);
Vector2 operator/(float scalar, const Vector2& other);