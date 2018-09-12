#include "2D_Collision.h"

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

Vector2 Rectangle::getOrigin() const
{
	return m_RectOrigin;
}

Vector2 Rectangle::getTopRight() const
{
	return m_RectTopRight;
}

Vector2 Rectangle::getBottomLeft() const
{
	return m_RectBottomLeft;
}

bool Rectangle::checkCollision(const Rectangle & other) const
{
	if (m_RectTopRight[0] < other.m_RectBottomLeft[0] || m_RectBottomLeft[0] > other.m_RectTopRight[0] ||
		m_RectTopRight[1] < other.m_RectBottomLeft[1] || m_RectBottomLeft[1] > other.m_RectTopRight[1])
		return false;
	else
		return true;
}
