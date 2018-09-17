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

	void update(float deltaTime, const Vector2& destination)
	{
		switch (m_State)
		{
		case Ant::Wander:
		{
			Circle c(getPosition() + getVelocity().normalise() * 100, 200);
			Vector2 wanderPoint(0, 1);

			m_M2.setIdentity();
			m_M2.setRotate(HLib::toRadian(rand() % 360));

			wanderPoint = m_M2 * wanderPoint;
			wanderPoint *= c.getRadius();
			wanderPoint += c.getOrigin();

			wanderPoint = (wanderPoint - getPosition()).normalise() * m_Speed;
			moveBy(wanderPoint - getVelocity());

			break;
		}

		case Ant::Seek:
		{
			Vector2 dir = (destination - getPosition()).normalise() * m_Speed;
			dir = dir - getVelocity();
			moveBy(dir);
			break;
		}

		default:
			break;
		}
		Agent::update(deltaTime);
	}

	void moveBy(const Vector2& dest)
	{

		setVelocity(dest + getVelocity());
	}

	Vector2 limitSpeed(const Vector2& vel)
	{
		Vector2 temp = vel;
		temp.normalise();

		if (MagPow2_2D(vel, getPosition()) > MagPow2_2D(temp * m_Speed, getPosition()))
		{
			return temp * m_Speed;
		}
		else
			return vel;
	}

private:

	int m_Speed = 100;
	Team m_Team;

	enum State
	{
		Wander,
		Seek
	};
	State m_State = Wander;
	Matrix2 m_M2;
};
