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

Vector3 & SceneObj::operator[](int index)
{
	return m_Local[index];
}

Vector3 SceneObj::operator[](int index) const
{
	return m_Local[index];
}

Matrix3  SceneObj::getLocal() const
{
	return m_Local;
}

Matrix3 SceneObj::getGlobal() const
{
	return m_Global;
}

Matrix3 & SceneObj::setLocal()
{
	return m_Local;
}

Matrix3 & SceneObj::setGlobal()
{
	return m_Global;
}

void SceneObj::setParent(SceneObj * parent)
{
	m_Parent = parent;
}

void SceneObj::addChild(SceneObj* child)
{
	child->setParent(this);
	child->getGlobal() = m_Global;
	m_Children.push_front(child);
}
