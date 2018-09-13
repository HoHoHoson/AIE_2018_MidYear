#include "NotSoSupaCirclagonApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

#include "Algorithms.h"

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
	m_PlayerBounds = { m_PlayerPos.getGlobal()[2], m_PlayerTex->getWidth() };

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

void NotSoSupaCirclagonApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_SpawnTimer += deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT) || input->isKeyDown(aie::INPUT_KEY_A))
		m_PlayerOrigin.setLocal().rotateZ(HLib::toRadian(m_RotateSpeed) * deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT) || input->isKeyDown(aie::INPUT_KEY_D))
		m_PlayerOrigin.setLocal().rotateZ(HLib::toRadian(-m_RotateSpeed) * deltaTime);

	m_PlayerPos.setLocal().setIdentity();
	m_PlayerPos.setLocal().translate(NULL, (m_CircleTex->getWidth() + m_PlayerTex->getWidth()) / 2 + 20);

	for (auto r : m_Circlagons)
	{
		if (r->getBaseBounds().getRadius() < m_CircleTex->getWidth() / 2 && r->isActive() == true)
			r->isActive() = false;

		if (m_SpawnTimer > m_SpawnRate && r->isActive() == false)
		{
			r->loadCirclagon();
			m_Origin.updateTransform();

			r->isActive() = true;
			m_SpawnTimer = 0;
		}

		if (r->isActive() == true)
			r->updateCirclagon(deltaTime);
	}

	m_PlayerBounds.updateCircle(m_PlayerPos.getGlobal()[2]);

	m_Origin.updateTransform();

	for (auto r : m_Circlagons)
		if (r->isActive() == true && r->isOut() == false)
		{
			if (!isInside(m_PlayerBounds, r->getSafeBounds()))
			{
				if (!isInside(m_PlayerBounds, r->getBaseBounds()) && m_PlayerBounds.checkCollision(r->getExitBounds()))
				{
					r->isOut() = true;
					break;
				}

				if (!isInside(m_PlayerBounds, r->getExitBounds()))
					quit();
			}
		}

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

	for (auto r : m_Circlagons)
	{
		if (r->isActive() == true)
		{
			// NOTE the renderer depth has a MAX, it will not draw anything that is over the depth limit
			m_2dRenderer->drawSpriteTransformed3x3(m_CircleTex, r->getBaseGlobal(), NULL, NULL, (r->getBaseBounds().getRadius() + 1) / 10);
			m_2dRenderer->drawSpriteTransformed3x3(m_SafeTex, r->getSafeGlobal(), NULL, NULL, r->getBaseBounds().getRadius() / 10);
			m_2dRenderer->drawSpriteTransformed3x3(m_SafeTex, r->getExitGlobal(), NULL, NULL, r->getBaseBounds().getRadius() / 10);
		}
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
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
