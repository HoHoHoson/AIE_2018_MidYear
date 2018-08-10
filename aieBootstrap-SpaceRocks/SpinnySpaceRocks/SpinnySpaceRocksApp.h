#pragma once

#include "Application.h"
#include "Renderer2D.h"


struct Asteroid
{
	bool spinninX;
	bool m_switchDirX;
	bool m_coolDownX;
	bool m_switchDirY;
	bool m_coolDownY;
	int m_asteroidPosX;
	int m_asteroidPosY;
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

	bool checkCollision(Asteroid smallerTex);
	int getRandom(int min, int max);

	aie::Texture* m_shipTexture;
	aie::Texture* m_asteroidTexture;

	bool m_makeEven;

	int asteroidWidth;
	int asteroidHeight;
	int shipWidth;
	int shipHeight;

	unsigned int m_shipPosX;
	unsigned int m_shipPosY;
	float m_shipSpeed;
	float m_shipRotation;

	Asteroid* m_spaceRocks;
	unsigned int m_asteroidCount;
	float m_asteroidRotation;
};

