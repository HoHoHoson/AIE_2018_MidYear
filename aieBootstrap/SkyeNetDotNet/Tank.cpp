#include "Tank.h"

Tank::Tank(aie::Texture* skyeNet, aie::Texture* player, aie::Texture* barrel)
{
	m_SkyeNetTexture = skyeNet;
	m_PlayerTexture = player;
	m_BarrelTexture = barrel;

	m_BarrelObj.setLocal()[3][1] = 55;
	m_TurretObj.setLocal()[3] = { 0, -2, 0, 1 };
	m_TurretObj.addChild(&m_BarrelObj);
	addChild(&m_TurretObj);

	m_Team = SkyeNet;
	m_state = find;
	homeVec = { 50, 670 };
	AIBase::setMaxSpeed(100);
}

Tank::~Tank()
{
}

void Tank::update(float deltaTime, const Vector4& des)
{
	switch (m_state)
	{
	case Tank::find:
	{
		if (m_Pathfind.empty() == false)
		{
			seekForce(Vector4(m_Pathfind.back()[0], m_Pathfind.back()[1], 0, 0));
			Circle destination(m_Pathfind.back(), 15);

			if (destination.checkCollision(Circle(AIBase::getPosition(), 50)))
			{
				m_Pathfind.pop_back();
			}
		}
		break;
	}
	case Tank::home:
	{
		if (m_Pathfind.empty() == false)
		{
			seekForce(Vector4(m_Pathfind.back()[0], m_Pathfind.back()[1], 0, 0));
			Circle destination(m_Pathfind.back(), 15);

			if (destination.checkCollision(Circle(AIBase::getPosition(), 50)))
			{
				m_Pathfind.pop_back();
			}
		}

		Circle homeBound(homeVec, 20);
		if (homeBound.checkCollision(Circle(AIBase::getPosition(), 30)))
		{
			m_Pathfind.clear();
			m_state = find;
		}
		break;
	}
	default:
		break;
	}

	AIBase::update(deltaTime);
}

void Tank::draw(aie::Renderer2D * m_Render)
{
	m_Render->drawSprite(m_PlayerTexture, homeVec[0], homeVec[1], NULL, NULL, NULL, 50.0f);

	if (m_state == home)
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

std::list<Vector2>& Tank::setPath()
{
	return m_Pathfind;
}
