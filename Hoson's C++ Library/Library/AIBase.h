#pragma once

#include "SceneObject.h"
#include "2D_Collision.h"


class AIBase : public SceneObject
{
public:
	AIBase();
	~AIBase();

	void update(float deltaTime);

	void setPosition(const Vector4& position);
	void setVelocity(const Vector4& vector);
	void setMaxSpeed(float newSpeed);
	void setMaxForce(float newForce);
	void setAIRadiusSize(unsigned int newRadius);
	void setWanderCircle(unsigned int circleDistance = 0, unsigned int circleDiameter = 0);
	void setCollisionDetectDistance(unsigned int newRange);

	Vector4 getPosition() const;
	Vector4 getVelocity() const;
	SceneObject* getSceneObj();

	Vector4 seekForce(const Vector4& destination, bool calledFromSeperateFunction = false, float weight = 1);
	Vector4 fleeForce(const Vector4& fleeFrom, bool fromSeperateFunction = false, float weight = 1);
	void wanderForce(float deltaTime, float weight = 1);
	void pursuitForce(const Vector4 & hotPursuitPos, const Vector4 & hotPursuitVel, float weight = 1);
	void evadeForce(const Vector4 & evadePos, const Vector4 & evadeVel, float weight = 1);
	void arrivalForce(const Vector4& dest, float radius, float offset = 0, float weight = 1);

	template<typename T>
	Vector4 collisionAvoidance(const T& objBounds);

private:

	float m_SeekWeight;
	float m_FleeWeight;
	float m_WanderWeight;
	float m_PursuitWeight;
	float m_EvadeWeight;
	float m_AvoidanceWeight;

	Vector4 m_Velocity;
	Vector4 m_SteeringForce;

	bool m_WanderFlip = false;
	float m_MaxSpeed = 50;
	float m_MaxForce = 50;
	unsigned int m_Radius = 0;
	unsigned int m_CicleDistance = 100;
	unsigned int m_CircleDiameter = 15;
	unsigned int m_CollisionDetectRange = 50;

	void sumSteerForce(const Vector4& addForce);
	Vector4 limitVector(const Vector4& vector, float maxValue);
};

template<typename T>
inline Vector4 AIBase::collisionAvoidance(const T & objBounds)
{
	unsigned int dynamicLength = HLib::MagPow2_2D(Vector4(), getVelocity()) / m_MaxSpeed;
	Vector4 avoidanceForce;
	Ray2D detectorRay(getPosition(), getPosition() + getVelocity().normalise() * dynamicLength, dynamicLength);

	if (detectorRay.checkCollision(objBounds) == true)
	{
		Vector2 l = (detectorRay.getDirection() * detectorRay.getLength()) - objBounds.getOrigin();
		l.normalise() *= m_MaxForce;
		avoidanceForce = avoidanceForce + Vector4(l[0], l[1], 0, 0);
	}
	if (objBounds.checkCollision(Circle(getPosition(), m_Radius)) == true)
	{
		avoidanceForce = avoidanceForce + fleeForce(Vector4(objBounds.getOrigin()[0], objBounds.getOrigin()[1], 0, 0));
	}

	return avoidanceForce;
}
