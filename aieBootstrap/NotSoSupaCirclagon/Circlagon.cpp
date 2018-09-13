#include "Circlagon.h"

Circlagon::Circlagon()
{
}

Circlagon::Circlagon(unsigned int baseSize, float& scaleSp)
{
	m_IsActive = false;
	m_ScaleSp = &scaleSp;

	m_BaseZone.addChild(&m_SafeZone);
	m_BaseZone.addChild(&m_ExitZone);

	m_SafeZone.setLocal().scale(0.85, 0.85);
	m_ExitZone.setLocal().translate(0, 15);
	m_ExitZone.setLocal().scale(0.53, 0.53);

	m_BaseSize = baseSize;
	m_SafeSize = baseSize * 0.85;
	m_ExitSize = baseSize * 0.53;

	m_BaseBounds = { m_BaseZone.getGlobal()[2], (unsigned int)(m_BaseSize) };
	m_SafeBounds = { m_SafeZone.getGlobal()[2], (unsigned int)(m_SafeSize) };
	m_ExitBounds = { m_ExitZone.getGlobal()[2], (unsigned int)(m_ExitSize) };
}

Circlagon::~Circlagon()
{
}

void Circlagon::loadCirclagon(float startingAngle, float RotateSpeed)
{
	m_IsActive = true;
	m_IsOut = false;
	m_Scale = m_SetScale;
	m_Angle = startingAngle;
	m_RotateSpeed = RotateSpeed;
}

void Circlagon::updateCirclagon(float deltaTime)
{
	m_Scale -= *m_ScaleSp * deltaTime;
	m_Angle += m_RotateSpeed * deltaTime;
	m_BaseZone.setLocal().setIdentity();
	m_BaseZone.setLocal().scale(m_Scale, m_Scale);

	m_BaseZone.setLocal().rotateZ(HLib::toRadian(m_Angle));

	updateCircle();
}

bool& Circlagon::isActive()
{
	return m_IsActive;
}

bool& Circlagon::isOut()
{
	return m_IsOut;
}

float Circlagon::getScale() const
{
	return m_Scale;
}

Matrix3 Circlagon::getBaseGlobal() const
{
	return m_BaseZone.getGlobal();
}

Matrix3 Circlagon::getSafeGlobal() const
{
	return m_SafeZone.getGlobal();
}

Matrix3 Circlagon::getExitGlobal() const
{
	return m_ExitZone.getGlobal();
}

Circle Circlagon::getBaseBounds() const
{
	return m_BaseBounds;
}

Circle Circlagon::getSafeBounds() const
{
	return m_SafeBounds;
}

Circle Circlagon::getExitBounds() const
{
	return m_ExitBounds;
}

SceneObj* Circlagon::loadThis()
{
	return &m_BaseZone;
}

void Circlagon::updateCircle()
{
	m_BaseBounds.updateCircle(m_BaseZone.getGlobal()[2], m_BaseSize * m_Scale);
	m_SafeBounds.updateCircle(m_SafeZone.getGlobal()[2], m_SafeSize * m_Scale);
	m_ExitBounds.updateCircle(m_ExitZone.getGlobal()[2], m_ExitSize * m_Scale);
}
