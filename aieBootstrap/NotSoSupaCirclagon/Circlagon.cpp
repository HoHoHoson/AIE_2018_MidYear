#include "Circlagon.h"

Circlagon::Circlagon()
{
}

Circlagon::Circlagon(unsigned int baseSize)
{
	m_IsActive = false;

	m_BaseZone.addChild(&m_SafeZone);
	m_BaseZone.addChild(&m_ExitZone);

	m_SafeZone.setLocal().scale(0.85, 0.85);
	m_ExitZone.setLocal().scale(0.5, 0.5);
	m_ExitZone.setLocal().translate(0, 10);

	m_BaseSize = baseSize;
	m_SafeSize = baseSize * 0.85;
	m_ExitSize = baseSize * 0.5;

	m_BaseBounds = { m_BaseZone.getGlobal()[2], (unsigned int)(m_BaseSize * m_Scale) };
	m_SafeBounds = { m_SafeZone.getGlobal()[2], (unsigned int)(m_SafeSize * m_Scale) };
	m_ExitBounds = { m_ExitZone.getGlobal()[2], (unsigned int)(m_ExitSize * m_Scale) };
}

Circlagon::~Circlagon()
{
}

void Circlagon::loadCirclagon()
{
	m_IsActive = true;
	m_Scale = 20;
}

void Circlagon::updateCirclagon(float deltaTime)
{
	m_Scale -= 1 * deltaTime;
	m_BaseZone.setLocal().setIdentity();
	m_BaseZone.setLocal().scale(m_Scale, m_Scale);

	m_BaseBounds.updateCircle(m_BaseZone.getGlobal()[2], m_BaseSize * m_Scale);
	m_SafeBounds.updateCircle(m_SafeZone.getGlobal()[2], m_SafeSize * m_Scale);
	m_ExitBounds.updateCircle(m_ExitZone.getGlobal()[2], m_ExitSize * m_Scale);
}

bool Circlagon::isActive() const
{
	return m_IsActive;
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
