#include "2D_Collision.h"

Circle::Circle()
{
}

Circle::~Circle()
{
}

Vector2 Circle::getOrigin() const
{
	return m_CircleOrigin;
}

unsigned int Circle::getRadius() const
{
	return m_CircleRadius;
}

bool Circle::checkCollision(const Circle & other) const
{
	float sumRadiiPow2 = pow(m_CircleRadius + other.m_CircleRadius, 2);
	float distancePow2 = MagPow2_2D(m_CircleOrigin, other.m_CircleOrigin);
	
	if (distancePow2 <= sumRadiiPow2)
		return true;
	else
		return false;
}

bool Circle::collisionRectangle(const Rectangle & r) const
{
	Vector2 topLeft(r.getBottomLeft()[0], r.getTopRight()[1]);
	Vector2 bottomRight(r.getTopRight()[0], r.getBottomLeft()[1]);
	float rad = m_CircleRadius;
	float rad2 = pow(rad, 2);

	if (MagPow2_2D(r.getTopRight(), m_CircleOrigin) < rad2 || MagPow2_2D(r.getBottomLeft(), m_CircleOrigin) < rad2 ||
		MagPow2_2D(topLeft, m_CircleOrigin) < rad2 || MagPow2_2D(bottomRight, m_CircleOrigin) < rad2)
		return true;
	else if (r.getTopRight()[0] < m_CircleOrigin[0] - rad || r.getBottomLeft()[0] > m_CircleOrigin[0] + rad ||
		r.getTopRight()[1] < m_CircleOrigin[1] - rad || r.getBottomLeft()[1] > m_CircleOrigin[1] + rad)
		return false;
	else
		return true;
}