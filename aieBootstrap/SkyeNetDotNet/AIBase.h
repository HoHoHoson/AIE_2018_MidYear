#pragma once

#include <set>
#include "Renderer2D.h"
#include "SceneObject.h"
#include "Vector2.h"

namespace aie
{
	class Texture;
}

class AIBase : SceneObject
{
public:
	AIBase(aie::Texture* tex);

	void update(float deltaTime);
	void draw(aie::Renderer2D* r);

	void setVelocity(const Vector2& vector);

	SceneObject* getSceneObj();

private:

	std::set<Vector4> test;

	aie::Texture* m_Texture;

	Vector4 m_Velocity;
	Vector4 m_SteeringForce;
};