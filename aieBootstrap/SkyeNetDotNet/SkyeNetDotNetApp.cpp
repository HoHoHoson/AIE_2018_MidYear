#include "SkyeNetDotNetApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
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

	const unsigned char* c = m_SkyeNetTankTex->getPixels();
	c[0];
	c[1];
	c[2];
	c[3];

	m_Origin->update();
}

void SkyeNetDotNetApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	for (auto t : m_Tanks)
		t->draw(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}