#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <string>
#include <time.h>
#include <random>
#include <algorithm>
#include <cassert>
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>


struct AngryRock
{
	float m_PosX;
	float m_PosY;

};

struct Bullet
{
	float m_PosX;
	float m_PosY;
	float m_AngX;
	float m_AngY;
	float m_Speed = 800;
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

	aie::Texture* m_shipTexture;
	aie::Texture* m_asteroidTexture;
	aie::Texture* m_BulletTexture;

	bool m_makeEven;

	int asteroidWidth;
	int asteroidHeight;
	int shipWidth;
	int shipHeight;

	float m_shipPosX;
	float m_shipPosY;
	float m_shipSpeed;
	float m_shipRotation;

	Asteroid* m_spaceRocks;
	unsigned int m_asteroidCount;
	float m_asteroidRotation;

	std::list<Bullet*> m_ActiveBullets;
	std::list<Bullet*> m_InactiveBullets;

	size_t m_ChoiceValue = 69;
	int m_Select;

	enum GameState
	{
		Menu,
		Game
	};
	GameState state;
};

// CODE FOR DIRECTIONAL MOVEMENT (make it into a function) 
	//dy = PositionDestination.Y - PositionCurrent.Y
	//dx = PositionDestination.X - PositionCurrent.X
	//angle = atan2(dy / dx)
	//
	//posY += cos(angle) * speed
	//posX -= sin(angle) * speed