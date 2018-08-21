#include "SpinnySpaceRocksApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


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
	
	state = Game;
	
	m_makeEven = false;

	m_shipTexture = new aie::Texture("../bin/textures/ship.png");
	m_shipPosX = getWindowWidth() / 2;
	m_shipPosY = getWindowHeight() / 2;
	m_shipSpeed = 600;
	m_shipRotation = 0;

	m_BulletTexture = new aie::Texture("../bin/textures/bullet.png");
	for (size_t i = 0; i < 10; ++i)
		m_InactiveBullets.push_back(new Bullet);

	AngryRock boss;

	m_asteroidTexture = new aie::Texture("../bin/textures/rock_large.png");
	m_asteroidCount = 10;
	m_asteroidRotation = 0;
	m_spaceRocks = new Asteroid[m_asteroidCount];

	// randomly spawns an even number of asteroids on the bottom and left of the screen
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

void SpinnySpaceRocksApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_Select = m_ChoiceValue % 3;

	switch (state)
	{
	case SpinnySpaceRocksApp::Menu:
	{
		if (input->wasKeyPressed(aie::INPUT_KEY_UP))
			m_ChoiceValue--;
		if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
			m_ChoiceValue++;

		switch (m_Select)
		{
		case 0:
		{
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
				state = Game;
			break;
		}
		case 1:
		{
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
			break;
		}
		case 2:
		{
			if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
				quit();
			break;
		}
		default:
			assert(false && "The Menu switch statement broke");
		}
		break;
	}

	case SpinnySpaceRocksApp::Game:
	{
		m_shipRotation = atan2(input->getMouseY() - m_shipPosY, input->getMouseX() - m_shipPosX) + 3.15 * 1.5;

		if (input->isKeyDown(aie::INPUT_KEY_W))
		{
			if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_D))
				m_shipPosY += (cosf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosY += m_shipSpeed * deltaTime;
		}
		if (input->isKeyDown(aie::INPUT_KEY_S))
		{
			if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_D))
				m_shipPosY -= (cosf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosY -= m_shipSpeed * deltaTime;
		}
		if (input->isKeyDown(aie::INPUT_KEY_A))
		{
			if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_S))
				m_shipPosX -= (sinf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosX -= m_shipSpeed * deltaTime;
		}
		if (input->isKeyDown(aie::INPUT_KEY_D))
		{
			if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_S))
				m_shipPosX += (sinf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosX += m_shipSpeed * deltaTime;
		}
		if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) && !m_InactiveBullets.empty())
		{
			Bullet* b = m_InactiveBullets.back();
			b->m_PosX = m_shipPosX;
			b->m_PosY = m_shipPosY;
			b->m_AngX = sinf(m_shipRotation) * b->m_Speed;
			b->m_AngY = cosf(m_shipRotation) * b->m_Speed;
			m_InactiveBullets.pop_back();
			m_ActiveBullets.push_front(b);
		}

		// code for clamping the ship to stay within the screen since I can't find the Clamp function
		if (m_shipPosX > getWindowWidth() - shipWidth)
			m_shipPosX = getWindowWidth() - shipWidth;
		if (m_shipPosX < 0 + shipWidth)
			m_shipPosX = 0 + shipWidth;
		if (m_shipPosY > getWindowHeight() - shipHeight)
			m_shipPosY = getWindowHeight() - shipHeight;
		if (m_shipPosY < 0 + shipHeight)
			m_shipPosY = 0 + shipHeight;

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
					m_spaceRocks[i].m_asteroidSpeed *= 1.0f + getRandom(0, 3) / 10.0f;
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
					m_spaceRocks[i].m_asteroidSpeed *= 1.0f + getRandom(0, 2) / 1000.0f;							 
				 }

			m_asteroidRotation++;

			if (!m_ActiveBullets.empty())
			{
				auto it = m_ActiveBullets.begin();
				do
				{
					// to dereference an iterator to a pointer, you need to have the iterator with the dereference pointer inside some brackets
					(*it)->m_PosX -= (*it)->m_AngX * deltaTime;
					(*it)->m_PosY += (*it)->m_AngY * deltaTime;

					if ((*it)->m_PosX > getWindowWidth() || (*it)->m_PosX < 0 ||
						(*it)->m_PosY > getWindowHeight() || (*it)->m_PosY < 0)
					{
						m_InactiveBullets.push_front(*it);
						it = m_ActiveBullets.erase(it);
					}
					else
						++it;

				} while (it != m_ActiveBullets.end());
			}

			// exit if the ship collides with the asteroids
			//if (checkCollision(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, 
			//	m_shipTexture, m_shipPosX, m_shipPosY))
			//	quit();
		}

		//setShowCursor(false);
		break;
	}

	default:
		assert(false && "The Update switch statement broke");
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void SpinnySpaceRocksApp::draw() 
{
	std::string counter = std::to_string(m_Select);

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	switch (state)
	{
	case SpinnySpaceRocksApp::Menu:
	{
		m_2dRenderer->drawText(m_font, "PLAY", getWindowWidth() / 2, getWindowHeight() / 2, 0.1f);
		m_2dRenderer->drawText(m_font, " ", getWindowWidth() / 2, getWindowHeight() / 2 - 40, 0.1f);
		m_2dRenderer->drawText(m_font, "EXIT", getWindowWidth() / 2, getWindowHeight() / 2 - 80, 0.1f);

		switch (m_Select)
		{
		case 0:
		{
			m_2dRenderer->drawText(m_font, "> ", getWindowWidth() / 2 - 20, getWindowHeight() / 2, 0.1f);
			break;
		}
		case 1:
		{
			m_2dRenderer->drawText(m_font, "> ", getWindowWidth() / 2 - 20, getWindowHeight() / 2 - 40, 0.1f);
			break;
		}
		case 2:
		{
			m_2dRenderer->drawText(m_font, "> ", getWindowWidth() / 2 - 20, getWindowHeight() / 2 - 80, 0.1f);
			break;
		}
		default:
			assert(false && "The draw menu switch statement broke");
		}
		break;
	}

	case SpinnySpaceRocksApp::Game:
	{
		m_2dRenderer->drawSprite(m_shipTexture, m_shipPosX, m_shipPosY, NULL, NULL, m_shipRotation, 0, 0.5f, 0.5f);

		for (size_t i = 0; i < m_asteroidCount; ++i)
			m_2dRenderer->drawSprite(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, NULL, NULL, m_asteroidRotation, 0, 0.5f, 0.5f);

		for (auto bullet : m_ActiveBullets)
			m_2dRenderer->drawSprite(m_BulletTexture, bullet->m_PosX, bullet->m_PosY, NULL, NULL, NULL, 1);

		// output some text, uses the last used colour
		m_2dRenderer->drawText(m_font, "TRY NOT TO DIE :D", 0, 10, 0.1f);

		break;
	}

	default:
		assert(false && "The main draw switch statement is broken");
	}

	// done drawing sprites
	m_2dRenderer->end();
}

// AABB Rectangular Collision between the Ship and the Asteroids
bool SpinnySpaceRocksApp::checkCollision(aie::Texture* s_Obj, float s_X, float s_Y, aie::Texture* l_Obj, float l_X, float l_Y)
{
	if (s_X - s_Obj->getWidth() / 2 >= l_X - l_Obj->getWidth() / 2 &&
		s_X - s_Obj->getWidth() / 2 <= l_X + l_Obj->getWidth() / 2 ||
		s_X + s_Obj->getWidth() / 2 >= l_X - l_Obj->getWidth() / 2 &&
		s_X + s_Obj->getWidth() / 2 <= l_X + l_Obj->getWidth() / 2)
		if (s_Y - s_Obj->getHeight() / 2 >= l_Y - l_Obj->getHeight() / 2 &&
			s_Y - s_Obj->getHeight() / 2 <= l_Y + l_Obj->getHeight() / 2 ||
			s_Y + s_Obj->getHeight() / 2 >= l_Y - l_Obj->getHeight() / 2 &&
			s_Y + s_Obj->getHeight() / 2 <= l_Y + l_Obj->getHeight() / 2)
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

double SpinnySpaceRocksApp::getRadians(double degrees)
{
	return (degrees * M_PI / 180);
}

