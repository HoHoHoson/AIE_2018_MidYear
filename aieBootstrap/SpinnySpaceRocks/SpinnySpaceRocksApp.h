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
	bool invincible = true;
	float m_PosX;
	float m_PosY;
	float m_SpeedX;
	float m_SpeedY;
	float m_SetSpeed = 300;
	float m_Rotation = 0;
	float m_RotationSpeed = 1;
	float m_Health = 5;
};

struct LilRock
{
	float X;
	float Y;
	float speedX;
	float speedY;
	float setSpeed = 1000;
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
	float m_Timer = 0.0f;

	aie::Texture* m_shipTexture;
	aie::Texture* m_asteroidTexture;
	aie::Texture* m_BulletTexture;
	aie::Texture* m_smlRockTexture;

	bool m_makeEven;
	bool set = false;

	int asteroidWidth;
	int asteroidHeight;
	int minionWidth;
	int minionHeight;
	int shipWidth;
	int shipHeight;

	float m_shipPosX;
	float m_shipPosY;
	float m_shipSpeed = 600;
	float m_shipRotation = 0;

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
	};
	BossAI bossState;

	const size_t m_MaxMinions = 360;
	std::list<LilRock*> m_ActiveMinions;
	std::vector<LilRock*> m_InactiveMinions;

	enum GameState
	{
		Menu,
		Game
	};
	GameState state;
};