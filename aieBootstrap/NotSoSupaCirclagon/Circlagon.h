#pragma once

#include "2D_Collision.h"
#include "SceneObj.h"

class Circlagon
{
public:
	Circlagon();
	Circlagon(unsigned int baseSize);
	~Circlagon();

	void loadCirclagon();
	void updateCirclagon(float deltaTime);

	bool& isOut();
	bool& isActive();
	float getScale()		const;
	Matrix3 getBaseGlobal() const;
	Matrix3 getSafeGlobal() const;
	Matrix3 getExitGlobal() const;
	Circle getBaseBounds()	const;
	Circle getSafeBounds()  const;
	Circle getExitBounds()  const;

	SceneObj* loadThis();

private:

	bool m_IsOut;
	bool m_IsActive;
	float m_Scale;

	const unsigned int m_SetScale = 27;
	unsigned int m_BaseSize;
	unsigned int m_SafeSize;
	unsigned int m_ExitSize;

	SceneObj m_BaseZone;
	SceneObj m_SafeZone;
	SceneObj m_ExitZone;

	Circle m_BaseBounds;
	Circle m_SafeBounds;
	Circle m_ExitBounds;
};
