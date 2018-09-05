#pragma once

#include <list>
#include "Matrix3.h"

class SceneObj
{
public:
	SceneObj();
	~SceneObj();

	void updateObj(float deltaTime);
	void updateTransform();

	Matrix3& getGlobal();
	Matrix3& getLocal();
	void addChild(SceneObj& child);

private:

	SceneObj * m_Parent;
	std::list<SceneObj*> m_Children;

	Matrix3 m_Global;
	Matrix3 m_Local;
};
