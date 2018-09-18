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
	enum State
	{
		Wander,
		Seek,
		Home
	};

	Ant(Team team, aie::Texture* texture) : Agent(texture)
	{
		m_Team = team;
		switch (m_Team)
		{
		case Ant::Red:
		{
			m_Home = Vector2(100, 100);
			break;
		}
		case Ant::Blue:
		{
			m_Home = Vector2(1180, 620);
			break;
		}
		default:
			break;
		}
		setPosition(m_Home);
	}

	Team getTeam() const { return m_Team; }

	void update(float deltaTime, const Vector2& destination)
	{
		switch (m_State)
		{
		case Ant::Wander:
		{
			Circle c(getPosition() + getVelocity().normalise() * m_WanderCircleDistance, m_WanderCircleWidth);
			Vector2 wanderPoint(0, 1);

			m_M2.setIdentity();
			m_M2.setRotate(HLib::toRadian(rand() % 360));

			wanderPoint = m_M2 * wanderPoint;
			wanderPoint *= c.getRadius();
			wanderPoint += c.getOrigin();

			Vector2 force = (wanderPoint - getPosition()).normalise() * m_MaxSpeed;
			force = force - getVelocity();
			m_WanderForce += force * deltaTime;
			setVelocity(getVelocity() + limitVector(m_WanderForce, m_MaxForce) * deltaTime);

			break;
		}
		case Ant::Seek:
		{
			moveTo(destination, deltaTime);
			break;
		}
		case Ant::Home:
		{
			if (MagPow2_2D(m_Home, getPosition()) > pow(20, 2))
				moveTo(m_Home, deltaTime);
			else
			{
				setVelocity(getVelocity() * (MagPow2_2D(m_Home, getPosition()) / pow(20, 2)));
				moveTo(m_Home, deltaTime);
				if (MagPow2_2D(m_Home, getPosition()) < pow(15, 2))
					m_State = Wander;
			}
		}
		default:
			break;
		}
		Agent::update(deltaTime);
	}

	void moveTo(const Vector2& dest, float dTime)
	{
		Vector2 dir = (dest - getPosition()).normalise() * m_MaxSpeed;
		dir = dir - getVelocity();

		setVelocity(getVelocity() + limitVector(dir, m_MaxForce) * dTime);
	}

	Vector2 limitVector(const Vector2& vel, int maxVal)
	{
		Vector2 temp = vel;
		temp.normalise();

		if (MagPow2_2D(vel, getPosition()) > MagPow2_2D(temp * maxVal, getPosition()))
			return temp * maxVal;
		else
			return vel;
	}

	void setState(const State& switchTo)
	{
		m_State = switchTo;
	}

	State getState() const
	{
		return m_State;
	}
	
private:

	int m_MaxSpeed = 50;
	int m_MaxForce = 40;
	int m_WanderCircleWidth = 100;
	int m_WanderCircleDistance = 100;

	Team m_Team;
	State m_State = Wander;
	Vector2 m_Home;
	Matrix2 m_M2;
	Vector2 m_WanderForce = { 0,0 };
};
