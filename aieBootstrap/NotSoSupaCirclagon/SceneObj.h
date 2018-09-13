#pragma once

#include <list>
#include "Matrix3.h"

class SceneObj
{
public:
	SceneObj();
	~SceneObj();

	void updateTransform();

	Vector3& operator[](int index);
	Vector3 operator[](int index) const;
	Matrix3 getLocal() const;
	Matrix3 getGlobal() const;
	Matrix3& setLocal();
	Matrix3& setGlobal();
	void setParent(SceneObj* parent);

	void addChild(SceneObj* child);

private:

	SceneObj * m_Parent;
	std::list<SceneObj*> m_Children;

	Matrix3 m_Global;
	Matrix3 m_Local;
};
