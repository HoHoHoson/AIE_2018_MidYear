#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace aie
{
	class Texture;
	class Renderer2D;
}

class Agent
{
public:
	Agent(aie::Texture* tex);

	void setPosition(const Vector2& pos);
	void setVelocity(const Vector2& pos);

	Vector2 getPosition() const;
	Vector2 getVelocity() const;

	void update(float deltaTime);
	void render(aie::Renderer2D* renderer);

private:

	void updateFacing();

	Matrix4 m_Transform;
	Vector2 m_Velocity;

	aie::Texture* m_Texture;
};
