#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include "Tank.h"

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

	aie::Texture* m_TankBarrelTex;
	aie::Texture* m_SkyeNetTankTex;
	aie::Texture* m_PlayerTankTex;

	SceneObject* m_Origin;

	std::vector<Tank*> m_Tanks;

	unsigned int m_TankPoolCount = 1;
};