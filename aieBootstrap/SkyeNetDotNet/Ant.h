#pragma once
#include "Agent.h"
#include "2D_Collision.h"
#include "Algorithms.h"
#include "Matrix2.h"

class Ant : public Agent
{
public:
	enum Team
	{
		Red,
		Blue
	};

	Ant(Team team, aie::Texture* texture) : Agent(texture)
	{
		m_Team = team;
	}

	Team getTeam() const { return m_Team; }

	void update(float deltaTime)
	{
		switch (m_State)
		{
		case Ant::Wander:
		{
			m_M2.setIdentity();
			m_M2.setRotate(HLib::toRadian(rand() % 360));
			Vector2 v2 = m_M2 * getVelocity().normalise();
			v2 *= 50;
			v2 -= getPosition();
			setVelocity(v2.normalise() * 25);
		}
		default:
			break;
		}
		Agent::update(deltaTime);
	}

private:

	Team m_Team;

	enum State
	{
		Wander,
		Seek
	};
	State m_State = Wander;
	Matrix2 m_M2;
};
