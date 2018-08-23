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
	m_shipTexture = new aie::Texture("../bin/textures/ship.png");
	m_BulletTexture = new aie::Texture("../bin/textures/bullet.png");
	m_asteroidTexture = new aie::Texture("../bin/textures/rock_large.png");
	m_smlRockTexture = new aie::Texture("../bin/textures/rock_small.png");
	
	state = Game;
	
	m_makeEven = false;

	m_shipPosX = getWindowWidth() / 2;
	m_shipPosY = getWindowHeight() / 2;

	for (size_t i = 0; i < m_MaxBullets; ++i)
		m_InactiveBullets.push_back(new Bullet);

	boss.m_PosX = getWindowWidth() + m_asteroidTexture->getWidth();
	boss.m_PosY = getWindowHeight() + m_asteroidTexture->getHeight();
	bossState = Idle;

	for (size_t i = 0; i < m_MaxMinions; ++i)
		m_InactiveMinions.push_back(new LilRock);

	//m_asteroidCount = 10;
	//m_asteroidRotation = 0;
	//m_spaceRocks = new Asteroid[m_asteroidCount];

	//// randomly spawns an even number of asteroids on the bottom and left of the screen
	//for (size_t i = 0; i < m_asteroidCount; ++i)
	//{
	//	if (m_makeEven)
	//	{
	//		m_spaceRocks[i].m_asteroidPosY = getRandom(0 + m_asteroidTexture->getHeight() / 2, getWindowHeight() - m_asteroidTexture->getHeight() / 2);
	//		m_spaceRocks[i].m_asteroidPosX = 0 + m_asteroidTexture->getWidth() / 2;
	//		m_spaceRocks[i].spinninX = true;
	//	}
	//	else
	//	{
	//		m_spaceRocks[i].m_asteroidPosX = getRandom(0 + m_asteroidTexture->getWidth() / 2, getWindowWidth() - m_asteroidTexture->getWidth() / 2);
	//		m_spaceRocks[i].m_asteroidPosY = 0 + m_asteroidTexture->getHeight() / 2;
	//		m_spaceRocks[i].spinninX = false;
	//	}

	//	m_spaceRocks[i].m_asteroidSpeed = 300;
	//	m_spaceRocks[i].m_switchDirX = false;
	//	m_spaceRocks[i].m_coolDownX = false;
	//	m_spaceRocks[i].m_switchDirY = false;
	//	m_spaceRocks[i].m_coolDownY = false;

	//	m_makeEven = !m_makeEven;
	//}

	asteroidWidth = m_asteroidTexture->getWidth() / 2;
	asteroidHeight = m_asteroidTexture->getHeight() / 2;
	shipWidth = m_shipTexture->getWidth() / 2;
	shipHeight = m_shipTexture->getHeight() / 2;
	minionWidth = m_smlRockTexture->getWidth() / 2;
	minionHeight = m_smlRockTexture->getHeight() / 2;

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
		m_Timer += deltaTime;
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
			b->m_SpeedX = sinf(m_shipRotation) * b->m_SetSpeed;
			b->m_SpeedY = cosf(m_shipRotation) * b->m_SetSpeed;
			b->hurtsPlayer = false;
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

		//for (size_t i = 0; i < m_asteroidCount; ++i)
		//{
		//	if (m_spaceRocks[i].m_asteroidSpeed >= m_shipSpeed + 50)
		//		m_spaceRocks[i].m_asteroidSpeed = m_shipSpeed + 50;

		//	if (m_spaceRocks[i].spinninX)
		//	{
		//		if (!m_spaceRocks[i].m_switchDirX)
		//			m_spaceRocks[i].m_asteroidPosX += m_spaceRocks[i].m_asteroidSpeed * deltaTime;
		//		else
		//			m_spaceRocks[i].m_asteroidPosX -= m_spaceRocks[i].m_asteroidSpeed * deltaTime;

		//		if (!m_spaceRocks[i].m_switchDirY)
		//			m_spaceRocks[i].m_asteroidPosY += (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
		//		else
		//			m_spaceRocks[i].m_asteroidPosY -= (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
		//	}
		//	else
		//	{
		//		if (!m_spaceRocks[i].m_switchDirY)
		//			m_spaceRocks[i].m_asteroidPosY += m_spaceRocks[i].m_asteroidSpeed * deltaTime;
		//		else
		//			m_spaceRocks[i].m_asteroidPosY -= m_spaceRocks[i].m_asteroidSpeed * deltaTime;

		//		if (!m_spaceRocks[i].m_switchDirX)
		//			m_spaceRocks[i].m_asteroidPosX += (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
		//		else
		//			m_spaceRocks[i].m_asteroidPosX -= (m_spaceRocks[i].m_asteroidSpeed * deltaTime) / 2;
		//	}

		//	if (m_spaceRocks[i].m_coolDownX == true)
		//	{
		//		float timer = 0;
		//		while (timer < 0.5f)
		//			timer += deltaTime;
		//		timer = 0;
		//		m_spaceRocks[i].m_coolDownX = false;
		//	}
		//	else if (m_spaceRocks[i].m_asteroidPosX < 0 + m_asteroidTexture->getWidth() / 2 ||
		//		m_spaceRocks[i].m_asteroidPosX > getWindowWidth() - m_asteroidTexture->getWidth() / 2 &&
		//		m_spaceRocks[i].m_coolDownX == false)
		//	{
		//		m_spaceRocks[i].m_coolDownX = true;
		//		m_spaceRocks[i].m_switchDirX = !m_spaceRocks[i].m_switchDirX;
		//		m_spaceRocks[i].m_asteroidSpeed *= 1.0f + getRandom(0, 3) / 10.0f;
		//	}

		//	if (m_spaceRocks[i].m_coolDownY == true)
		//	{
		//		float timer = 0;
		//		while (timer < 0.5f)
		//			timer += deltaTime;
		//		timer = 0;
		//		m_spaceRocks[i].m_coolDownY = false;
		//	}
		//	else if (m_spaceRocks[i].m_asteroidPosY < 0 + m_asteroidTexture->getHeight() / 2 ||
		//		m_spaceRocks[i].m_asteroidPosY > getWindowHeight() - m_asteroidTexture->getHeight() / 2)
		//	{
		//		m_spaceRocks[i].m_coolDownY = true;
		//		m_spaceRocks[i].m_switchDirY = !m_spaceRocks[i].m_switchDirY;
		//		m_spaceRocks[i].m_asteroidSpeed *= 1.0f + getRandom(0, 2) / 1000.0f;
		//	}

		//	m_asteroidRotation++;

		//	// exit if the ship collides with the asteroids
		//	//if (checkCollision(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, 
		//	//	m_shipTexture, m_shipPosX, m_shipPosY))
		//	//	quit();
		//}

		switch (bossState)
		{
		case SpinnySpaceRocksApp::Idle:
		{

			setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, getWindowWidth() / 2, getWindowHeight() / 2, deltaTime);

			/*if (m_Timer > 1 && !m_InactiveMinions.empty() && boss.m_SpeedX == 0 && boss.m_SpeedY == 0)
			{
				m_Timer = 0.0f;
				LilRock* r = m_InactiveMinions.back();
				r->X = boss.m_PosX;
				r->Y = boss.m_PosY;
				setAnglesTo(r->speedX, r->speedY, r->setSpeed, r->X, r->Y, m_shipPosX, m_shipPosY, deltaTime);
				m_InactiveMinions.pop_back();
				m_ActiveMinions.push_front(r);
			}*/
			/*if (!m_InactiveMinions.empty() && m_Timer > 1)
			{
				m_Timer = 0;
				double increment = getRadians(360) / 10;
				double angle = 0;
				for (size_t i = 0; i < 10; ++i)
				{
					LilRock* r = m_InactiveMinions.back();
					r->X = boss.m_PosX;
					r->Y = boss.m_PosY;
					r->speedX = cos(angle) * r->setSpeed;
					r->speedY = sin(angle) * r->setSpeed;
					angle += increment;
					m_InactiveMinions.pop_back();
					m_ActiveMinions.push_front(r);
				}
			}*/
			if (!m_InactiveMinions.empty() && m_Timer > 0.1f)
			{
				m_Timer = 0;

				LilRock* r = m_InactiveMinions.back();
				r->X = boss.m_PosX;
				r->Y = boss.m_PosY;
				setAnglesTo(r->speedX, r->speedY, r->setSpeed, r->X, r->Y, m_shipPosX, m_shipPosY, deltaTime);
				m_InactiveMinions.pop_back();
				m_ActiveMinions.push_front(r);
			}

			break;
		}
		case SpinnySpaceRocksApp::Charge:
		{
			
			boss.m_SetSpeed = 1000;
			if (boss.rebound == true)
			{
				setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, m_shipPosX, m_shipPosY, deltaTime);
				boss.rebound = false;
			}
			if (boss.m_PosX < 0 + asteroidWidth || boss.m_PosX > getWindowWidth() - asteroidWidth)
			{
				boss.rebound = true;
				boss.m_SetSpeed = 1000 * (getWindowWidth() / getWindowHeight());
			}
			if (boss.m_PosY < 0 + asteroidHeight || boss.m_PosY > getWindowHeight() - asteroidHeight)
			{
				boss.rebound = true;
				boss.m_SetSpeed = 1000;
			}

			break;
		}
		default:
			break;
		}

		if (boss.invincible == true)
		{
			boss.m_RotationSpeed = 100;
		}

		boss.m_PosX += boss.m_SpeedX * deltaTime;
		boss.m_PosY += boss.m_SpeedY * deltaTime;
		boss.m_Rotation += boss.m_RotationSpeed * deltaTime;

		if (!m_ActiveMinions.empty())
		{
			auto it = m_ActiveMinions.begin();
			do
			{
				(*it)->X += (*it)->speedX * deltaTime;
				(*it)->Y += (*it)->speedY * deltaTime;

				if ((*it)->X < 0 - minionWidth || (*it)->X > getWindowWidth() + minionWidth ||
					(*it)->Y < 0 - minionHeight || (*it)->Y > getWindowHeight() + minionHeight ||
					(*it)->speedX ==0 & (*it)->speedY == 0)
				{
					m_InactiveMinions.push_back(*it);
					it = m_ActiveMinions.erase(it);
				}
				else
					++it;

			} while (it != m_ActiveMinions.end());
		}

		if (!m_ActiveBullets.empty())
		{
			auto it = m_ActiveBullets.begin();
			do
			{
				// to dereference a pointer inside an iterator, you need to dereference the iterator first, then the pointer.
				// hence why the iterator "it" is dereferenced inside some brackets first then dereferenced again to access the value of the pointer.
				(*it)->m_PosX -= (*it)->m_SpeedX * deltaTime;
				(*it)->m_PosY += (*it)->m_SpeedY * deltaTime;

				if (checkCollision(m_BulletTexture, (*it)->m_PosX, (*it)->m_PosY, m_asteroidTexture, boss.m_PosX, boss.m_PosY))
				{
					if (boss.invincible == true)
					{
						(*it)->m_SpeedX = -(*it)->m_SpeedX;
						(*it)->m_SpeedY = -(*it)->m_SpeedY;
						(*it)->hurtsPlayer = true;
						++it;
					}
					else
					{
						boss.m_Health--;
						m_InactiveBullets.push_front(*it);
						it = m_ActiveBullets.erase(it);
					}
				}
				else if ((*it)->m_PosX > getWindowWidth() || (*it)->m_PosX < 0 || (*it)->m_PosY > getWindowHeight() || (*it)->m_PosY < 0)
				{
					m_InactiveBullets.push_front(*it);
					it = m_ActiveBullets.erase(it);
				}
				else if ((*it)->hurtsPlayer == true)
				{
					if (checkCollision(m_BulletTexture, (*it)->m_PosX, (*it)->m_PosY, m_shipTexture, m_shipPosX, m_shipPosY))
					{
						quit();
					}
					else
						++it;
				}
				else
					++it;
				
			} while (it != m_ActiveBullets.end());
		}

		if (!m_ActiveMinions.empty())
		{
			auto minIt = m_ActiveMinions.begin();
			bool removed = false;
			do
			{
				if (!m_ActiveBullets.empty())
				{
					auto it = m_ActiveBullets.begin();
					do
					{
						if (checkCollision(m_BulletTexture, (*it)->m_PosX, (*it)->m_PosY, m_smlRockTexture, (*minIt)->X, (*minIt)->Y))
						{
							m_InactiveBullets.push_front(*it);
							m_ActiveBullets.erase(it);
							m_InactiveMinions.push_back(*minIt);
							minIt = m_ActiveMinions.erase(minIt);
							removed = true;
							break;
						}
						else
							++it;

					} while (it != m_ActiveBullets.end());
				}
				if (removed == false)
					++minIt;
				else
					removed = false;

			} while (minIt != m_ActiveMinions.end());
		}

		break;
	}

	default:
		assert(false && "The Update switch statement broke");
	}

	//setShowCursor(false);

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
		std::string h = std::to_string(boss.m_Health);

		m_2dRenderer->drawSprite(m_shipTexture, m_shipPosX, m_shipPosY, NULL, NULL, m_shipRotation, 0, 0.5f, 0.5f);

		m_2dRenderer->drawSprite(m_asteroidTexture, boss.m_PosX, boss.m_PosY, NULL, NULL, boss.m_Rotation, 0);

		for (auto rock : m_ActiveMinions)
			m_2dRenderer->drawSprite(m_smlRockTexture, rock->X, rock->Y);

		/*for (size_t i = 0; i < m_asteroidCount; ++i)
			m_2dRenderer->drawSprite(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, NULL, NULL, m_asteroidRotation, 0, 0.5f, 0.5f);*/

		for (auto bullet : m_ActiveBullets)
			m_2dRenderer->drawSprite(m_BulletTexture, bullet->m_PosX, bullet->m_PosY, NULL, NULL, NULL, 1);

		// output some text, uses the last used colour
		m_2dRenderer->drawText(m_font, h.c_str(), 100, 100, 0.1f);
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

void SpinnySpaceRocksApp::setAnglesTo(float& speedX, float& speedY, float setSpeed, float currentX, float currentY, float toX, float toY, float deltaT)
{
	float dy = toY - currentY;
	float dx = toX - currentX;
	float angle = atan2(dy, dx);

	speedX = cosf(angle) * setSpeed;
	speedY = sinf(angle) * setSpeed;

	if (currentX > toX - speedX * deltaT && currentX < toX + speedX * deltaT) 
		speedX = 0;
	if (currentY > toY - speedY * deltaT && currentY < toY + speedY * deltaT)
		speedY = 0;
}

