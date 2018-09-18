#pragma once

#include "Vector2.h"
#include "2D_Collision.h"
#include "Algorithms.h"
#include "Renderer2D.h"
#include "Texture.h"

class Food
{
public:

	Food(aie::Texture* tex);

	void setup(const Vector2& randPos);
	bool checkCollision(float deltaTime, const Vector2& ant);
	void render(aie::Renderer2D* renderer);

	bool checkStatus() const;
	Vector2 getPosition() const;

private:

	aie::Texture* m_Texture;
	Vector2 m_Position;
	Circle m_Bounds;

	bool m_Active;
};