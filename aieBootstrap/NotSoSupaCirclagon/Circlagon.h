#pragma once

#include "Matrix3.h"
#include "SceneObj.h"

class Circlagon
{
public:
	Circlagon();
	~Circlagon();

	void loadCirclagon();
	void updateCirclagon(float deltaTime);

	bool isActive() const;
	Matrix3 getBaseGlobal() const;
	Matrix3 getSafeGlobal() const;
	SceneObj* loadThis();

private:

	bool m_IsActive;
	float m_Scale;

	SceneObj m_BaseZone;
	SceneObj m_SafeZone;
};
