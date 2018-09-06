#pragma once

#include "Vector2.h"

class Rectangle
{
public:
	template<typename T>
	Rectangle(T& pointVector, unsigned int width, unsigned int height);
	~Rectangle();

	Vector2 getOrigin();
	Vector2 getTopRight();
	Vector2 getBottomLeft();

	bool checkCollision(const Rectangle& other);
	Rectangle& updateRect(Vector2& newOrigin);

private:

	Vector2 m_RectOrigin;
	Vector2 m_RectTopRight;
	Vector2 m_RectBottomLeft;
};

template<typename T>
inline Rectangle::Rectangle(T& pointVector, unsigned int width, unsigned int height)
{
	m_RectOrigin[0] = pointVector[0];
	m_RectOrigin[1] = pointVector[1];
	m_RectTopRight[0] = m_RectOrigin[0] + width / 2;
	m_RectTopRight[1] = m_RectOrigin[1] + height / 2;
	m_RectBottomLeft[0] = m_RectOrigin[0] - width / 2;
	m_RectBottomLeft[1] = m_RectOrigin[1] - height / 2;
}



class Circle
{
public:
	template<typename T>
	Circle(T& pointVector, unsigned int diameter);
	~Circle();

	Vector2 getOrigin();
	float getRadius();

	bool checkCollision(Circle& other);
	Circle& updateCircle(const Vector2& newOrigin);

private:

	Vector2 m_CircleOrigin;
	float m_CircleRadius;
};

template<typename T>
inline Circle::Circle(T & pointVector, unsigned int diameter)
{
	m_CircleOrigin[0] = pointVector[0];
	m_CircleOrigin[1] = pointVector[1];
	m_CircleRadius = diameter / 2;
}



static bool checkCollision(Rectangle& r, Circle& c)
{
	Vector2 topLeft(r.getBottomLeft[0], r.getTopRight[1]);
	Vector2 bottomRight(r.getTopRight[0], r.getBottomLeft[1]);
	float rad = c.getRadius();
	float rad2 = pow(rad, 2);

	if (r.getTopRight()[0] < c.getOrigin()[0] - rad || r.getBottomLeft()[0] > c.getOrigin()[0] + rad ||
		r.getTopRight()[1] < c.getOrigin()[1] - rad || r.getBottomLeft()[1] > c.getOrigin()[1] + rad)
		return false;
	else if (magnitudePow2(r.getTopRight(), c.getOrigin()) > rad2 || magnitudePow2(r.getBottomLeft(), c.getOrigin()) > rad2 ||
		magnitudePow2(topLeft, c.getOrigin()) > rad2 || magnitudePow2(bottomRight, c.getOrigin()) > rad2)
		 {
			
		 }
}

static float magnitudePow2(Vector2 v1, Vector2 v2)
{
	Vector2 temp = v1 - v2;
	float magPow2 = pow(temp[0], 2) + pow(temp[1], 2);
	return magPow2;
}
