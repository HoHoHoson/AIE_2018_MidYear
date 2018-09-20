#include "SceneObject.h"

SceneObject::SceneObject()
{
	m_Parent = nullptr;
}

SceneObject::~SceneObject()
{
}

Matrix4 SceneObject::getLocal() const
{
	return m_Local;
}

Matrix4 SceneObject::getGlobal() const
{
	return m_Global;
}

Matrix4 & SceneObject::setLocal()
{
	return m_Local;
}

Matrix4 & SceneObject::setGlobal()
{
	return m_Global;
}

void SceneObject::update()
{
	if (m_Parent == nullptr)
		m_Global = m_Local;
	else
		m_Global = m_Parent->getGlobal() * m_Local;

	for (auto c : m_Children)
		c->update();
}

void SceneObject::setParent(SceneObject* parent)
{
	m_Parent = parent;
}

void SceneObject::addChild(SceneObject * child)
{
	child->setParent(this);
	m_Children.push_back(child);
}

