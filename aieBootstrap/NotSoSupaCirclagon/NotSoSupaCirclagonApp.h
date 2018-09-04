#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "SceneObj.h"
#include "AvoidObj.h"


class NotSoSupaCirclagonApp : public aie::Application {
public:

	NotSoSupaCirclagonApp();
	virtual ~NotSoSupaCirclagonApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	aie::Texture* m_PlayerTex;
	aie::Texture* m_CircleTex;
	aie::Texture* m_SafeTex;

	float m_WidthMid;
	float m_HeightMid;
	float degrees = 0;

	SceneObj m_Origin;
	SceneObj* m_PlayerPos = new SceneObj;

	float toRadian(float degrees);
	bool isInside(const aie::Texture* s_Obj, Matrix3& s_M, const aie::Texture* l_Obj, Matrix3& l_M, float l_Multi);
};