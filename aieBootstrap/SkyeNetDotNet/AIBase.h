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

	Vector4 getPosition() const;
	Vector4 getVelocity() const;
	SceneObject* getSceneObj();

	Vector4 seekForce(const Vector4& destination, bool calledFromSeperateFunction = false) const;
	Vector4 fleeForce(const Vector4& fleeFrom, bool fromSeperateFunction = false) const;
	Vector4 wanderForce(float deltaTime);
	Vector4 pursuitForce(const Vector4 & hotPursuitPos, const Vector4 & hotPursuitVel) const;
	Vector4 evadeForce(const Vector4 & evadePos, const Vector4 & evadeVel) const;
	void arrivalForce(const Vector4& dest, unsigned int radius, unsigned int offset = 0);

	template<typename T>
	Vector4 collisionAvoidance(const T& objBounds);

	Vector4 m_SteeringForce;
private:

	enum States 
	{
		Seek,
		Flee,
		Wander,
		Pursuit,
		Evade,
		Arrival
	};
	std::set<States> m_StateFlags;

	float m_SeekWeight = 1;
	float m_FleeWeight = 1;
	float m_WanderWeight = 1;
	float m_PursuitWeight = 1;
	float m_EvadeWeight = 1;
	float m_AvoidanceWeight = 1;

	aie::Texture* m_Texture;

	Vector4 m_Velocity;
	Vector4 m_WanderForce;

	float m_MaxSpeed = 50;
	float m_MaxForce = 40;
	unsigned int m_CicleDistance = 50;
	unsigned int m_CircleDiameter = 100;
	unsigned int m_AIRadius = 0;
	unsigned int m_CollisionDetectRange = 50;

	Vector4 limitVector(const Vector4& vector, float maxValue);
};

template<typename T>
inline Vector4 AIBase::collisionAvoidance(const T & objBounds)
{
	Vector4 avoidanceForce;
	unsigned int dynamicLength = MagPow2_2D(Vector4(), getVelocity()) / m_MaxSpeed;
	Ray2D detectorRay(getPosition(), getPosition() + getVelocity().normalise() * dynamicLength, dynamicLength);

	if (detectorRay.checkCollision(objBounds) == true)
	{
		Vector2 l = (detectorRay.getDirection() * detectorRay.getLength()) - objBounds.getOrigin();
		l.normalise() *= m_MaxForce;
		avoidanceForce = avoidanceForce + Vector4(l[0], l[1], 0, 0);
	}
	if (objBounds.checkCollision(Circle(getPosition(), m_AIRadius)) == true)
	{
		avoidanceForce = avoidanceForce + fleeForce(Vector4(objBounds.getOrigin()[0], objBounds.getOrigin()[1], 0, 0));
	}

	return avoidanceForce;
}
