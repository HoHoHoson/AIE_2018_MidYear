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
	m_HoleTex = new aie::Texture("../bin/textures/ballBlack.png");
	m_RedNest = new aie::Texture("../bin/textures/ballRed.png");
	m_BlueNest = new aie::Texture("../bin/textures/ballBlue.png");

	m_TankBarrel = new aie::Texture("../bin/textures/barrelBeige.png");
	m_BlueTankTex = new aie::Texture("../bin/textures/tankBlue.png");

	Ant* a = new Ant(Ant::Red, m_RedAntTex);
	a->setPosition(Vector2(100, 100));
	a->setVelocity(Vector2(25, 25));
	m_Ants.push_back(a);

	a = new Ant(Ant::Blue, m_BlueAntTex);
	a->setPosition(Vector2(getWindowWidth() - 100, getWindowHeight() - 100));
	a->setVelocity(Vector2(-25, -25));
	m_Ants.push_back(a);

	for (size_t i = 0; i < 20; ++i)
	{
		Food* f = new Food(m_FoodTex);
		m_Food.push_back(f);
	}
	
	base = new AIBase(m_BlueAntTex);
	base->setPosition(Vector4(getWindowWidth() / 2, getWindowHeight() / 2, 0, 0));
	m_Origin = new SceneObject;
	m_Origin->addChild(base->getSceneObj());

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
	m_Timer += deltaTime;

	if (m_Timer > 3)
	{
		m_Timer = 0;
		for (auto* f : m_Food)
		{
			if (f->checkStatus() == false)
			{
				f->setup(Vector2(rand() % getWindowWidth(), rand() % getWindowHeight()));
				break;
			}
		}
	}
		/*for (auto a : m_Ants)
		a->update(deltaTime, a->getPosition());*/
	auto antIt = m_Ants.begin();
	while (antIt != m_Ants.end())
	{
		Food* closestYum = nullptr;
		auto a = (*antIt);

		//if (a->getState() != a->Home)
		//	for (auto* f : m_Food)
		//	{
		//		if (f->checkStatus() == true)
		//		{
		//			if (f->checkCollision(deltaTime, a->getPosition()) == true)
		//			{
		//				aie::Texture* temp;
		//				if (a->getTeam() == a->Blue)
		//					temp = m_BlueAntTex;
		//				else
		//					temp = m_RedAntTex;
		//				m_Ants.push_back(new Ant(a->getTeam(), temp));
		//				m_Add = true;
		//				a->setState(a->Home);
		//				break;
		//			}

		//			if (closestYum == nullptr)
		//				closestYum = f;
		//			if (MagPow2_2D(f->getPosition(), a->getPosition()) < MagPow2_2D(closestYum->getPosition(), a->getPosition()))
		//				closestYum = f;
		//		}
		//	}
		
		if (a->getState() != a->Home)
			if (closestYum != nullptr)
			{
				a->setState(a->Seek);
				a->update(deltaTime, closestYum->getPosition());
			}
			else
			{
				a->setState(a->Wander);
				a->update(deltaTime, a->getPosition());
			}
		else
			a->update(deltaTime, a->getPosition());

		if (m_Add == true)
		{
			m_Add = false;
			break;
		}
		antIt++;
	};

	base->m_SteeringForce = { 0,0,0,0 };
	base->m_SteeringForce += base->wanderForce(deltaTime);
	base->update(deltaTime);
	m_Origin->update();
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

	unsigned int nestScale = m_HoleTex->getWidth() * 2;

	m_2dRenderer->drawSprite(m_HoleTex, 100, 100, NULL, NULL, NULL, 0.9);
	m_2dRenderer->drawSprite(m_RedNest, 100, 100, nestScale, nestScale, NULL, 1);

	m_2dRenderer->drawSprite(m_HoleTex, 1180, 620, NULL, NULL, NULL, 0.9);
	m_2dRenderer->drawSprite(m_BlueNest, 1180, 620, nestScale, nestScale, NULL, 1);

	base->draw(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}