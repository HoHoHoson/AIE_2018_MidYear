#pragma once

#include "Renderer2D.h"
#include "AIBase.h"
#include <vector>

namespace aie
{
	class Texture;
}

class Tank : public AIBase
{
public:

	enum state
	{
		find,
		home
	};

	state m_state;

	enum Team
	{
		Player,
		SkyeNet
	};

	Tank(aie::Texture* skyeNet, aie::Texture* player, aie::Texture* barrel);
	~Tank();

	void update(float deltaTime, const Vector4& des);
	void draw(aie::Renderer2D* m_Render);

	void setTeam(Team setTo);
	std::list<Vector2>& setPath();
	Vector2 homeVec;

private:


	Team m_Team;

	aie::Texture* m_BarrelTexture;
	aie::Texture* m_SkyeNetTexture;
	aie::Texture* m_PlayerTexture;

	SceneObject m_TurretObj;
	SceneObject m_BarrelObj;

	std::list<Vector2> m_Pathfind;

};
