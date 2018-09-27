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

	void createNavMesh();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	aie::Texture* m_TankBarrelTex;
	aie::Texture* m_SkyeNetTankTex;
	aie::Texture* m_PlayerTankTex;
	aie::Texture* m_MapTex;
	aie::Texture* m_RedDot;

	std::vector<Vector2*> m_MapNodes;

	SceneObject* m_Origin;

	std::vector<Tank*> m_Tanks;

	unsigned int m_TankPoolCount = 1;

	unsigned int m_NodeSpacing = 20;
	unsigned int m_Red = 192, m_Green = 192, m_Blue = 192;

	// Row count starts from the top of the image, therefore the top row = 1 and the bottom row = image height
	// RGB, Red = 0, Green = 1, Blue = 2
	unsigned int getRGB(const aie::Texture* texture, unsigned int xCoord, unsigned int yCoord, unsigned int RGB) const;
	bool isEqualRGB(aie::Texture* texture, unsigned int x, unsigned int y);
	bool isEdge(aie::Texture* texture, unsigned int x, unsigned int y);
};