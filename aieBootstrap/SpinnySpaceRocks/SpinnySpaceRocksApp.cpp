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
	m_HealthTexture = new aie::Texture("../bin/textures/barrelGreen.png");
	m_BossHealthTexture = new aie::Texture("../bin/textures/barrelRed.png");
	m_ShieldTexture = new aie::Texture("../bin/textures/ball.png");
	m_Crosshair = new aie::Texture("../bin/textures/crossHair.png");

	state = Menu;
	
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
	setShowCursor(false);

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
				state = Instructions;
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

		m_CrosshairX = input->getMouseX();
		m_CrosshairY = input->getMouseY();
		m_GameTimer += deltaTime;
		exTimer += deltaTime;
		boss.coolDown += deltaTime;
		m_FirerateTimer += deltaTime;
		firerate_LMG += deltaTime;
		m_shipRotation = atan2(input->getMouseY() - m_shipPosY, input->getMouseX() - m_shipPosX) + 3.15 * 1.5;

		if (input->isKeyDown(aie::INPUT_KEY_W) && m_YouDed == false)
		{
			if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_D))
				m_shipPosY += (cosf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosY += m_shipSpeed * deltaTime;
		}
		if (input->isKeyDown(aie::INPUT_KEY_S) && m_YouDed == false)
		{
			if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_D))
				m_shipPosY -= (cosf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosY -= m_shipSpeed * deltaTime;
		}
		if (input->isKeyDown(aie::INPUT_KEY_A) && m_YouDed == false)
		{
			if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_S))
				m_shipPosX -= (sinf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosX -= m_shipSpeed * deltaTime;
		}
		if (input->isKeyDown(aie::INPUT_KEY_D) && m_YouDed == false)
		{
			if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_S))
				m_shipPosX += (sinf(45) * m_shipSpeed) * deltaTime;
			else
				m_shipPosX += m_shipSpeed * deltaTime;
		}
		if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT) && !m_InactiveBullets.empty() && m_YouDed == false && firerate_LMG > 0.2f)
		{
			firerate_LMG = 0;
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

		if (m_BossAlive == false && m_GameTimer > 26)
			for (size_t i = 0; i < m_asteroidCount; ++i)
			{

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

				if (checkCollision(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, m_shipTexture, m_shipPosX, m_shipPosY) &&
					m_ShipInvulnerable == false)
				{
					m_ShipInvulnerable = true;
					m_ShipHealth--;
				}
			}

		switch (bossState)
		{
		case SpinnySpaceRocksApp::Idle:
		{

			if (boss.m_Health <= 0)
			{
				m_BossAlive = false;
				m_GameTimer = 0;
				m_FirerateTimer = 0;
				exTimer = 0;
				bossState = Dead;
			}

			setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, getWindowWidth() / 2, getWindowHeight() / 2, deltaTime);

			if (boss.m_SpeedX == 0 && boss.m_SpeedY == 0)
			{
				if (m_FirerateTimer > 0.5f)
				{
					if (!m_InactiveMinions.empty() && boss.m_Health >= 4 || boss.m_Health <= 2)
					{
						m_FirerateTimer = 0.0f;
						LilRock* r = m_InactiveMinions.back();
						r->X = boss.m_PosX;
						r->Y = boss.m_PosY;
						setAnglesTo(r->speedX, r->speedY, r->setSpeed, r->X, r->Y, m_shipPosX, m_shipPosY, deltaTime);
						m_InactiveMinions.pop_back();
						m_ActiveMinions.push_front(r);
					}
			
				}
				if (exTimer > 1.5f && boss.m_Health < 4)
				{
					exTimer = 0.0f;
					bossExplosion();
				}
			}

			if (boss.invincible == true && boss.m_SpeedX == 0 && boss.m_SpeedY == 0)
			{
				boss.coolDown = 0;
				m_FirerateTimer = 0;
				exTimer = 0;

				if (boss.m_Health == 4)
					bossState = RapidFire;
				else
					bossState = Charge;
			}

			break;
		}
		case SpinnySpaceRocksApp::Charge:
		{

			if (boss.m_Health <= 2 && m_FirerateTimer > 1.5f)
			{
				m_FirerateTimer = 0;
				bossExplosion();
			}

			if (boss.coolDown > 2 && boss.coolDown < 7)
			{
				boss.m_SetSpeed = 950;
				if (boss.rebound == true)
				{
					setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, m_shipPosX, m_shipPosY, deltaTime);
					boss.rebound = false;
				}
				if (boss.m_PosX < 0 + asteroidWidth || boss.m_PosX > getWindowWidth() - asteroidWidth)
				{
					boss.rebound = true;
					boss.m_SetSpeed = 950 * (getWindowWidth() / getWindowHeight());
				}
				if (boss.m_PosY < 0 + asteroidHeight || boss.m_PosY > getWindowHeight() - asteroidHeight)
				{
					boss.rebound = true;
					boss.m_SetSpeed = 950;
				}
			}
			if (boss.coolDown > 7)
			{
				boss.rebound = true;
				boss.m_SetSpeed = 650;

				if (boss.m_Health >= 3)
				{
					boss.invincible = false;
					m_FirerateTimer = 0;
					boss.coolDown = 0;
					bossState = Idle;
				}
				else
				{
					if (m_shipPosX > getWindowWidth() / 2)
						setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, getWindowWidth() * 0.25f, getWindowHeight() / 2, deltaTime);
					else
						setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, getWindowWidth() * 0.75f, getWindowHeight() / 2, deltaTime);

					if (boss.m_SpeedX == 0 && boss.m_SpeedY == 0)
					{
						m_FirerateTimer = 0;
						boss.coolDown = 0;
						exTimer = 0;
						bossState = RapidFire;
					}
				}
			}

			break;
		}
		case SpinnySpaceRocksApp::RapidFire:
		{

			if (boss.m_Health <= 1 && exTimer > 1.5f)
			{
				exTimer = 0;
				bossExplosion();
			}

			if (!m_InactiveMinions.empty() && m_FirerateTimer > 0.2f && boss.coolDown > 2 && boss.coolDown < 9)
			{
				m_FirerateTimer = 0;
				bool alt = false;

				for (size_t i = 0; i < 2; i++)
				{
					LilRock* r = m_InactiveMinions.back();
					r->X = boss.m_PosX;
					r->Y = boss.m_PosY;
					setAnglesTo(r->speedX, r->speedY, r->setSpeed, r->X, r->Y, m_shipPosX, m_shipPosY, deltaTime);

					if (alt == false)
					{
						r->speedX = +r->speedX;
						r->speedY = -r->speedY;
						alt = true;
					}
					else
						alt = false;

					m_InactiveMinions.pop_back();
					m_ActiveMinions.push_front(r);
				}
			}

			if (boss.coolDown > 12 && m_BossAlive != false)
				if (boss.m_Health <= 1 && lastStand == false)
				{
					static float temp = boss.m_PosX;
					if (temp > getWindowWidth() / 2)
						setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, getWindowWidth() * 0.25f, getWindowHeight() / 2, deltaTime);
					else
						setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY, getWindowWidth() * 0.75f, getWindowHeight() / 2, deltaTime);

					if (boss.m_SpeedX == 0 && boss.m_SpeedY == 0)
					{
						m_FirerateTimer = 0;
						boss.coolDown = 0;
						lastStand = true;
					}
				}
				else
				{
					m_FirerateTimer = 0;
					boss.coolDown = 0;
					boss.invincible = false;
					bossState = Idle;
				}

			break;
		}
		case SpinnySpaceRocksApp::Dead:
		{

			m_DeathTimer += deltaTime;

			if (m_BossAlive == true)
			{
				if (m_DeathTimer < 3)
				{
					boss.invincible = false;
					setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY,
						getWindowWidth() / 2, getWindowHeight() - m_asteroidTexture->getHeight() * 2, deltaTime);
				}
				else if (m_DeathTimer < 3.2f)
				{
					boss.invincible = true;
					setAnglesTo(boss.m_SpeedX, boss.m_SpeedY, boss.m_SetSpeed, boss.m_PosX, boss.m_PosY,
						getWindowWidth() / 2, 0 + m_asteroidTexture->getHeight() * 2, deltaTime);
				}
				else
					bossExplosion();
			}

			break;
		}
		default:
			break;
		}

		if (boss.invincible == true)
			boss.m_RotationSpeed = 70;
		else
			boss.m_RotationSpeed = 7;

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
				if (checkCollision(m_smlRockTexture, (*it)->X, (*it)->Y, m_shipTexture, m_shipPosX, m_shipPosY) && m_ShipInvulnerable == false)
				{
					m_ShipHealth--;
					m_ShipInvulnerable = true;
					m_InactiveMinions.push_back(*it);
					it = m_ActiveMinions.erase(it);
				}
				else if ((*it)->X < 0 - minionWidth || (*it)->X > getWindowWidth() + minionWidth ||
					(*it)->Y < 0 - minionHeight || (*it)->Y > getWindowHeight() + minionHeight ||
					(*it)->speedX == 0 & (*it)->speedY == 0)
				{
					m_InactiveMinions.push_back(*it);
					it = m_ActiveMinions.erase(it);
				}
				else
					++it;

			} while (it != m_ActiveMinions.end());
		}

		if (m_ShipInvulnerable == true)
		{
			m_iCoolDown += deltaTime;
			if (m_iCoolDown > 3)
			{
				m_iCoolDown = 0;
				m_ShipInvulnerable = false;
			}
		}

		if (checkCollision(m_asteroidTexture, boss.m_PosX, boss.m_PosY, m_shipTexture, m_shipPosX, m_shipPosY) && m_ShipInvulnerable == false)
		{
			m_ShipInvulnerable = true;
			m_ShipHealth--;
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
						boss.invincible = true;
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
					if (checkCollision(m_BulletTexture, (*it)->m_PosX, (*it)->m_PosY, m_shipTexture, m_shipPosX, m_shipPosY) && m_ShipInvulnerable == false)
					{
						m_ShipInvulnerable = true;
						m_ShipHealth--;
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

		if (m_ShipHealth <= 0)
		{
			iCantThinkSo += deltaTime;
			bossState = Dead;
			m_YouDed = true;
			if (iCantThinkSo > 10 || m_BossAlive == false && iCantThinkSo > 5)
				quit();
		}
		if (m_BossAlive == false)
		{
			boss.m_PosX = 6900;
			boss.m_PosY = 6900;
		}

		break;
	}
	case SpinnySpaceRocksApp::Instructions:
	{

		if (input->wasKeyPressed(aie::INPUT_KEY_BACKSPACE))
			state = Menu;

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
		m_2dRenderer->drawText(m_font, "INSTRUCTIONS", getWindowWidth() / 2, getWindowHeight() / 2 - 40, 0.1f);
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

		m_2dRenderer->drawSprite(m_Crosshair, m_CrosshairX, m_CrosshairY, NULL, NULL, NULL, 0);

		for (auto rock : m_ActiveMinions)
			m_2dRenderer->drawSprite(m_smlRockTexture, rock->X, rock->Y, NULL, NULL, NULL, 1);

		for (auto bullet : m_ActiveBullets)
			m_2dRenderer->drawSprite(m_BulletTexture, bullet->m_PosX, bullet->m_PosY, NULL, NULL, NULL, 1);

		if (m_BossAlive == false && m_GameTimer > 26)
			for (size_t i = 0; i < m_asteroidCount; ++i)
				m_2dRenderer->drawSprite(m_asteroidTexture, m_spaceRocks[i].m_asteroidPosX, m_spaceRocks[i].m_asteroidPosY, NULL, NULL, m_asteroidRotation, 0.2f);

		if (m_BossAlive == true)
		{
			m_2dRenderer->drawSprite(m_asteroidTexture, boss.m_PosX, boss.m_PosY, NULL, NULL, boss.m_Rotation, 0.2f);

			for (size_t i = 0; i < boss.m_Health; ++i)
				m_2dRenderer->drawSprite(m_BossHealthTexture, 
					(getWindowWidth() / 2 - m_BossHealthTexture->getHeight() * 2.5f + 10) + i * (m_BossHealthTexture->getHeight() + 5), 
					getWindowHeight() - m_BossHealthTexture->getWidth(), 
					NULL, NULL, getRadians(90), 0.1f);
		}

		if (m_YouDed == false)
		{
			m_2dRenderer->drawSprite(m_shipTexture, m_shipPosX, m_shipPosY, NULL, NULL, m_shipRotation, 0.4f);

			for (size_t i = 0; i < m_ShipHealth; ++i)
				m_2dRenderer->drawSprite(m_HealthTexture,
				getWindowWidth() - m_HealthTexture->getHeight() + 10,
					0 + m_HealthTexture->getWidth() + i * (m_HealthTexture->getWidth() + 5),
					NULL, NULL, getRadians(90), 0.1f);

			if (m_ShipInvulnerable == true)
				m_2dRenderer->drawSprite(m_ShieldTexture, m_shipPosX, m_shipPosY, 100, 100, m_shipRotation, 0.3f);
		}
		if (m_BossAlive == true && m_DeathTimer > 5 || m_BossAlive == false && m_YouDed == true)
		{
			m_2dRenderer->drawText(m_font, "Earth blew up.", getWindowWidth() / 2, getWindowHeight() / 2, 0);
			if (m_BossAlive == false && m_YouDed == true)
			{
				m_2dRenderer->drawText(m_font, "BUT, only you died Congrats!", getWindowWidth() / 2, getWindowHeight() / 2 - 40, 0);
				m_2dRenderer->drawText(m_font, "At least humanity can now Noahs Ark Mars or something", getWindowWidth() / 2, getWindowHeight() / 2 - 80, 0);
			}
			else
				m_2dRenderer->drawText(m_font, "There were no survivors.", getWindowWidth() / 2, getWindowHeight() / 2 - 40, 0);
		}

		// output some text, uses the last used colour
		if (m_YouDed != true)
			if (m_BossAlive == true)
			{
				if (m_GameTimer < 3)
					m_2dRenderer->drawText(m_font, "You are Earth's last line of defence!", 0, 10, 0.1f);
				else if (m_GameTimer > 3)
					m_2dRenderer->drawText(m_font, "DESTROY: The Rock", 0, 10, 0.1f);
			}
			else
			{
				if (m_GameTimer < 3)
					m_2dRenderer->drawText(m_font, "DESTROYED: The Rock", 0, 10, 0.1f);
				else if (m_GameTimer < 6)
					m_2dRenderer->drawText(m_font, "But", 0, 10, 0.1f);
				else if (m_GameTimer < 8)
					m_2dRenderer->drawText(m_font, "There's not just one asteroid", 0, 10, 0.1f);
				else if (m_GameTimer < 10)
					m_2dRenderer->drawText(m_font, "The entire Asteroid Belt is heading this way", 0, 10, 0.1f);
				else if (m_GameTimer < 11)
					m_2dRenderer->drawText(m_font, "Welp", 0, 10, 0.1f);
				else if (m_GameTimer < 15)
					m_2dRenderer->drawText(m_font, "You do know that there were already EVAC warpgates back here on Earth?", 0, 10, 0.1f);
				else if (m_GameTimer < 18)
					m_2dRenderer->drawText(m_font, "Unfortunately for you, due to the SPACE FORCE's poor funding", 0, 10, 0.1f);
				else if (m_GameTimer < 21)
					m_2dRenderer->drawText(m_font, "Your RUST BUCKET MK1 does not have a FTL drive or a fast enough engine", 0, 10, 0.1f);
				else if (m_GameTimer < 22)
					m_2dRenderer->drawText(m_font, "So..", 0, 10, 0.1f);
				else
					m_2dRenderer->drawText(m_font, "TRY NOT TO DIE :D", 0, 10, 0.1f);
			}

		break;
	}
	case SpinnySpaceRocksApp::Instructions:
	{

		m_2dRenderer->drawText(m_font, "MOVEMENT : WASD Keys", 0 + 10, getWindowHeight() - 40, 0);
		m_2dRenderer->drawText(m_font, "FIRE     : Left Mouse", 0 + 10, getWindowHeight() - 80, 0);
		m_2dRenderer->drawText(m_font, "INSTRUCTIONS : From your smecksy commander", 0 + 10, getWindowHeight() - 160, 0);
		m_2dRenderer->drawText(m_font, "Destroy The Rock by shooting it while it's vulnerable", 0 + 10, getWindowHeight() - 200, 0);
		m_2dRenderer->drawText(m_font, "It spins incredibly fast for a while after being damaged", 0 + 10, getWindowHeight() - 240, 0);
		m_2dRenderer->drawText(m_font, "Invulnerable while in this state", 0 + 10, getWindowHeight() - 280, 0);

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

void SpinnySpaceRocksApp::bossExplosion()
{
	if (m_InactiveMinions.size() > 10)
	{
		double increment = getRadians(360) / 10;
		double angle = 0;

		if (evenRings == true)
		{
			angle += increment * 0.5f;
			evenRings = false;
		}
		else
			evenRings = true;

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
	}
}

