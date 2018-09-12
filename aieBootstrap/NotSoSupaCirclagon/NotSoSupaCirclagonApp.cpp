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
	m_PLayerBounds = { m_PlayerPos.getGlobal()[2], m_PlayerTex->getWidth() };

	for (size_t i = 0; i < m_RingCount; ++i)
	{
		Circlagon* newRing = new Circlagon(m_CircleTex->getWidth());
		m_Origin.addChild(newRing->loadThis());
		m_Circlagons.push_back(newRing);
	}

	return true;
}

void NotSoSupaCirclagonApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void NotSoSupaCirclagonApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_LEFT) || input->isKeyDown(aie::INPUT_KEY_A))
		m_PlayerOrigin.setLocal().rotateZ(toRadian(m_RotateSpeed) * deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT) || input->isKeyDown(aie::INPUT_KEY_D))
		m_PlayerOrigin.setLocal().rotateZ(toRadian(-m_RotateSpeed) * deltaTime);

	m_PLayerBounds.updateCircle(m_PlayerPos.getGlobal()[2]);

	for (size_t i = 0; i < m_RingCount; ++i)
	{
		Circlagon* cIt = m_Circlagons.at(i);
		if (cIt->isActive() == false)
			cIt->loadCirclagon();
		if (cIt->isActive() == true)
		{
			cIt->updateCirclagon(deltaTime);

			if (!isInside(m_PLayerBounds, cIt->getSafeBounds()))
				quit();
		}
	}

	m_PlayerPos.setLocal().setIdentity();
	m_PlayerPos.setLocal().translate(NULL, (m_CircleTex->getWidth() + m_PlayerTex->getWidth()) / 2 + 10);

	m_Origin.updateObj(deltaTime);

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

	m_2dRenderer->drawSpriteTransformed3x3(m_CircleTex, m_PlayerOrigin.getGlobal(), NULL, NULL, 0);
	m_2dRenderer->drawSpriteTransformed3x3(m_PlayerTex, m_PlayerPos.getGlobal(), NULL, NULL, 0);

	for (auto ring : m_Circlagons)
		if (ring->isActive() == true)
		{
			m_2dRenderer->drawSpriteTransformed3x3(m_CircleTex, ring->getBaseGlobal(), NULL, NULL, 1);
			m_2dRenderer->drawSpriteTransformed3x3(m_SafeTex, ring->getSafeGlobal(), NULL, NULL, 0.5);
			m_2dRenderer->drawSpriteTransformed3x3(m_SafeTex, ring->getExitGlobal(), NULL, NULL, 0.5);
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

bool NotSoSupaCirclagonApp::isInside(const Circle& obj, const Circle& bounds) const
{
	float distanceSqr = MagPow2_2D(bounds.getOrigin(), obj.getOrigin());
	float safeZoneSqr = pow(bounds.getRadius() - obj.getRadius(), 2);

	if (distanceSqr > safeZoneSqr)
		return false;
	else
		return true;
}
