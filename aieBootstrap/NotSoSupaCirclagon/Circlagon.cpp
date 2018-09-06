#include "Circlagon.h"

Circlagon::Circlagon()
{
	m_BaseZone.addChild(m_SafeZone);

	m_IsActive = false;
}

Circlagon::~Circlagon()
{
}

void Circlagon::updateCirclagon(float deltaTime)
{

}
