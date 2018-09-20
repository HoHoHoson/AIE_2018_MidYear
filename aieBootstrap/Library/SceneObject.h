#pragma once

#include <list>
#include "Matrix4.h"

class SceneObject
{
public:
	SceneObject();
	~SceneObject();

	Matrix4 getLocal() const;
	Matrix4 getGlobal() const;
	Matrix4& setLocal();
	Matrix4& setGlobal();

	void update();
	void setParent(SceneObject* parent = nullptr);
	void addChild(SceneObject* child);

private:

	SceneObject * m_Parent;
	std::list<SceneObject*> m_Children;

	Matrix4 m_Global;
	Matrix4 m_Local;
};
