#include "Agent.h"
#include "Renderer2D.h"

Agent::Agent(aie::Texture * tex)
{
	m_Texture = tex;
	m_Transform = m_Transform.setIdentity();
}

void Agent::setPosition(const Vector2 & pos)
{
	m_Transform[3] = Vector4( pos[0], pos[1], 0, 1 );
}

void Agent::setVelocity(const Vector2 & pos)
{
	m_Velocity = pos;
}

Vector2 Agent::getPosition() const
{
	return Vector2(m_Transform[3][0], m_Transform[3][1]);
}

Vector2 Agent::getVelocity() const
{
	return m_Velocity;
}

void Agent::update(float deltaTime)
{
	Vector2 vDelta = m_Velocity * deltaTime;
	m_Transform[3] += Vector4(vDelta[0], vDelta[1], 0, 0);
	updateFacing();
}

void Agent::render(aie::Renderer2D * renderer)
{
	renderer->drawSpriteTransformed4x4(m_Texture, m_Transform);
}

void Agent::updateFacing()
{
	Vector3 newDir(m_Velocity[0], m_Velocity[1], 0);
	newDir.normalise();

	if (newDir.magnitude() == 0)
		newDir = { 0, 1, 0 };

	Vector3 cross = newDir.cross(Vector3(m_Transform[2][0], m_Transform[2][1], m_Transform[2][2]));

	m_Transform[1] = { newDir[0], newDir[1], newDir[2], 0 };
	m_Transform[0] = { cross[0], cross[1], cross[2], 0 };
}
