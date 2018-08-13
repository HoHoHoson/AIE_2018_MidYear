#include "SpinnySpaceRocksApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <time.h>
#include <random>


SpinnySpaceRocksApp::SpinnySpaceRocksApp() 
{
	srand((unsigned int)time(nullptr));
}

SpinnySpaceRocksApp::~SpinnySpaceRocksApp() 
{

}

bool SpinnySpaceRocksApp::startup() 
{
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	
	m_makeEven = false;

	m_shipTexture = new aie::Texture("../bin/textures/ship.png");
	m_shipPosX = getWindowWidth() / 2;
	m_shipPosY = getWindowHeight() / 2;
	m_shipSpeed = 700;
	m_shipRotation = 0;

	m_asteroidTexture = new aie::Texture("../bin/textures/rock_large.png");
	m_asteroidCount = 10;
	m_asteroidRotation = 0;
	m_spaceRocks = new Asteroid[m_asteroidCount];
	for (size_t i = 0; i < m_asteroidCount; ++i)
	{
		if (m_makeEven)
		{
			m_spaceRocks[i].m_asteroidPosY = getRandom(0 + m_asteroidTexture->getHeight() / 2, getWindowHeight() - m_asteroidTexture->getHeight() / 2);
			m_spaceRocks[i].m_asteroidPosX = 0 + m_asteroidTexture->getWidth() / 2;
			m_spaceRocks[i].spinninX = true;
		}
		else
		{
			m_spaceRocks[i].m_asteroidPosX = getRandom(0 + m_asteroidTexture->getWidth() / 2, getWindowWidth() - m_asteroidTexture->getWidth() / 2);
			m_spaceRocks[i].m_asteroidPosY = 0 + m_asteroidTexture->getHeight() / 2;
			m_spaceRocks[i].spinninX = false;
		}

		m_spaceRocks[i].m_asteroidSpeed = 300;
		m_spaceRocks[i].m_switchDirX = false;
		m_spaceRocks[i].m_coolDownX = false;
		m_spaceRocks[i].m_switchDirY = false;
		m_spaceRocks[i].m_coolDownY = false;

		m_makeEven = !m_makeEven;
	}

	asteroidWidth = m_asteroidTexture->getWidth() / 2;
	asteroidHeight = m_asteroidTexture->getHeight() / 2;
	shipWidth = m_shipTexture->getWidth() / 2;
	shipHeight = m_shipTexture->getHeight() / 2;

	return true;
}

void SpinnySpaceRocksApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void SpinnySpaceRocksApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_W) && m_shipPosY < getWindowHeight() - shipHeight)
	{
		m_shipPosY += m_shipSpeed * deltaTime;
		m_shipRotation = 0;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S) && m_shipPosY > 0 + shipHeight)
	{
		m_shipPosY -= m_shipSpeed * deltaTime;
		m_shipRotation = 3.15f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A) && m_shipPosX > 0 + shipWidth)
	{
		m_shipPosX -= m_shipSpeed * deltaTime;
		m_shipRotation = 1.575f;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D) && m_shipPosX < getWindowWidth() - shipWidth)
	{
		m_shipPosX += m_shipSpeed * deltaTime;
		m_shipRotation = 4.725f;
	}

	for (size_t i = 0; i < m_asteroidCount; ++i)
	{
		if (m_spaceRocks[i].m_asteroidSpeed >= m_shipSpeed + 50)
			m_spaceRocks[i].m_asteroidSpeed = m_shipSpeed + 50;

		if (m_spaceRocks[i].spinninX)
		{
			if (!m_spaceRocks[i].m_switchDirX)
				m_spaceRocks[i].m_asteroidPosX += m_spaceRocks[i].m_asteroidSpeed * deltaTime;
			else
				m_spaceRocks[i].m_asteroidPosX -= m_spaceRocks[i].m_asteroidSpeed * deltaTime;

			if (!m_spaceRocks[i].m_switchDirY)
				m_spaceRocks[i].m_asteroidPosY += (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
			else
				m_spaceRocks[i].m_asteroidPosY -= (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
		}
		else
		{
			if (!m_spaceRocks[i].m_switchDirY)
				m_spaceRocks[i].m_asteroidPosY += m_spaceRocks[i].m_asteroidSpeed * deltaTime;
			else
				m_spaceRocks[i].m_asteroidPosY -= m_spaceRocks[i].m_asteroidSpeed * deltaTime;

			if (!m_spaceRocks[i].m_switchDirX)
				m_spaceRocks[i].m_asteroidPosX += (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
			else
				m_spaceRocks[i].m_asteroidPosX -= (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
		}

		if (m_spaceRocks[i].m_coolDownX == true)
		{
			float timer = 0;
			while (timer < 0.5f)
				timer += deltaTime;
			timer = 0;
			m_spaceRocks[i].m_coolDownX = false;
		}
		else if (m_spaceRocks[i].m_asteroidPosX < 0 + m_asteroidTexture->getWidth() / 2 ||
			m_spaceRocks[i].m_asteroidPosX > getWindowWidth() - m_asteroidTexture->getWidth() / 2 &&
			m_spaceRocks[i].m_coolDownX == false)
		{
			m_spaceRocks[i].m_coolDownX = true;
			m_spaceRocks[i].m_switchDirX = !m_spaceRocks[i].m_switchDirX;
			m_spaceRocks[i].m_asteroidSpeed *= 1.0f + getRandom(0, 3) / 10.0f;;
		}

		if (m_spaceRocks[i].m_coolDownY == true)
		{
			float timer = 0;
			while (timer < 0.5f)
				timer += deltaTime;
			timer = 0;
			m_spaceRocks[i].m_coolDownY = false;
		}
		else if (m_spaceRocks[i].m_asteroidPosY < 0 + m_asteroidTexture->getHeight() / 2 ||
			m_spaceRocks[i].m_asteroidPosY > getWindowHeight() - m_asteroidTexture->getHeight() / 2)
		{
			m_spaceRocks[i].m_coolDownY = true;
			m_spaceRocks[i].m_switchDirY = !m_spaceRocks[i].m_switchDirY;
			m_spaceRocks[i].m_asteroidSpeed *= 1.0f + getRandom(0, 2) / 1000.0f;;
		}

		m_asteroidRotation++;
		if (checkCollision(m_spaceRocks[i]))
			quit();
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void SpinnySpaceRocksApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawSprite(m_shipTexture, m_shipPosX, m_shipPosY, NULL, NULL, m_shipRotation, 0, 0.5f, 0.5f);
	for (size_t i = 0; i < m_asteroidCount; ++i)
		m_2dRenderer->drawSprite(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, NULL, NULL, m_asteroidRotation, 0, 0.5f, 0.5f);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "TRY NOT TO DIE :D", 0, 10, 0.1f);

	// done drawing sprites
	m_2dRenderer->end();
}

bool SpinnySpaceRocksApp::checkCollision(Asteroid rock)
{
	if (rock.m_asteroidPosX - asteroidWidth >= m_shipPosX - shipWidth &&
		rock.m_asteroidPosX - asteroidWidth <= m_shipPosX + shipWidth ||
		rock.m_asteroidPosX + asteroidWidth >= m_shipPosX - shipWidth &&
		rock.m_asteroidPosX + asteroidWidth <= m_shipPosX + shipWidth)
		if (rock.m_asteroidPosY - asteroidHeight >= m_shipPosY - shipHeight &&
			rock.m_asteroidPosY - asteroidHeight <= m_shipPosY + shipHeight ||
			rock.m_asteroidPosY + asteroidHeight >= m_shipPosY - shipHeight &&
			rock.m_asteroidPosY + asteroidHeight <= m_shipPosY + shipHeight)
			return true;

	return false;
}

int SpinnySpaceRocksApp::getRandom(int min, int max)
{
	int temp = 0;
	if (min > max)
	{
		temp = min;
		min = max;
		max = temp;
	}
	temp = max - min;
	temp = rand() % (temp + 1) + min;
	return temp;
}
