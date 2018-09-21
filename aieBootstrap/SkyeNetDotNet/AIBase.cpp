#include "AIBase.h"

AIBase::AIBase(aie::Texture* tex)
{
	m_Texture = tex;
	m_SteeringForce = { 0, 0, 0, 0 };
	m_Velocity = { 25, 25, 1, 1 };
	m_WanderForce = { 0, 0, 0, 0 };
}

void AIBase::update(float dTime)
{
	setVelocity(limitVector(getVelocity() + limitVector(m_SteeringForce, m_MaxForce), m_MaxSpeed) * dTime);
	setLocal().translate(getVelocity()[0], getVelocity()[1], 0, 0);

	Vector4 newDir(getVelocity()[0], getVelocity()[1], 0, 0);
	newDir.normalise();

	Vector4 cross = newDir.cross(Vector4(setLocal()[2][0], setLocal()[2][1], setLocal()[2][2], setLocal()[2][3]));

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
	Vector4 dir = (dest - getPosition()).normalise() * m_MaxSpeed;
	dir = dir - getVelocity();

 	if (calledFromSeperateFunction == true)
		return dir;
	else
		return dir * m_SeekWeight;
}

Vector4 AIBase::fleeForce(const Vector4 & fleeFrom) const
{
	Vector4 f = seekForce(fleeFrom, true);

	return Vector4(-f[0], -f[1], -f[2], -f[3]) * m_FleeWeight;
}

Vector4 AIBase::wanderForce(float deltaTime) 
{
	Circle c(getPosition() + getVelocity().normalise() * m_CicleDistance, m_CircleDiameter);
	Vector4 wanderPoint(0,1,0,0);
	Matrix4 m4;

	m4.setRotateZ(HLib::toRadian(rand() % 360));

	wanderPoint = m4 * wanderPoint;
	wanderPoint *= c.getRadius();
	wanderPoint += Vector4(c.getOrigin()[0], c.getOrigin()[1], 0, 0);

	wanderPoint = (wanderPoint - getPosition()).normalise() * m_MaxSpeed - (Vector4(c.getOrigin()[0], c.getOrigin()[1], 0, 0) - getPosition()).normalise() * m_MaxSpeed;
	m_WanderForce += (wanderPoint - getVelocity()) * deltaTime;
	m_WanderForce = limitVector(m_WanderForce, m_MaxForce);

	return m_WanderForce * m_WanderWeight;
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
