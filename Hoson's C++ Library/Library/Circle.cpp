#include "2D_Collision.h"

Circle::~Circle()
{

}

Vector2 Circle::getOrigin()
{
	return m_CircleOrigin;
}

float Circle::getRadius()
{
	return m_CircleRadius;
}

bool Circle::checkCollision(Circle & other)
{
	float sumRadiiPow2 = pow(m_CircleRadius + other.m_CircleRadius, 2);
	float distancePow2 = magnitudePow2(m_CircleOrigin, other.m_CircleOrigin);
	
	if (distancePow2 <= sumRadiiPow2)
		return true;
	else
		return false;
}

Circle & Circle::updateCircle(const Vector2 & newOrigin)
{
	m_CircleOrigin = newOrigin;
	return *this;
}
