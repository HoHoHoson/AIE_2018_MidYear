
// This main.cpp is for testing if different parts of my library are functional

#include <iostream>

// Add header files here
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "2D_Collision.h"
#include "Algorithms.h"
#include "SceneObject.h"
#include "AIBase.h"


int main()
{
	Vector2 v2a(3, 4);
	Vector3 v3a(1, 2, 3);
	Vector4 v4a(1, 2, 3, 4);
	Matrix2 m2a(
		1.1f, 1.2f, 
		2.1f, 2.2f);
	Matrix3 m3a(
		1.1f, 1.2f, 1.3f, 
		2.1f, 2.2f, 2.3f, 
		3.1f, 3.2f, 3.3f);
	Matrix4 m4a(
		1.1f, 1.2f, 1.3f, 1.4f, 
		2.1f, 2.2f, 2.3f, 2.4f, 
		3.1f, 3.2f, 3.3f, 3.4f, 
		4.1f, 4.2f, 4.3f, 4.4f);
	Rectangle r1(Vector2(0, 0), 10, 10);
	Circle c1(Vector2(0, 0), 200);
	Plane2D p1(Vector2(0, 4), Vector2(4, 0));
	Ray2D ray1(Vector2(100, 100), Vector2(0, 0));
	double f = -10.2525f;
	double round = HLib::roundTo(f, 2);
	SceneObject origin;
	SceneObject soTest;
	float magTest = HLib::MagPow2_2D(v2a, Vector2());
	AIBase AlDusty;

	origin.addChild(&soTest);
	origin.update();
	Vector4 truetest(0, 0, 0, 0);
	if (truetest == v4a)
	{
	}
	else
		if (v4a != truetest)
		{
			truetest = v4a;
		}

	float dgs = HLib::toDegrees(atan2(0, 2) - atan2(2,2));
	c1.updateCircle(v4a, 10);
	r1.updateRect(v4a + Vector4(15,15,0,0), 6, 6);
	m2a.scale(2, 2);
	m3a.scale(2, 2, 2);
	m3a.translate(10, 10, 10);
	m4a.scale(2, 2, 2, 2);
	m4a.translate(10, 10, 10, 10);
	if (p1.checkCollision(Vector2(10, 10)))
		std::cout << "Kaboom\n";
	else
		std::cout << "Never touched\n";

	return 0;
}