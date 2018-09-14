#pragma once

#include <vector>

#include "Application.h"
#include "Renderer2D.h"

#include <fstream>
#include "SceneObj.h"
#include "Circlagon.h"

struct Score
{
	std::string name;
	float time;
};

struct ScoreToData
{
	ScoreToData(){}
	ScoreToData(const Score& store)
	{
		strcpy_s(nameData, 255, store.name.data());
		timeData = store.time;
	}
	char nameData[256];
	float timeData;
};

class NotSoSupaCirclagonApp : public aie::Application {
public:

	NotSoSupaCirclagonApp();
	virtual ~NotSoSupaCirclagonApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	aie::Texture* m_PlayerTex;
	aie::Texture* m_CircleTex;
	aie::Texture* m_SafeTex;

	const unsigned int m_RingCount = 30;

	float m_GameTime;

	float m_SpawnTimer = 0;
	float m_SpawnRate;

	float m_WidthMid;
	float m_HeightMid;
	float m_PlayerSpeed;
	int m_SetSpeed = 360;

	SceneObj m_Origin;
	SceneObj m_PlayerOrigin;
	SceneObj m_PlayerPos;
	Circle m_PlayerBounds;
	std::vector<Circlagon*> m_Circlagons;

	enum Patterns
	{
		Stairs,
		Random
	};
	Patterns p;
	float m_RingAngle = 0;
	int m_RingSpeed;
	float m_ScaleSpeed;
	float m_Set;
	bool m_IsSet = false;

	enum GameStates
	{
		Menu,
		Game,
		GameOver,
		HighScores,
		HighScoreInput,
		Controls
	};
	GameStates state;

	Score scoreTable[10];

	void setDefaultTable();
	void saveTable();
	void loadTable();

	bool isInside(const Circle& obj, const Circle& bounds) const;
	void insertPattern(Circlagon* c);
	void reloadGame();
};

static bool operator<(const Score& a, const Score& b)
{
	return a.time < b.time;
}