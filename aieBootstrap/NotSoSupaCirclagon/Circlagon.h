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

private:

	bool m_IsActive;

	SceneObj m_BaseZone;
	SceneObj m_SafeZone;
};
