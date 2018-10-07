#include "2D_Collision.h"


Plane2D::Plane2D()
{
}

Plane2D::~Plane2D()
{
}

Vector2 Plane2D::getNormal() const
{
	return normal;
}

float Plane2D::getScalar() const
{
	return scalar;
}

Vector2 Plane2D::closestPointTo(const Vector2 & other) const
{
	return (other - normal * distanceTo(other));
}

float Plane2D::distanceTo(const Vector2 & point) const
{
	return (point.dot(normal) - scalar);
}

bool Plane2D::checkCollision(const Vector2 & other) const
{
	return (distanceTo(other) <= 0);
}

bool Plane2D::checkCollision(const Circle& c) const
{
	return (distanceTo(c.getOrigin()) < c.getRadius());
}

bool Plane2D::checkCollision(const Rectangle & r) const
{
	return (distanceTo(r.getTopRight()) <= 0 || distanceTo(r.getBottomLeft()) <= 0 ||
			distanceTo(Vector2(r.getBottomLeft()[0], r.getTopRight()[1])) <= 0 || distanceTo(Vector2(r.getTopRight()[0], r.getBottomLeft()[1])) <= 0);
}
