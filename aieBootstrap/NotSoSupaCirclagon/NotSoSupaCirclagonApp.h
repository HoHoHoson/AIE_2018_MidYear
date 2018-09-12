#pragma once

#include <vector>

#include "Application.h"
#include "Renderer2D.h"

#include "SceneObj.h"
#include "Circlagon.h"

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

	const unsigned int m_RingCount = 1;

	float m_WidthMid;
	float m_HeightMid;
	float m_RotateSpeed = 540;

	SceneObj m_Origin;
	SceneObj m_PlayerOrigin;
	SceneObj m_PlayerPos;
	Circle m_PLayerBounds;
	std::vector<Circlagon*> m_Circlagons;

	float toRadian(float degrees) const;
	bool isInside(const Circle& obj, const Circle& bounds) const;
};