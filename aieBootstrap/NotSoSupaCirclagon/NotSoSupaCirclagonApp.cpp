#include "NotSoSupaCirclagonApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#define _USE_MATH_DEFINES
#include <math.h>


NotSoSupaCirclagonApp::NotSoSupaCirclagonApp() 
{
}

NotSoSupaCirclagonApp::~NotSoSupaCirclagonApp()
{
}

bool NotSoSupaCirclagonApp::startup() 
{
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_PlayerTex = new aie::Texture("../bin/textures/car.png");
	m_CircleTex = new aie::Texture("../bin/textures/ballWhite.png");
	m_SafeTex = new aie::Texture("../bin/textures/ballBlack.png");

	m_WidthMid = getWindowWidth() / 2;
	m_HeightMid = getWindowHeight() / 2;

	m_Origin.setLocal()[2] = { m_WidthMid, m_HeightMid, 1 };
	m_Origin.addChild(&m_PlayerOrigin);
	m_PlayerOrigin.addChild(&m_PlayerPos);
	Circlagon* test = new Circlagon;
	test->loadCirclagon();
	m_Origin.addChild(test->loadThis());
	m_Circlagons.push_back(test);

	return true;
}

void NotSoSupaCirclagonApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void NotSoSupaCirclagonApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	degrees += 50 * deltaTime;
	m_Origin.updateObj(deltaTime);
	m_PlayerPos.getLocal().rotateZ(toRadian(90) * deltaTime);
	//m_PlayerPos.getLocal().setRotateZ(toRadian(270));
	m_PlayerPos.getLocal()[2][0] = degrees;


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void NotSoSupaCirclagonApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	//m_2dRenderer->drawSpriteTransformed3x3(m_CircleTex, m_PlayerOrigin.getGlobal(), NULL, NULL, 0);
	//m_2dRenderer->drawSpriteTransformed3x3(m_PlayerTex, m_PlayerPos.getGlobal(), NULL, NULL, 0);

	for (auto ring : m_Circlagons)
		if (ring->isActive() == true)
		{
			m_2dRenderer->drawSpriteTransformed3x3(m_CircleTex, ring->getBaseGlobal(), NULL, NULL, 1);
			m_2dRenderer->drawSpriteTransformed3x3(m_SafeTex, ring->getSafeGlobal(), NULL, NULL, 0.5);
		}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

float NotSoSupaCirclagonApp::toRadian(float degrees) const
{
	return (degrees * (M_PI / 180));
}

bool NotSoSupaCirclagonApp::isInside(const aie::Texture* s_Obj, const Matrix3& s_M, const aie::Texture* l_Obj, const Matrix3& l_M, float l_Multi) const
{
	float distance = (s_M[2] - l_M[2]).magnitude();
	float safeZone = (l_Obj->getWidth() / 2) * l_Multi - s_Obj->getWidth() / 2;

	if (distance > safeZone)
		return true;
	else
		return false;
}
