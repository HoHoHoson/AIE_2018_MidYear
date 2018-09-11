#include "Circlagon.h"

Circlagon::Circlagon()
{
	m_BaseZone.addChild(&m_SafeZone);
	m_SafeZone.setLocal().scale(0.75, 0.75);
	m_IsActive = false;
}

Circlagon::~Circlagon()
{
}

void Circlagon::loadCirclagon()
{
	m_IsActive = true;
	m_Scale = 10;
}

void Circlagon::updateCirclagon(float deltaTime)
{
	m_Scale -= 1 * deltaTime;
	m_BaseZone.setLocal().setIdentity();
	m_BaseZone.setLocal().scale(m_Scale, m_Scale);
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

SceneObj* Circlagon::loadThis()
{
	return &m_BaseZone;
}
