#include "SkyeNetDotNetApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <time.h>

SkyeNetDotNetApp::SkyeNetDotNetApp() 
{
	srand((unsigned int)time(nullptr));
}

SkyeNetDotNetApp::~SkyeNetDotNetApp() {

}

bool SkyeNetDotNetApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_TankBarrelTex = new aie::Texture("../bin/textures/barrelBeige.png");
	m_SkyeNetTankTex = new aie::Texture("../bin/textures/tankYellow.png");
	m_PlayerTankTex = new aie::Texture("../bin/textures/tankBlue.png");
	m_MapTex = new aie::Texture("../bin/textures/map.png");
	m_RedDot = new aie::Texture("../bin/textures/redDot.png");

	createNavMesh();

	for (size_t i = 0; i < m_TankPoolCount; ++i)
	{
		Tank* newTank = new Tank(m_SkyeNetTankTex, m_PlayerTankTex, m_TankBarrelTex);

		newTank->setPosition(Vector4(getWindowWidth() / 2, getWindowHeight() / 2, 0, 0));
		m_Tanks.push_back(newTank);
	}

	m_Origin = new SceneObject;
	m_Origin->addChild(m_Tanks.at(0)->getSceneObj());

	return true;
}

void SkyeNetDotNetApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void SkyeNetDotNetApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	HLib::clamp(deltaTime, 0, 0.1);

	for (auto t : m_Tanks)
	{
		t->update(deltaTime, Vector4(input->getMouseX(), input->getMouseY(), 0, 0));
	}

	m_Origin->update();
}

void SkyeNetDotNetApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->drawSprite(m_MapTex, 0, 0, NULL, NULL, NULL, 100.0f, 0.0f, 0.0f);
	
	for (auto mNode : m_MeshNodes)
	{
		m_2dRenderer->drawSprite(m_RedDot, (*mNode).position[0], (*mNode).position[1]);
		m_2dRenderer->drawLine(mNode->position[0], mNode->position[1], mNode->nextNode->position[0], mNode->nextNode->position[1], 2, 0.1f);
	}

	for (auto t : m_Tanks)
		t->draw(m_2dRenderer);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();
}

void SkyeNetDotNetApp::createNavMesh()
{
	unsigned int yNodeCount = getWindowHeight() / m_NodeSpacing;
	unsigned int xNodeCount = getWindowWidth() / m_NodeSpacing;
	unsigned int x, y;

	int width = m_MapTex->getWidth();
	int height = m_MapTex->getHeight();
	isEqualRGB(m_MapTex, width / 2, height / 2);

	for (size_t yNode = 0; yNode <= yNodeCount; ++yNode)
		for (size_t xNode = 0; xNode <= xNodeCount; ++xNode)
		{
			x = xNode * m_NodeSpacing;
			y = yNode * m_NodeSpacing;

			if (isEdge(m_MapTex, x, y) == true)
				m_MeshNodes.push_back(new MeshNode(Vector2(x, getWindowHeight() - y)));
		}	

	for (auto n : m_MeshNodes)
	{
		if (n->nextNode == nullptr && n->prevNode == nullptr)
		{
			auto it = n;

			do
			{
				for (auto node : m_MeshNodes)
				{
					if (node->prevNode == nullptr && node != it->prevNode && node != it)
					{
						if (it->nextNode == nullptr)
							it->nextNode = node;
						else
						{
							float set = HLib::MagPow2_2D(it->position, it->nextNode->position);
							float other = HLib::MagPow2_2D(it->position, node->position);

							if (other < set)
								it->nextNode = node;
						}
					}
				}
				it->nextNode->prevNode = it;
				it = it->nextNode;

			} while (it != n);
		}
	}

	bool hasErased;
	auto it = m_MeshNodes.begin();
	while (it != m_MeshNodes.end())
	{
		hasErased = false;
		auto n = (*it);

		if (!isVertex(m_MapTex, n->position[0], getWindowHeight() - n->position[1]))
		{
			n->prevNode->nextNode = n->nextNode;
			n->nextNode->prevNode = n->prevNode;
			it = m_MeshNodes.erase(it);
			hasErased = true;
		}

		if (hasErased == false)
			it++;
	}

	for (auto n : m_MeshNodes)
	{
		Vector2 nextVec = n->nextNode->position - n->position;
		Vector2 prevVec = n->prevNode->position - n->position;
		float nextAngle = atan2(nextVec[0], nextVec[1]);
		float prevAngle = atan2(prevVec[0], prevVec[1]);

		if (nextAngle >= prevAngle)
		{
			n->greaterRadian = nextAngle;
			n->lesserRadian = prevAngle;
		}
		else
		{
			n->greaterRadian = prevAngle;
			n->lesserRadian = nextAngle;
		}

		Vector2 outsidePoint;
		Vector2 left(n->position[0] - m_NodeSpacing, n->position[1]);
		Vector2 right(n->position[0] + m_NodeSpacing, n->position[1]);
		Vector2 bottom(n->position[0], n->position[1] - m_NodeSpacing);
		Vector2 top(n->position[0], n->position[1] + m_NodeSpacing);

		if (n->position[0] == 0)
			outsidePoint = left;
		else if (n->position[0] == m_MapTex->getWidth())
			outsidePoint = right;
		else if (n->position[1] == 0)
			outsidePoint = bottom;
		else if (n->position[1] == m_MapTex->getHeight())
			outsidePoint = top;
		else if (isEqualRGB(m_MapTex, n->position[0], n->position[1] + m_NodeSpacing) == false)
			outsidePoint = top;
		else if (isEqualRGB(m_MapTex, n->position[0], n->position[1] - m_NodeSpacing) == false)
			outsidePoint = bottom;
		else if (isEqualRGB(m_MapTex, n->position[0] + m_NodeSpacing, n->position[1]) == false)
			outsidePoint = right;
		else if (isEqualRGB(m_MapTex, n->position[0] - m_NodeSpacing, n->position[1]) == false)
			outsidePoint = left;

		Vector2 invalidVec = outsidePoint - n->position;
		float check = atan2(invalidVec[0], invalidVec[1]);

		if (check > n->lesserRadian && check < n->greaterRadian)
			n->flipAngle = true;
	}
}

