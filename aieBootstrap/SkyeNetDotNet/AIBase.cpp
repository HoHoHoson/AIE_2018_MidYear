#include "AIBase.h"

AIBase::AIBase(aie::Texture* tex)
{
	m_Texture = tex;
}

void AIBase::update(float dTime)
{
	Vector4 v = m_Velocity * dTime;
	setLocal().translate(v[0], v[1], v[2], v[3]);
	
	Vector4 newDir(m_Velocity[0], m_Velocity[1], 0, 0);
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

void AIBase::setVelocity(const Vector2 & vector)
{
	m_Velocity[0] = vector[0];
	m_Velocity[1] = vector[1];
}
