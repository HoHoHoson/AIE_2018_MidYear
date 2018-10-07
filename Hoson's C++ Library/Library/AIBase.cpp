#include "AIBase.h"

AIBase::AIBase()
{
	m_SteeringForce = { 0, 0, 0, 0 };
	m_Velocity = { 0, 0, 0, 0 };
}

AIBase::~AIBase()
{
}

void AIBase::update(float deltaTime)
{
	setVelocity(getVelocity() + m_SteeringForce * deltaTime);
	setLocal().translate(getVelocity()[0] * deltaTime, getVelocity()[1] * deltaTime, 0, 0);

	m_SteeringForce = { 0,0,0,0 };

	Vector4 newDir(getVelocity()[0], getVelocity()[1], 0, 0);
	float check = HLib::MagPow2_2D(Vector4(0,0,0,0), newDir);

	if (check == 0)
		newDir = { 0,1,0,0 };
	else
		newDir.normalise();

	Vector4 cross = newDir.cross(Vector4(getLocal()[2][0], getLocal()[2][1], getLocal()[2][2], getLocal()[2][3]));

	setLocal()[1] = { newDir[0], newDir[1], newDir[2], 0 };
	setLocal()[0] = { cross[0], cross[1], cross[2], 0 };
}

SceneObject * AIBase::getSceneObj()
{
	return this;
}

void AIBase::setPosition(const Vector4 & position)
{
	setLocal()[3] = position;
}

void AIBase::setVelocity(const Vector4 & vector)
{
	m_Velocity = vector;
}

void AIBase::setMaxSpeed(float newSpeed)
{
	m_MaxSpeed = newSpeed;
}

void AIBase::setMaxForce(float newForce)
{
	m_MaxForce = newForce;
}

void AIBase::setAIRadiusSize(unsigned int newRadius)
{
	m_Radius = newRadius;
}

void AIBase::setWanderCircle(unsigned int circleDistance, unsigned int circleDiameter)
{
	m_CicleDistance = circleDistance;
}

void AIBase::setCollisionDetectDistance(unsigned int newRange)
{
	m_CollisionDetectRange = newRange;
}

Vector4 AIBase::seekForce(const Vector4& dest, bool calledFromSeperateFunction, float weight)
{
	m_SeekWeight = weight;

	Vector4 force = (dest - getPosition()).normalise() * m_MaxSpeed;
	force = force - getVelocity();

 	if (calledFromSeperateFunction != true)
		sumSteerForce(force * m_SeekWeight);

		return force;
}

Vector4 AIBase::fleeForce(const Vector4 & fleeFrom, bool fromSeperateFunction, float weight)
{
	m_FleeWeight = weight;

	Vector4 force = (getPosition() - fleeFrom).normalise() * m_MaxSpeed;
	force = force - getVelocity();

	if (fromSeperateFunction == true)
		sumSteerForce(force * m_FleeWeight);

		return force;
}

void AIBase::wanderForce(float deltaTime, float weight) 
{
	m_WanderWeight = weight;

	Vector4 wanderPoint = { 0,0,0,0 };
	if (HLib::MagPow2_2D(wanderPoint, getVelocity()) != 0)
		wanderPoint = getVelocity().normalise();
	else
		wanderPoint = { 0,1,0,0 };

	Circle c(getPosition() + wanderPoint * (float)m_CicleDistance, m_CircleDiameter);
	Matrix4 m4;

	if (rand() % 100 < 2)
		m_WanderFlip = !m_WanderFlip;

	int flip = 1;
	if (m_WanderFlip == true)
		flip = -1;

	m4.setRotateZ((float)HLib::toRadian((float)(rand() % 15)) * flip);

	wanderPoint = m4 * wanderPoint;
	wanderPoint *= (float)c.getRadius();
	wanderPoint += Vector4(c.getOrigin()[0], c.getOrigin()[1], 0, 0);

	Vector4 wanderForce = seekForce(wanderPoint, true) * m_MaxForce;

	sumSteerForce(wanderForce * m_WanderWeight);
}

void AIBase::pursuitForce(const Vector4 & hotPursuitPos, const Vector4 & hotPursuitVel, float weight)
{
	m_PursuitWeight = weight;

	sumSteerForce(seekForce(hotPursuitPos + hotPursuitVel, true) * m_PursuitWeight);
}

void AIBase::evadeForce(const Vector4 & evadePos, const Vector4 & evadeVel, float weight)
{
	m_EvadeWeight = weight;

	sumSteerForce(fleeForce(evadePos + evadeVel, true) * m_EvadeWeight);
}

void AIBase::arrivalForce(const Vector4 & dest, float radius, float offset, float weight)
{
	m_AvoidanceWeight = weight;

	float quotient = (HLib::MagPow2_2D(dest, getPosition()) - powf(offset, 2)) / powf(radius, 2);

	if (quotient < 0)
		setVelocity(Vector4(0,0,0,0));
	else if (quotient < 1)
		setVelocity(getVelocity() * quotient);
}

void AIBase::sumSteerForce(const Vector4 & addForce)
{
		m_SteeringForce += addForce;
}

Vector4 AIBase::limitVector(const Vector4& v, float maxValue)
{
	Vector4 temp = v;
	temp.normalise();

	float velocityLength = HLib::MagPow2_2D(v, Vector4());
	float limitLength = HLib::MagPow2_2D(temp * maxValue, Vector4());

	if (velocityLength > limitLength)
		return temp * maxValue;
	else
		return v;
}

Vector4 AIBase::getPosition() const
{
	return SceneObject::getGlobal()[3];
}

Vector4 AIBase::getVelocity() const
{
	return m_Velocity;
}
