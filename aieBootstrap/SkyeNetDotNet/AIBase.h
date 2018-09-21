#pragma once

#include <set>
#include "Renderer2D.h"
#include "SceneObject.h"
#include "2D_Collision.h"

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

	void setPosition(const Vector4& position);
	void setVelocity(const Vector4& vector);
	Vector4 seekForce(const Vector4& destination, bool calledFromSeperateFunction = false) const;
	Vector4 fleeForce(const Vector4& fleeFrom) const;
	Vector4 wanderForce(float deltaTime);

	Vector4 limitVector(const Vector4& vector, float maxValue);
	Vector4 getPosition() const;
	Vector4 getVelocity() const;
	SceneObject* getSceneObj();

	Vector4 m_SteeringForce;
private:

	enum States 
	{
		Seek,
		Wander
	};
	std::set<States> m_StateFlags;

	float m_SeekWeight = 1;
	float m_FleeWeight = 1;
	float m_WanderWeight = 1;

	aie::Texture* m_Texture;

	Vector4 m_Velocity;

	float m_MaxSpeed = 50;
	float m_MaxForce = 40;
	unsigned int m_CicleDistance = 100;
	unsigned int m_CircleDiameter = 100;
	Vector4 m_WanderForce;
};