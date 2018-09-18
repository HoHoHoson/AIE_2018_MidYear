#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

class Ant;
class Food;

class SkyeNetDotNetApp : public aie::Application {
public:

	SkyeNetDotNetApp();
	virtual ~SkyeNetDotNetApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	aie::Texture* m_RedAntTex;
	aie::Texture* m_BlueAntTex;
	aie::Texture* m_FoodTex;
	aie::Texture* m_HoleTex;
	aie::Texture* m_RedNest;
	aie::Texture* m_BlueNest;

	std::vector<Ant*> m_Ants;
	std::vector<Food*> m_Food;


	bool m_Add;
	float m_Timer = 0;
};