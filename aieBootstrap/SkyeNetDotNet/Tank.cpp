#include "Tank.h"

Tank::Tank(aie::Texture* skyeNet, aie::Texture* player, aie::Texture* barrel)
{
	m_SkyeNetTexture = skyeNet;
	m_PlayerTexture = player;
	m_BarrelTexture = barrel;

	m_BarrelObj.setLocal()[3][1] = 30;
	m_TurretObj.setLocal()[3] = { 0, -2, 0, 1 };
	m_TurretObj.addChild(&m_BarrelObj);
	addChild(&m_TurretObj);

	m_Team = SkyeNet;
}

Tank::~Tank()
{
}

void Tank::update(float deltaTime, const Vector4& des)
{
	m_TurretObj.setLocal().rotateZ(HLib::toRadian(1));
	AIBase::wanderForce(deltaTime);
	AIBase::update(deltaTime);
}

void Tank::draw(aie::Renderer2D * m_Render)
{
	m_Render->drawSpriteTransformed4x4(m_BarrelTexture, m_BarrelObj.getGlobal(), NULL, NULL, 0.0f);

	switch (m_Team)
	{
	case Tank::Player:
	{
		m_Render->drawSpriteTransformed4x4(m_PlayerTexture, getGlobal(), NULL, NULL, 1.0f);
		break;
	}
	case Tank::SkyeNet:
	{
		m_Render->drawSpriteTransformed4x4(m_SkyeNetTexture, getGlobal(), NULL, NULL, 1.0f);
		break;
	}
	default:
		break;
	}
}

void Tank::setTeam(Team setTo)
{
	m_Team = setTo;
}
