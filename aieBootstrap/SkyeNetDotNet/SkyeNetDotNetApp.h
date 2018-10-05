#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>
#include <list>
#include <set>
#include "Tank.h"

struct MeshNode
{
	MeshNode(const Vector2& pos)
	{
		position = pos;
	}

	Vector2 position;

	MeshNode* nextNode = nullptr;
	MeshNode* prevNode = nullptr;
	Plane2D toNext;

	float greaterRadian;
	float lesserRadian;
	bool flipAngle = false;
};

struct Triangle
{
	Triangle(MeshNode* m1, MeshNode* m2, MeshNode* m3)
	{
		vertexA = m1;
		vertexB = m2;
		vertexC = m3;
		position = Vector2((m1->position[0] + m2->position[0] + m3->position[0]) / 3, (m1->position[1] + m2->position[1] + m3->position[1]) / 3);
	}
	Vector2 position;

	MeshNode* vertexA;
	MeshNode* vertexB;
	MeshNode* vertexC;
	std::set<Triangle*> connections;
};

struct PathNode
{
	PathNode(Triangle* t)
	{
		triangle = t;
	}
	Triangle* triangle;

	float fScore = 0;
	float hScore = 0;
	float gScore = 0;
	PathNode* parent = nullptr;
};

class Ant;
class Food;

class SkyeNetDotNetApp : public aie::Application {
public:

	SkyeNetDotNetApp();
	virtual ~SkyeNetDotNetApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void createNavMesh();
	void pathFind(Tank* ai, const Vector2& destination);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	aie::Texture* m_TankBarrelTex;
	aie::Texture* m_SkyeNetTankTex;
	aie::Texture* m_PlayerTankTex;
	aie::Texture* m_MapTex;
	aie::Texture* m_RedDot;

	SceneObject* m_Origin;

	std::vector<Tank*> m_Tanks;
	unsigned int m_TankPoolCount = 1;

	std::list<Triangle*>m_Triangles;
	std::list<MeshNode*> m_MeshNodes;
	unsigned int m_NodeSpacing = 20;
	unsigned int m_Red = 195, m_Green = 195, m_Blue = 195;

	// Row count starts from the top of the image, therefore the top row = 1 and the bottom row = image height
	// RGB, Red = 0, Green = 1, Blue = 2
	unsigned int getRGB(const aie::Texture* texture, unsigned int xCoord, unsigned int yCoord, unsigned int RGB) const;

	bool isEqualRGB(aie::Texture* texture, unsigned int x, unsigned int y);
	bool isEdge(aie::Texture* texture, unsigned int x, unsigned int y);
	bool isVertex(aie::Texture* texture, unsigned int x, unsigned int y);

	bool isConnectionValid(const MeshNode& from, const Vector2& to);
};