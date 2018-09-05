#include "SceneObj.h"

SceneObj::SceneObj()
{
	m_Parent = nullptr;
}

SceneObj::~SceneObj()
{
}

void SceneObj::updateObj(float deltaTime)
{
	updateTransform();
}

void SceneObj::updateTransform()
{
	if (m_Parent != nullptr)
		m_Global = m_Parent->m_Global * m_Local;
	else
		m_Global = m_Local;

	for (auto child : m_Children)
		child->updateTransform();
}

Matrix3& SceneObj::getGlobal()
{
	return m_Global;
}

Matrix3 & SceneObj::getLocal()
{
	return m_Local;
}

void SceneObj::addChild(SceneObj& child)
{
	child.m_Parent = this;
	child.m_Global = m_Global;
	m_Children.push_front(&child);
}
