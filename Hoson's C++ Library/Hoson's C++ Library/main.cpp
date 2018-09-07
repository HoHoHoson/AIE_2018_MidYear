
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

int main()
{
	Vector2 v2a(1, 2);
	Vector3 v3a(1, 2, 3);
	Vector4 v4a(1, 2, 3, 4);
	Matrix2 m2a(
		1.1, 1.2, 
		2.1, 2.2);
	Matrix3 m3a(
		1.1, 1.2, 1.3, 
		2.1, 2.2, 2.3, 
		3.1, 3.2, 3.3);
	Matrix4 m4a(
		1.1, 1.2, 1.3, 1.4, 
		2.1, 2.2, 2.3, 2.4, 
		3.1, 3.2, 3.3, 3.4, 
		4.1, 4.2, 4.3, 4.4);
	Rectangle r1(Vector2(0, 0), 3, 3);
	Circle c1(Vector2(0, 0), 2);
	Plane2D p1(Vector2(4, 0), Vector2(0, 4));

	m2a.scale(2, 2);
	m3a.scale(2, 2, 2);
	m3a.translate(10, 10, 10);
	m4a.scale(2, 2, 2, 2);
	m4a.translate(10, 10, 10, 10);
	if (p1.collisionRectangle(r1))
		std::cout << "Kaboom\n";
	else
		std::cout << "Tips never touched\n";


	return 0;
}