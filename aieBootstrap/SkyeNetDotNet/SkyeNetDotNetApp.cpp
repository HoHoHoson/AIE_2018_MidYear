#include "SkyeNetDotNetApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Ant.h"
#include "Food.h"
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

	m_BlueAntTex = new aie::Texture("../bin/textures/blue_ant.png");
	m_RedAntTex = new aie::Texture("../bin/textures/red_ant.png");
	m_FoodTex = new aie::Texture("../bin/textures/ball.png");

	Ant* a = new Ant(Ant::Red, m_RedAntTex);
	a->setVelocity(Vector2(25, 25));
	m_Ants.push_back(a);

	a = new Ant(Ant::Blue, m_BlueAntTex);
	a->setPosition(Vector2(getWindowWidth(), getWindowHeight()));
	a->setVelocity(Vector2(-25, -25));
	m_Ants.push_back(a);

	for (size_t i = 0; i < 20; ++i)
	{
		Food* f = new Food(m_FoodTex);
		m_Food.push_back(f);
	}
	
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

	m_Timer += deltaTime;

	if (m_Timer > 3)
	{
		m_Timer = 0;
		for (auto* f : m_Food)
		{
			if (f->checkStatus() == false)
			{
				f->setup(Vector2(rand() % getWindowHeight(), rand() % getWindowHeight()));
				break;
			}
		}
	}

	for (auto* a : m_Ants)
	{
		a->update(deltaTime);
		for (auto* f : m_Food)
			f->update(deltaTime, a->getPosition());
	}
	
}

void SkyeNetDotNetApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	for (auto* f : m_Food)
		if (f->checkStatus() == true)
			f->render(m_2dRenderer);

	for (auto* a : m_Ants)
		a->render(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}