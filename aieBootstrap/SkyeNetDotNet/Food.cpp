#include "Food.h"

Food::Food(aie::Texture* tex)
{
	m_Texture = tex;
	m_Active = false;
}

void Food::setup(const Vector2& randPos)
{
	m_Active = true;
	m_Position = randPos;
	m_Bounds.updateCircle(randPos, m_Texture->getWidth());
}

void Food::update(float deltaTime, const Vector2& ant)
{
	if (m_Bounds.checkCollision(Circle(ant, 0)) && m_Active == true)
		m_Active = false;
}

void Food::render(aie::Renderer2D * renderer)
{
	if (m_Active == true)
		renderer->drawSprite(m_Texture, m_Position[0], m_Position[1]);
}

bool Food::checkStatus() const
{
	return m_Active;
}

Vector2 Food::getPosition() const
{
	return m_Position;
}
