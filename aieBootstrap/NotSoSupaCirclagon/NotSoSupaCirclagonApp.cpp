#include "NotSoSupaCirclagonApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

NotSoSupaCirclagonApp::NotSoSupaCirclagonApp() 
{
	srand((unsigned int)time(nullptr));
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
		Circlagon* newRing = new Circlagon(m_CircleTex->getWidth(), m_ScaleSpeed);
		m_Origin.addChild(newRing->loadThis());
		m_Circlagons.push_back(newRing);
	}

	std::fstream file;
	file.open("scores.dat", std::ios::binary | std::ios::in);
	if (file.is_open())
	{
		file.close();
		loadTable();
	}
	else
	{
		file.close();
		setDefaultTable();
	}


	m_GameTime = 0;
	m_IsSet = false;
	p = Random;
	state = Menu;

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

	switch (state)
	{

	case NotSoSupaCirclagonApp::Menu:
	{


		if (input->wasKeyPressed(aie::INPUT_KEY_P))
		{
			reloadGame();
			state = Game; 
			break;
		}

		if (input->wasKeyPressed(aie::INPUT_KEY_H))
		{
			state = HighScores; 
			break;
		}

		if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
			quit();


		break;
	}

	case NotSoSupaCirclagonApp::Game:
	{


		m_GameTime += deltaTime;
		m_SpawnTimer += deltaTime;
		m_RingAngle += m_RingSpeed * 0.9 * deltaTime;

		if (p == Random)
		{
			m_SpawnRate = 1.75 - m_RingSpeed / 1000;
			m_SpawnRate = HLib::clamp(m_SpawnRate, 1.5, 1.75);

			if (m_IsSet == false)
			{
				int cooldown = (rand() % (10 + 1) + 10) - m_GameTime / 10;
				cooldown = HLib::clamp(cooldown, 6, 20);

				m_Set = m_GameTime + cooldown;
				m_IsSet = true;
			}

			if (m_GameTime > m_Set && m_IsSet == true)
			{
				m_IsSet = false;
				m_SpawnTimer = -1.1;
				p = Stairs;
			}
		}

		if (p == Stairs)
		{
			m_SpawnRate = 0.5;

			if (m_IsSet == false)
			{
				if ((rand() % (2 + 1)) == 2)
					m_RingSpeed = -m_RingSpeed;

				m_Set = m_GameTime + 5 + (m_GameTime / 100);
				m_IsSet = true;
			}

			if (m_GameTime > m_Set && m_IsSet == true)
			{
				m_IsSet = false;
				m_SpawnTimer = 0;
				p = Random;
			}
		}

		m_RingSpeed = m_GameTime * 2.5;
		m_RingSpeed = HLib::clamp(m_RingSpeed, 0, 240);
		m_ScaleSpeed = m_RingSpeed / 8;
		m_ScaleSpeed = HLib::clamp(m_ScaleSpeed, 5, 20);

		if (input->isKeyDown(aie::INPUT_KEY_LEFT) || input->isKeyDown(aie::INPUT_KEY_A))
			m_PlayerOrigin.setLocal().rotateZ(HLib::toRadian(m_PlayerSpeed) * deltaTime);
		if (input->isKeyDown(aie::INPUT_KEY_RIGHT) || input->isKeyDown(aie::INPUT_KEY_D))
			m_PlayerOrigin.setLocal().rotateZ(HLib::toRadian(-m_PlayerSpeed) * deltaTime);
		if (input->isKeyDown(aie::INPUT_KEY_SPACE))
			m_PlayerSpeed = m_SetSpeed * 0.4;
		else
			m_PlayerSpeed = m_SetSpeed;

		m_PlayerPos.setLocal().setIdentity();
		m_PlayerPos.setLocal().translate(NULL, (m_CircleTex->getWidth() + m_PlayerTex->getWidth()) / 2 + 20);

		for (auto r : m_Circlagons)
		{
			if (r->getBaseBounds().getRadius() < m_CircleTex->getWidth() / 2 && r->isActive() == true)
				r->isActive() = false;

			if (m_SpawnTimer > m_SpawnRate && r->isActive() == false)
			{
				insertPattern(r);
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
						state = GameOver;
				}
			}


		break;
	}

	case NotSoSupaCirclagonApp::GameOver:
	{


		if (m_GameTime > scoreTable[9].time)
		{
			state = HighScoreInput;
			break;
		}

		if (input->wasKeyPressed(aie::INPUT_KEY_R))
		{
			reloadGame();
			state = Game; break;
		}

		if (input->wasKeyPressed(aie::INPUT_KEY_M))
			state = Menu; 


		break;
	}

	case NotSoSupaCirclagonApp::HighScores:
	{


		if (input->wasKeyPressed(aie::INPUT_KEY_ESCAPE))
			state = Menu;


		break;
	}

	case NotSoSupaCirclagonApp::HighScoreInput:
	{


		std::string input;
		do
		{
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin >> input;

		} while (input.length() > 12);

		scoreTable[9].name = input;
		scoreTable[9].time = m_GameTime;
		HLib::bubbleSort(scoreTable, 10);
		saveTable();
		m_GameTime = 0;

		state = GameOver;


		break;
	}

	default:
		assert(false && "Update switch statement error!");
	}
}

void NotSoSupaCirclagonApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!

	switch (state)
	{

	case NotSoSupaCirclagonApp::Menu:
	{


		m_2dRenderer->drawText(m_font, "(P)lay", getWindowWidth() / 2 - 80, getWindowHeight() / 2);
		m_2dRenderer->drawText(m_font, "(H)ighScores", getWindowWidth() / 2 - 80, getWindowHeight() / 2 - 40);
		m_2dRenderer->drawText(m_font, "(Esc)ape", getWindowWidth() / 2 - 80, getWindowHeight() / 2 - 80);


		break;
	}

	case NotSoSupaCirclagonApp::Game:
	{


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


		break;
	}

	case NotSoSupaCirclagonApp::GameOver:
	{

		
		m_2dRenderer->drawText(m_font, "GAMEOVER", getWindowWidth() / 2 - 80, getWindowHeight() / 2 + 200);
		m_2dRenderer->drawText(m_font, "(R)etry", getWindowWidth() / 2 - 80, getWindowHeight() / 2);
		m_2dRenderer->drawText(m_font, "(M)enu", getWindowWidth() / 2 - 80, getWindowHeight() / 2 - 40);


		break;
	}

	case NotSoSupaCirclagonApp::HighScores:
	{

		
		m_2dRenderer->drawText(m_font, "HIGHSCORE", getWindowWidth() / 2 - 80, getWindowHeight() / 2 + 200);

		for (size_t i = 0; i < 10; ++i)
		{
			std::string num = std::to_string(i + 1);
			std::string time = std::to_string(scoreTable[i].time);
			char sname[256];
			strcpy_s(sname, 255, scoreTable[i].name.data());

			m_2dRenderer->drawText(m_font, num.c_str(), getWindowWidth() / 2 - 200, getWindowHeight() / 2 + 120 - 40 * i);
			m_2dRenderer->drawText(m_font, scoreTable[i].name.c_str(), getWindowWidth() / 2 - 80, getWindowHeight() / 2 + 120 - 40 * i);
			m_2dRenderer->drawText(m_font, time.c_str(), getWindowWidth() / 2 + 180, getWindowHeight() / 2 + 120 - 40 * i);
		}

		m_2dRenderer->drawText(m_font, "(Esc)ape", 0, 10);


		break;
	}

	case NotSoSupaCirclagonApp::HighScoreInput:
	{


		m_2dRenderer->drawText(m_font, "NEW HIGHSCORE", getWindowWidth() / 2 - 80, getWindowHeight() / 2 + 200);
		m_2dRenderer->drawText(m_font, "Input a name into the Console", getWindowWidth() / 2 - 240, getWindowHeight() / 2 + 120);
		m_2dRenderer->drawText(m_font, "Can't be longer than 12 Characters!", getWindowWidth() / 2 - 240, getWindowHeight() / 2 + 80);


		break;
	}

	default:
		assert(false && "Draw switch statement error!");
	}

	// done drawing sprites
	m_2dRenderer->end();
}

void NotSoSupaCirclagonApp::setDefaultTable()
{
	for (size_t i = 0; i < 10; ++i)
	{
		scoreTable[i].name = "---";
		scoreTable[i].time = 0;
	}

	std::fstream file;
	file.open("scores.dat", std::ios::binary | std::ios::out);
	file.close();

	saveTable();
}

void NotSoSupaCirclagonApp::saveTable()
{
	std::fstream file;

	file.open("scores.dat", std::ios::binary | std::ios::in);
	if (file.good())
	{
		for (size_t i = 0; i < 10; ++i)
		{
			ScoreToData write(scoreTable[i]);
			file.write((char*)&write, sizeof(ScoreToData));
		}
	}

	file.close();
}

void NotSoSupaCirclagonApp::loadTable()
{
	std::fstream file;

	file.open("scores.dat", std::ios::binary | std::ios::out);
	if (file.good())
	{
		for (size_t i = 0; i < 10; ++i)
		{
			ScoreToData read;
			file.write((char*)&read, sizeof(ScoreToData));

			scoreTable[i].name = read.nameData;
			scoreTable[i].time = read.timeData;
		}
	}

	file.close();
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

void NotSoSupaCirclagonApp::insertPattern(Circlagon * c)
{
	switch (p)
	{
	case NotSoSupaCirclagonApp::Stairs:
		c->loadCirclagon(m_RingAngle, m_RingSpeed); return;

	case NotSoSupaCirclagonApp::Random:
	{
		if (m_RingSpeed < 0)
			m_RingSpeed = -m_RingSpeed;

		int randSpeed = rand() % (m_RingSpeed + m_RingSpeed) - m_RingSpeed;

		if (randSpeed <= 0 && randSpeed > -m_RingSpeed / 2)
			randSpeed -= m_RingSpeed / 2;
		else if (randSpeed > 0 && randSpeed < m_RingSpeed / 2)
			randSpeed += m_RingSpeed / 2;

		c->loadCirclagon(rand() % 360, randSpeed);
	}
	default:
		break;
	}
}

void NotSoSupaCirclagonApp::reloadGame()
{
	m_GameTime = 0;
	m_SpawnTimer = 0;
	m_PlayerOrigin.setLocal().setRotateZ(0);
	for (auto r : m_Circlagons)
		r->isActive() = false;
	m_IsSet = false;
	p = Random;
}