unsigned int SkyeNetDotNetApp::getRGB(const aie::Texture * texture, unsigned int xCoord, unsigned int yCoord, unsigned int RGB) const
{
	unsigned int w = texture->getWidth();
	unsigned int h = texture->getHeight();

	assert(xCoord <= w && xCoord >= 0 && "Invalid image xCoord number");
	assert(yCoord <= h && yCoord >= 0 && "Invalid image yCoord number");
	assert(RGB >= 0 && RGB <= 2 && "Invalid RGB value");

	unsigned int y = yCoord, x = xCoord;

	if (y == 0)
		y++;
	if (x == 0)
		x++;

	const unsigned char* c = texture->getPixels();
	unsigned int RGBValue = c[(y - 1) * w * 3 + (x - 1) * 3 + RGB];

	return RGBValue;
}

bool SkyeNetDotNetApp::isEqualRGB(aie::Texture* texture, unsigned int x, unsigned int y)
{
	if (getRGB(texture, x, y, 0) == m_Red &&
		getRGB(texture, x, y, 1) == m_Green &&
		getRGB(texture, x, y, 2) == m_Blue)
		return true;
	else
		return false;
}

bool SkyeNetDotNetApp::isEdge(aie::Texture * texture, unsigned int x, unsigned int y)
{
	if (isEqualRGB(texture, x, y) == true)
	{
		if (x == 0 || y == 0 || y == getWindowHeight() || x == getWindowWidth() ||
			isEqualRGB(texture, x, y + m_NodeSpacing) == false || isEqualRGB(texture, x, y - m_NodeSpacing) == false ||
			isEqualRGB(texture, x + m_NodeSpacing, y) == false || isEqualRGB(texture, x - m_NodeSpacing, y) == false)
			return true;
	}

	return false;
}

bool SkyeNetDotNetApp::isVertex(aie::Texture * texture, unsigned int x, unsigned int y)
{
	if (isEdge(texture, x, y) == true)
	{
		if (x == 0 && y == 0 || x == 0 && y == getWindowHeight() || y == 0 && x == getWindowWidth() || y == getWindowHeight() && x == getWindowWidth())
			return true;

		if (x == 0 || x == getWindowWidth())
		{
			if (isEdge(texture, x, y + m_NodeSpacing) == true && isEdge(texture, x, y - m_NodeSpacing) == true)
				return false;
			return true;
		}
		if (y == 0 || y == getWindowHeight())
		{
			if (isEdge(texture, x + m_NodeSpacing, y) == true && isEdge(texture, x - m_NodeSpacing, y) == true)
				return false;
			return true;
		}

		if (isEdge(texture, x, y + m_NodeSpacing) == true && isEdge(texture, x, y - m_NodeSpacing) == true ||
			isEdge(texture, x + m_NodeSpacing, y) == true && isEdge(texture, x - m_NodeSpacing, y) == true ||
			isEdge(texture, x - m_NodeSpacing, y - m_NodeSpacing) == true && isEdge(texture, x + m_NodeSpacing, y + m_NodeSpacing) == true ||
			isEdge(texture, x - m_NodeSpacing, y + m_NodeSpacing) == true && isEdge(texture, x + m_NodeSpacing, y - m_NodeSpacing) == true)
			return false;

		return true;
	}
	return false;
}
