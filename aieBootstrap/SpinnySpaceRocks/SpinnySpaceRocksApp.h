#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <string>
#include <time.h>
#include <random>
#include <algorithm>
#include <cassert>
#include <list>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>


struct AngryRock
{
	bool rebound = true;
	bool invincible = false;
	float coolDown = 0;
	float m_PosX;
	float m_PosY;
	float m_SpeedX;
	float m_SpeedY;
	float m_SetSpeed = 300;
	float m_Rotation = 0;
	float m_RotationSpeed = 1;
	int m_Health = 5;
};

struct LilRock
{
	float X;
	float Y;
	float speedX;
	float speedY;
	float setSpeed = 600;
};

struct Bullet
{
	float m_PosX;
	float m_PosY;
	float m_SpeedX;
	float m_SpeedY;
	float m_SetSpeed = 1000;
	float hurtsPlayer = false;
};

struct Asteroid
{
	bool spinninX;
	bool m_switchDirX;
	bool m_coolDownX;
	bool m_switchDirY;
	bool m_coolDownY;
	float m_asteroidPosX;
	float m_asteroidPosY;
	float m_asteroidSpeed;
};

class SpinnySpaceRocksApp : public aie::Application {
public:

	SpinnySpaceRocksApp();
	virtual ~SpinnySpaceRocksApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	bool checkCollision(aie::Texture* s_Obj, float s_X, float s_Y, aie::Texture* l_Obj, float l_X, float l_Y);
	int getRandom(int min, int max);
	double getRadians(double degrees);
	void setAnglesTo(float& moveX, float& moveY, float setSpeed, float currentX, float currentY, float toX, float toY, float deltaTime);
	float m_FirerateTimer = 0.0f;
	float m_GameTimer = 0;
	float iCantThinkSo = 0;
	float firerate_LMG = 0;

	aie::Texture* m_shipTexture;
	aie::Texture* m_asteroidTexture;
	aie::Texture* m_BulletTexture;
	aie::Texture* m_smlRockTexture;
	aie::Texture* m_HealthTexture;
	aie::Texture* m_BossHealthTexture;
	aie::Texture* m_ShieldTexture;
	aie::Texture* m_Crosshair;

	float m_CrosshairX;
	float m_CrosshairY;

	bool m_makeEven;
	bool set = false;

	int asteroidWidth;
	int asteroidHeight;
	int minionWidth;
	int minionHeight;
	int shipWidth;
	int shipHeight;

	bool m_YouDed = false;
	float m_DeathTimer = 0;
	float m_shipPosX;
	float m_shipPosY;
	float m_shipSpeed = 650;
	float m_shipRotation = 0;
	int m_ShipHealth = 5;
	bool m_ShipInvulnerable = false;
	float m_iCoolDown = 0;

	Asteroid* m_spaceRocks;
	unsigned int m_asteroidCount;
	float m_asteroidRotation;

	const size_t m_MaxBullets = 10;
	std::list<Bullet*> m_ActiveBullets;
	std::list<Bullet*> m_InactiveBullets;

	size_t m_ChoiceValue = 69;
	int m_Select;

	AngryRock boss;
	enum BossAI
	{
		Idle,
		Charge,
		RapidFire,
		Dead
	};
	BossAI bossState;
	void bossExplosion();
	float exTimer = 0;
	bool evenRings = true;
	bool lastStand = false;
	bool m_BossAlive = true;

	const size_t m_MaxMinions = 360;
	std::list<LilRock*> m_ActiveMinions;
	std::vector<LilRock*> m_InactiveMinions;

	enum GameState
	{
		Menu,
		Game,
		Instructions
	};
	GameState state;
};