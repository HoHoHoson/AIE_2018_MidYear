#include "SkyeNetDotNetApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <time.h>

SkyeNetDotNetApp::SkyeNetDotNetApp() 
{
	srand((unsigned int)time(nullptr));
}

SkyeNetDotNetApp::~SkyeNetDotNetApp() {

}

bool SkyeNetDotNetApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_TankBarrelTex = new aie::Texture("../bin/textures/barrelBeige.png");
	m_SkyeNetTankTex = new aie::Texture("../bin/textures/tankYellow.png");
	m_PlayerTankTex = new aie::Texture("../bin/textures/tankBlue.png");
	m_MapTex = new aie::Texture("../bin/textures/map.png");
	m_RedDot = new aie::Texture("../bin/textures/redDot.png");

	createNavMesh();

	for (size_t i = 0; i < m_TankPoolCount; ++i)
	{
		Tank* newTank = new Tank(m_SkyeNetTankTex, m_PlayerTankTex, m_TankBarrelTex);

		newTank->setPosition(Vector4(getWindowWidth() / 2, getWindowHeight() / 2, 0, 0));
		m_Tanks.push_back(newTank);
	}

	m_Origin = new SceneObject;
	m_Origin->addChild(m_Tanks.at(0)->getSceneObj());

	return true;
}

void SkyeNetDotNetApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void SkyeNetDotNetApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	HLib::clamp(deltaTime, 0, 0.1);

	for (auto t : m_Tanks)
	{
		t->update(deltaTime, Vector4(input->getMouseX(), input->getMouseY(), 0, 0));
	}

	m_Origin->update();
}

void SkyeNetDotNetApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawSprite(m_MapTex, 0, 0, NULL, NULL, NULL, 100.0f, 0.0f, 0.0f);
	
	for (auto dot : m_MapNodes)
		m_2dRenderer->drawSprite(m_RedDot, (*dot)[0], (*dot)[1]);

	for (auto t : m_Tanks)
		t->draw(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}

void SkyeNetDotNetApp::createNavMesh()
{
	unsigned int yNodeCount = getWindowHeight() / m_NodeSpacing;
	unsigned int xNodeCount = getWindowWidth() / m_NodeSpacing;
	unsigned int x, y;

	for (size_t yNode = 0; yNode <= yNodeCount; ++yNode)
		for (size_t xNode = 0; xNode <= xNodeCount; ++xNode)
		{
			x = xNode * m_NodeSpacing;
			y = yNode * m_NodeSpacing;

			if (isEdge(m_MapTex, x, y) == true)
			{
				Vector2* newV2 = new Vector2(x, getWindowHeight() - y);
				m_MapNodes.push_back(newV2);
			}
		}	
}

unsigned int SkyeNetDotNetApp::getRGB(const aie::Texture * texture, unsigned int xCoord, unsigned int yCoord, unsigned int RGB) const
{
	unsigned int w = texture->getWidth();
	unsigned int h = texture->getHeight();

	assert(xCoord <= w && xCoord >= 0 && "Invalid image xCoord number");
	assert(yCoord <= h && yCoord >= 0 && "Invalid image yCoord number");
	assert(RGB >= 0 && RGB <= 2 && "Invalid RGB value");

	unsigned int y = yCoord, x = xCoord;

	if (y == 0)
		y++;
	if (x == 0)
		x++;

	const unsigned char* c = texture->getPixels();
	unsigned int RGBValue = c[(y - 1) * w * 3 + (x - 1) * 3 + RGB];

	return RGBValue;
}

bool SkyeNetDotNetApp::isEqualRGB(aie::Texture* texture, unsigned int x, unsigned int y)
{
	if (getRGB(texture, x, y, 0) == m_Red &&
		getRGB(texture, x, y, 1) == m_Green &&
		getRGB(texture, x, y, 2) == m_Blue)
		return true;
	else
		return false;
}

bool SkyeNetDotNetApp::isEdge(aie::Texture * texture, unsigned int x, unsigned int y)
{
	if (isEqualRGB(m_MapTex, x, y) == true)
	{
		if (x == 0 || x == getWindowWidth() || y == 0 || y == getWindowHeight() || 
			isEqualRGB(m_MapTex, x + 5, y) == false || isEqualRGB(m_MapTex, x - 5, y) == false ||
			isEqualRGB(m_MapTex, x, y + 5) == false || isEqualRGB(m_MapTex, x, y - 5) == false)
			return true;	
	}
	return false;
}
