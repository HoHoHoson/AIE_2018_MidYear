#include "2D_Collision.h"


Ray2D::Ray2D()
{
}

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

Vector2 Ray2D::getEnd() const
{
	return m_End;
}

float Ray2D::getLength() const
{
	return m_Length;
}

Vector2 Ray2D::closestPoint(const Vector2 & point) const
{
	Vector2 difference = point - m_Origin;
	float t = difference.dot(m_Direction);
	HLib::clamp(t, 0, m_Length);
	return m_Origin + m_Direction * t;
}

bool Ray2D::checkCollision(const Ray2D & r, Vector2* v) const
{
	Vector2 end1 = m_Origin + m_Direction * m_Length;
	Vector2 end2 = r.m_Origin + r.m_Direction * r.m_Length;
	// Ray 1 
	float A1 = end1[1] - m_Origin[1];
	float B1 = m_Origin[0] - end1[0];
	float C1 = A1 * m_Origin[0] + B1 * m_Origin[1];
	// Ray 2
	float A2 = end2[1] - r.m_Origin[1];
	float B2 = r.m_Origin[0] - end2[0];
	float C2 = A2 * r.m_Origin[0] + B2 * r.m_Origin[1];

	float det = A1 * B2 - A2 * B1;

	// Lines are parallel
	if (det == 0)
		return false;

	Vector2 intersect((B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det);

	if (std::fminf(m_Origin[0], end1[0]) <= intersect[0] && intersect[0] <= std::fmaxf(m_Origin[0], end1[0]) &&
		std::fminf(m_Origin[1], end1[1]) <= intersect[1] && intersect[1] <= std::fmaxf(m_Origin[1], end1[1]))
		if (std::fminf(r.m_Origin[0], end2[0]) <= intersect[0] && intersect[0] <= std::fmaxf(r.m_Origin[0], end2[0]) &&
			std::fminf(r.m_Origin[1], end2[1]) <= intersect[1] && intersect[1] <= std::fmaxf(r.m_Origin[1], end2[1]))
			return true;

	return false;
}

bool Ray2D::checkCollision(const Circle & c, Vector2* i) const
{
	float length = (c.getOrigin() - m_Origin).dot(m_Direction);
	float toClosestPoint = HLib::MagPow2_2D(closestPoint(c.getOrigin()), c.getOrigin());
	float radiusSqr = powf(c.getRadius(), 2);

	if (toClosestPoint > radiusSqr)
		return false;

	if (i != nullptr)
		*i = m_Origin + m_Direction * (length - sqrt(radiusSqr - toClosestPoint));

	return true;
}

bool Ray2D::checkCollision(const Plane2D & pl, Vector2 * i) const
{
	float dir = m_Direction.dot(pl.getNormal());
	float length = pl.distanceTo(m_Origin);

	if (length == 0)
	{
		if (i != nullptr)
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

bool Ray2D::checkCollision(const Rectangle & r, Vector2 * i) const
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
