#include "Circlagon.h"

Circlagon::Circlagon()
{
	m_BaseZone.addChild(&m_SafeZone);
	m_SafeZone.setLocal().scale(0.75, 0.75);
	m_Scale = 1.0f;
	m_IsActive = false;
}

Circlagon::~Circlagon()
{
}

void Circlagon::loadCirclagon()
{
	m_IsActive = true;
}

void Circlagon::updateCirclagon(float deltaTime)
{
	m_Scale -= 0.05f * deltaTime;
}

bool Circlagon::isActive() const
{
	return m_IsActive;
}

Matrix3 Circlagon::getBaseGlobal() const
{
	return m_BaseZone.getGlobal();
}

Matrix3 Circlagon::getSafeGlobal() const
{
	return m_SafeZone.getGlobal();
}

SceneObj* Circlagon::loadThis()
{
	return &m_BaseZone;
}
