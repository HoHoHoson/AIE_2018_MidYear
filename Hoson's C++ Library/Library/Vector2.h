#pragma once

#include <cassert>
#define _USE_MATH_DEFINES
#include <cmath>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	operator float* ();
	float& operator[](int index);
	float operator[](int index)			const;

	float magnitude()					const;
	float dot(const Vector2& other)		const;
	Vector2& normalise();

	Vector2& operator=	(const Vector2& copyFrom);
	Vector2& operator+=	(const Vector2& other);
	Vector2& operator-=	(const Vector2& other);
	Vector2& operator*=	(float scalar);
	Vector2 operator-	(const Vector2& other)	const;
	Vector2 operator+	(const Vector2& other)	const;
	Vector2 operator*	(float scalar)	const;

	float getRadians	(const Vector2& other)	const;
	float getDegrees	(const Vector2& other)	const;

private:

	union
	{
		struct
		{
			float x;
			float y;
		};

		float data[1];
	};
};

Vector2 operator*(float scalar, const Vector2& other);