#include "AIBase.h"

AIBase::AIBase(aie::Texture* tex)
{
	m_Texture = tex;
	m_SteeringForce = { 0, 0, 0, 0 };
	m_WanderForce = { 0, 0, 0, 0 };
	m_Velocity = { 0, 0, 0, 0 };
}

void AIBase::update(float deltaTime)
{
	setVelocity(getVelocity() + m_SteeringForce * deltaTime);
	setLocal().translate(getVelocity()[0] * deltaTime, getVelocity()[1] * deltaTime, 0, 0);

	Vector4 newDir(getVelocity()[0], getVelocity()[1], 0, 0);
	float check = MagPow2_2D(Vector4(0,0,0,0), newDir);

	if (check == 0)
		newDir = { 0,1,0,0 };
	else
		newDir.normalise();

	Vector4 cross = newDir.cross(Vector4(getLocal()[2][0], getLocal()[2][1], getLocal()[2][2], getLocal()[2][3]));

	setLocal()[1] = { newDir[0], newDir[1], newDir[2], 0 };
	setLocal()[0] = { cross[0], cross[1], cross[2], 0 };
}

void AIBase::draw(aie::Renderer2D* r)
{
	r->drawSpriteTransformed4x4(m_Texture, getGlobal());
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

Vector4 AIBase::seekForce(const Vector4& dest, bool calledFromSeperateFunction) const
{
	Vector4 force = (dest - getPosition()).normalise() * m_MaxSpeed;
	force = force - getVelocity();

 	if (calledFromSeperateFunction == true)
		return force;
	else
		return force * m_SeekWeight;
}

Vector4 AIBase::fleeForce(const Vector4 & fleeFrom, bool fromSeperateFunction) const
{
	Vector4 force = (getPosition() - fleeFrom).normalise() * m_MaxSpeed;
	force = force - getVelocity();

	if (fromSeperateFunction == true)
		return force;
	else
		return force * m_FleeWeight;
}

Vector4 AIBase::wanderForce(float deltaTime) 
{
	Vector4 temp = { 0,0,0,0 };
	if (MagPow2_2D(temp, getVelocity()) != 0)
		temp = getVelocity().normalise();

	Circle c(getPosition() + temp * m_CicleDistance, m_CircleDiameter);
	Vector4 wanderPoint(0,1,0,0);
	Matrix4 m4;

	m4.setRotateZ(HLib::toRadian(rand() % 360));

	wanderPoint = m4 * wanderPoint;
	wanderPoint *= c.getRadius();
	wanderPoint += Vector4(c.getOrigin()[0], c.getOrigin()[1], 0, 0);

	m_WanderForce += seekForce(wanderPoint, true) * deltaTime;

	return m_WanderForce * m_WanderWeight;
}

Vector4 AIBase::pursuitForce(const Vector4 & hotPursuitPos, const Vector4 & hotPursuitVel) const
{
	return seekForce(hotPursuitPos + hotPursuitVel, true) * m_PursuitWeight;
}

Vector4 AIBase::evadeForce(const Vector4 & evadePos, const Vector4 & evadeVel) const
{
	return fleeForce(evadePos + evadeVel, true) * m_EvadeWeight;
}

void AIBase::arrivalForce(const Vector4 & dest, unsigned int radius, unsigned int offset)
{
	float quotient = (MagPow2_2D(dest, getPosition()) - pow(offset, 2)) / pow(radius, 2);

	if (quotient < 0)
		setVelocity(Vector4(0,0,0,0));
	else if (quotient < 1)
		setVelocity(getVelocity() * quotient);
}

Vector4 AIBase::limitVector(const Vector4& v, float maxValue)
{
	Vector4 temp = v;
	temp.normalise();

	if (MagPow2_2D(v, getPosition()) > MagPow2_2D(temp * maxValue, getPosition()))
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
