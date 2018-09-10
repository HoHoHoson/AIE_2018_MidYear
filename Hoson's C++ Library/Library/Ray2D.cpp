#include "2D_Collision.h"


Ray2D::~Ray2D()
{
}

Vector2 Ray2D::getOrigin() const
{
	return m_Origin;
}

Vector2 Ray2D::getDirection() const
{
	return m_Direction;
}

float Ray2D::getLength() const
{
	return m_Length;
}

Vector2 Ray2D::closestPoint(const Vector2 & point) const
{
	Vector2 difference = point - m_Origin;
	float t = HLib::clamp(difference.dot(m_Direction), 0, m_Length);
	return m_Origin + m_Direction * t;
}

bool Ray2D::collisionCircle(const Circle & c, Vector2* i) const
{
	float length = (c.getOrigin() - m_Origin).dot(m_Direction);
	float toClosestPoint = MagPow2_2D(closestPoint(c.getOrigin()), c.getOrigin());
	float radiusSqr = pow(c.getRadius(), 2);

	if (toClosestPoint > radiusSqr)
		return false;

	if (i != nullptr)
		*i = m_Origin + m_Direction * (length - sqrt(radiusSqr - toClosestPoint));

	return true;
}

bool Ray2D::collisionPlane(const Plane2D & pl, Vector2 * i) const
{
	float dir = m_Direction.dot(pl.getNormal());
	float length = pl.distanceTo(m_Origin);

	if (length == 0)
	{
		*i = m_Origin;
		return true;
	}

	if (dir >= 0)
		return false;

	float actualLength = -(length / dir);

	if (actualLength > m_Length)
		return false;
	else
	{
		if (i != nullptr)
			*i = m_Origin + m_Direction * actualLength;
		return true;
	}
}

bool Ray2D::collisionRectangle(const Rectangle & r, Vector2 * i) const
{
	float xMin, xMax, yMin, yMax;

	if (m_Direction[0] < 0)
	{
		xMax = (r.getBottomLeft()[0] - m_Origin[0]) / m_Direction[0];
		xMin = (r.getTopRight()[0] - m_Origin[0]) / m_Direction[0];
	}
	else
	{
		xMin = (r.getBottomLeft()[0] - m_Origin[0]) / m_Direction[0];
		xMax = (r.getTopRight()[0] - m_Origin[0]) / m_Direction[0];
	}

	if (m_Direction[1] < 0)
	{
		yMax = (r.getBottomLeft()[1] - m_Origin[1]) / m_Direction[1];
		yMin = (r.getTopRight()[1] - m_Origin[1]) / m_Direction[1];
	}
	else
	{
		yMin = (r.getBottomLeft()[1] - m_Origin[1]) / m_Direction[1];
		yMax = (r.getTopRight()[1] - m_Origin[1]) / m_Direction[1];
	}

	float temp;

	if (xMin > yMin)
		temp = xMin;
	else
		temp = yMin;

	if (xMin > yMax || yMin > xMax || m_Length < temp)
		return false;

	if (i != nullptr)
		*i = m_Origin + m_Direction * temp;

	return true;
}
