#pragma once

#include "Algorithms.h"
#include "Vector2.h"

class Rectangle
{
public:
	Rectangle();
	template<typename T>
	Rectangle(T pointVector, unsigned int width, unsigned int height);
	~Rectangle();

	Vector2 getOrigin()		const;
	Vector2 getTopRight()	const;
	Vector2 getBottomLeft()	const;

	template<typename T>
	Rectangle& updateRect(const T& newOrigin, unsigned int newWidth = NULL, unsigned int newHeight = NULL);
	bool checkCollision(const Rectangle& other) const;

private:

	Vector2 m_RectOrigin;
	Vector2 m_RectTopRight;
	Vector2 m_RectBottomLeft;
};

template<typename T>
inline Rectangle::Rectangle(T pointVector, unsigned int width, unsigned int height)
{
	m_RectOrigin[0] = pointVector[0];
	m_RectOrigin[1] = pointVector[1];
	m_RectTopRight[0] = m_RectOrigin[0] + width / 2;
	m_RectTopRight[1] = m_RectOrigin[1] + height / 2;
	m_RectBottomLeft[0] = m_RectOrigin[0] - width / 2;
	m_RectBottomLeft[1] = m_RectOrigin[1] - height / 2;
}

template<typename T>
inline Rectangle & Rectangle::updateRect(const T & newOrigin, unsigned int newWidth, unsigned int newHeight)
{
	int w = newWidth / 2;
	int h = newHeight / 2;
	Vector2 temp(newOrigin[0] - m_RectOrigin[0], newOrigin[1] - m_RectOrigin[1]);
	m_RectOrigin += temp;

	if (newWidth != NULL)
	{
		m_RectTopRight[0] = m_RectOrigin[0] + w;
		m_RectBottomLeft[0] = m_RectOrigin[0] - w;
	}
	else
	{
		m_RectTopRight[0] += temp[0];
		m_RectBottomLeft[0] += temp[0];
	}

	if (newHeight != NULL)
	{
		m_RectTopRight[1] = m_RectOrigin[1] + h;
		m_RectBottomLeft[1] = m_RectOrigin[1] - h;
	}
	else
	{
		m_RectTopRight[1] += temp[1];
		m_RectBottomLeft[1] += temp[1];
	}

	return *this;
}



class Circle
{
public:
	Circle();
	template<typename T>
	Circle(T pointVector, unsigned int diameter);
	~Circle();

	Vector2 getOrigin()		 const;
	float getRadius()		 const;

	template<typename T>
	Circle& updateCircle(const T& newOrigin, unsigned int newDiameter = NULL);
	bool checkCollision(const Circle& other)	const;
	bool checkCollision(const Rectangle& other) const;

private:

	Vector2 m_CircleOrigin;
	float m_CircleRadius;
};

template<typename T>
inline Circle::Circle(T pointVector, unsigned int diameter)
{
	m_CircleOrigin[0] = pointVector[0];
	m_CircleOrigin[1] = pointVector[1];
	m_CircleRadius = (float)diameter / 2;
}

template<typename T>
inline Circle & Circle::updateCircle(const T & newOrigin, unsigned int newDiameter)
{
	m_CircleOrigin[0] = newOrigin[0];
	m_CircleOrigin[1] = newOrigin[1];

	if (newDiameter != NULL)
		m_CircleRadius = (float)newDiameter / 2;

	return *this;
}



class Plane2D
{
public:
	Plane2D();
	template<typename T>
	Plane2D(T from, T to); 	// the normal is on the right side of this line (the collision side)
	~Plane2D();

	Vector2 getNormal() const;
	float getScalar()	const;
	float getLength()	const;

	Vector2 closestPointTo(const Vector2 & other)	const;
	float distanceTo(const Vector2& other)			const;

	bool checkCollision(const Vector2& p)			const;
	bool checkCollision(const Circle& c)			const;
	bool checkCollision(const Rectangle& r)			const;

private:

	Vector2 normal;
	float scalar;
	float length;
};

template<typename T>
inline Plane2D::Plane2D(T from, T to)
{
	T temp = (to - from).normalise();
	normal[0] = -temp[1];
	normal[1] = temp[0];
	scalar = to.dot(normal);
	length = (from - to).magnitude();

	if (normal[0] != normal[0] && normal[1] != normal[1])
		assert(false && "Can't create a Plane2D with only one point!");
}



class Ray2D
{
public:
	Ray2D();
	template<typename T>
	Ray2D(T origin, T destination, float length = INFINITY);
	~Ray2D();

	float getLength()		const;
	Vector2 getOrigin()		const;
	Vector2 getDirection()	const;
	Vector2 getEnd()		const;

	Vector2 closestPoint(const Vector2& point)						const;
	bool checkCollision(const Ray2D& ray)							const;
	bool checkCollision(const Circle& c, Vector2* i = nullptr)	  	const;
	bool checkCollision(const Plane2D& pl, Vector2* i = nullptr)	const;
	bool checkCollision(const Rectangle& r, Vector2* i = nullptr)	const;

private:

	Vector2 m_Origin;
	Vector2 m_End;
	Vector2 m_Direction;
	float m_Length;
};

template<typename T>
inline Ray2D::Ray2D(T origin, T destination, float length)
{
	m_Origin = { origin[0], origin[1] };
	m_Direction = { destination[0] - origin[0], destination[1] - origin[1] };
	m_Direction.normalise();
	m_Length = length;
	m_End = m_Origin + m_Direction * m_Length;
}