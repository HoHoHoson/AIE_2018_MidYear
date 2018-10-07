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

	m_TankBarrelTex = new aie::Texture("../bin/textures/ball.png");
	m_SkyeNetTankTex = new aie::Texture("../bin/textures/blue_ant.png");
	m_PlayerTankTex = new aie::Texture("../bin/textures/tankBlue.png");
	m_MapTex = new aie::Texture("../bin/textures/map.png");
	m_RedDot = new aie::Texture("../bin/textures/redDot.png");

	createNavMesh();

	for (size_t i = 0; i < m_TankPoolCount; ++i)
	{
		Tank* newTank = new Tank(m_SkyeNetTankTex, m_PlayerTankTex, m_TankBarrelTex);

		newTank->setPosition(Vector4(10, 700, 0, 0));
		m_Tanks.push_back(newTank);
	}

	m_Origin = new SceneObject;
	m_Origin->addChild(m_Tanks.at(0)->getSceneObj());

	ball = { (float)(getWindowWidth() / 2), 700 };

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

	Circle ballC(ball, 30);

	for (auto t : m_Tanks)
	{
		if (t->m_state == t->find)
		{
			if (t->setPath().empty() == true)
				pathFind(m_Tanks.front(), ball);

			if (ballC.checkCollision(Circle(t->getPosition(), 30)) == true)
			{
				Vector2 newPOS;
				do
				{
					newPOS = { (float)(rand() % (getWindowWidth() - 40) + 20), (float)(rand() % (getWindowHeight() - 40) + 20) };

				} while (isEqualRGB(m_MapTex, newPOS[0], (getWindowHeight() - newPOS[1])) == false);
			
				ball = newPOS;
				t->setPath().clear();
				t->m_state = t->home;
			}
		}
		else
		{
			if (t->setPath().empty() == true)
				pathFind(m_Tanks.front(), t->homeVec);

		}
		t->update(deltaTime, Vector4(ball[0], ball[1], 0, 0));
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
	
	m_2dRenderer->drawSprite(m_TankBarrelTex, ball[0], ball[1]);

	for (auto mNode : m_MeshNodes)
	{
		m_2dRenderer->drawSprite(m_RedDot, (*mNode).position[0], (*mNode).position[1]);
		m_2dRenderer->drawLine(mNode->position[0], mNode->position[1], mNode->nextNode->position[0], mNode->nextNode->position[1], 2, 0.1f);
	}

	for (auto tri : m_Triangles)
	{
		m_2dRenderer->drawSprite(m_RedDot, tri->position[0], tri->position[1]);
		m_2dRenderer->drawLine(tri->vertices.at(0)->position[0], tri->vertices.at(0)->position[1], tri->vertices.at(1)->position[0], tri->vertices.at(1)->position[1], 2, 0.1f);
		m_2dRenderer->drawLine(tri->vertices.at(1)->position[0], tri->vertices.at(1)->position[1], tri->vertices.at(2)->position[0], tri->vertices.at(2)->position[1], 2, 0.1f);
		m_2dRenderer->drawLine(tri->vertices.at(2)->position[0], tri->vertices.at(2)->position[1], tri->vertices.at(0)->position[0], tri->vertices.at(0)->position[1], 2, 0.1f);
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

	// finds all the nodes that make up the edge between safe and out of bounds
	for (size_t yNode = 0; yNode <= yNodeCount; ++yNode)
		for (size_t xNode = 0; xNode <= xNodeCount; ++xNode)
		{
			x = xNode * m_NodeSpacing;
			y = yNode * m_NodeSpacing;

			if (isEdge(m_MapTex, x, y) == true)
				m_MeshNodes.push_back(new MeshNode(Vector2(x, getWindowHeight() - y)));
		}	

	// links up edges to form complete loops where needed
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
				it->toNext = Plane2D(it->position, it->nextNode->position);
				it->nextNode->prevNode = it;
				it = it->nextNode;

			} while (it != n);
		}
	}

	// removes all non vertex nodes 
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

	// gives each node a valid cone of vision for nodes that can be connected to
	for (auto n : m_MeshNodes)
	{
		if (n->position[0] == 720 && n->position[1] == 520)
			int inn = 0;

		Vector2 nextVec = n->nextNode->position - n->position;
		Vector2 prevVec = n->prevNode->position - n->position;
		float nextAngle = atan2(nextVec[1], nextVec[0]);
		float prevAngle = atan2(prevVec[1], prevVec[0]);

		if (nextAngle < 0)
			nextAngle += M_PI * 2;
		if (prevAngle < 0)
			prevAngle += M_PI * 2;

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

		float checkRadian = 0;

		if (n->position[0] == 0)
			checkRadian = M_PI;
		else if (n->position[0] == m_MapTex->getWidth())
			checkRadian = 0;
		else if (n->position[1] == 0)
			checkRadian = M_PI * 1.5f;
		else if (n->position[1] == m_MapTex->getHeight())
			checkRadian = M_PI * 0.5f;
		else if (isEqualRGB(m_MapTex, n->position[0], getWindowHeight() - n->position[1] + m_NodeSpacing) == false)
			checkRadian = M_PI * 1.5f;
		else if (isEqualRGB(m_MapTex, n->position[0], getWindowHeight() - n->position[1] - m_NodeSpacing) == false)
			checkRadian = M_PI * 0.5f;
		else if (isEqualRGB(m_MapTex, n->position[0] + m_NodeSpacing, n->position[1]) == false)
			checkRadian = 0;
		else if (isEqualRGB(m_MapTex, n->position[0] - m_NodeSpacing, n->position[1]) == false)
			checkRadian = M_PI;

		if (checkRadian > n->lesserRadian && checkRadian < n->greaterRadian)
			n->flipAngle = true;
	}

	Triangle* curTriangle = nullptr;
	Triangle* prevTriangle = nullptr;
	Ray2D ray;
	Vector2 midRay;
	MeshNode* node1 = m_MeshNodes.front();
	MeshNode* node2 = node1->nextNode;
	MeshNode* node3 = nullptr;

	do
	{
		node3 = nullptr;
		ray = Ray2D(node1->position, node2->position, (node2->position - node1->position).magnitude());
		midRay = ray.getOrigin() + ray.getDirection() * (ray.getLength() * 0.5f);

		for (auto n : m_MeshNodes)
		{
			if (n->position[0] == 920 && n->position[1] == 720)
				ray = ray;

			if (isConnectionValid(*node1, n->position) && isConnectionValid(*node2, n->position))
			{
				bool empty = true;

				Vector2 checkValid1 = n->position - node1->position;
				Vector2 checkValid2 = n->position - node2->position;
				checkValid1.normalise();
				checkValid2.normalise();
				float dotCheck1 = HLib::roundTo(checkValid1.dot(ray.getDirection()), 3);
				float dotCheck2 = HLib::roundTo(checkValid2.dot(ray.getDirection()), 3);

				if (dotCheck1 == 1 || dotCheck1 == -1 || dotCheck2 == 1 || dotCheck2 == -1)
					empty = false;
				else
					for (auto tri : m_Triangles)
						for (auto usedVertex : tri->vertices)
							if (n == usedVertex)
							{
								empty = false;
								break;
							}

				if (empty == true)
					if (node3 == nullptr)
						node3 = n;
					else
					{
						float set = HLib::MagPow2_2D(node3->position, midRay);
						float to = HLib::MagPow2_2D(n->position, midRay);

						if (to < set)
							node3 = n;
					}
			}
		}

		if (node3 != nullptr)
		{
			curTriangle = new Triangle(node1, node2, node3);
			m_Triangles.push_back(curTriangle);

			if (prevTriangle != nullptr)
			{
				prevTriangle->connections.insert(curTriangle);
				curTriangle->connections.insert(prevTriangle);
			}
			prevTriangle = curTriangle;
	
			if (node3 == node1->nextNode || node3 == node1->prevNode)
				node1 = node3;
			else
				node2 = node3;
		}

	} while (node3 != nullptr);
}

void SkyeNetDotNetApp::pathFind(Tank* ai, const Vector2 & destination)
{
	PathNode* start = nullptr;
	PathNode* end = nullptr;
	PathNode* current = nullptr;
	PathNode* temp = nullptr;

	Triangle* closest = nullptr;
	for (auto tri : m_Triangles)
	{
		if (closest == nullptr)
			closest = tri;
		else if (closest != tri)
		{
			Vector4 test = ai->getPosition();
			float set = HLib::MagPow2_2D(closest->position, ai->getPosition());
			float to = HLib::MagPow2_2D(tri->position, ai->getPosition());

			if (to < set)
				closest = tri;
		}
	}

	start = new PathNode(closest);
	closest = nullptr;

	for (auto tri : m_Triangles)
	{
		if (closest == nullptr)
			closest = tri;
		else if (closest != tri)
		{
			float set = HLib::MagPow2_2D(closest->position, destination);
			float to = HLib::MagPow2_2D(tri->position, destination);

			if (to < set)
				closest = tri;
		}
	}

	end = new PathNode(closest);
	closest = nullptr;

	std::list<PathNode*> openNodes;
	std::list<PathNode*> closedNodes;

	start->gScore = 0;
	start->hScore = HLib::MagPow2_2D(start->triangle->position, end->triangle->position);
	start->fScore = start->hScore + start->gScore;

	openNodes.push_back(start);

	while (openNodes.empty() != true)
	{
		for (auto open : openNodes)
		{
			if (current == nullptr)
				current = open;
			else
				if (open->fScore < current->fScore)
					current = open;
		}

		openNodes.remove(current);
		closedNodes.push_back(current);

		if (current->triangle == end->triangle)
			break;

		for (auto child : current->triangle->connections)
		{
			bool closed = false;

			for (auto c : closedNodes)
				if (c->triangle == child)
					closed = true;

			if (closed == false)
			{
				for (auto o : openNodes)
					if (o->triangle == child)
						temp = o;

				PathNode* newNode = new PathNode(child);
				newNode->parent = current;
				newNode->gScore = HLib::MagPow2_2D(child->position, current->triangle->position) + current->gScore;
				newNode->hScore = HLib::MagPow2_2D(child->position, end->triangle->position);
				newNode->fScore = newNode->hScore + newNode->gScore;

				if (temp != nullptr)
					if (newNode->gScore < temp->gScore)
					{
						openNodes.remove(temp);
						delete temp;
						temp = nullptr;
					}

				openNodes.push_back(newNode);
			}
		}

		current = nullptr;
	}

	if (current != nullptr)
	{
		ai->setPath().push_back(destination);
		while (current != nullptr)
		{
			ai->setPath().push_back(current->triangle->position);
			current = current->parent;
		}
	}

	//if (current != nullptr)
	//{
	//	ai->setPath().clear();

	//	std::list<Triangle*> funnel;
	//	do
	//	{
	//		funnel.push_front(current->triangle);
	//		current = current->parent;

	//	} while (current != nullptr);

	//	Vector2 rayOrigin(ai->getPosition()[0], ai->getPosition()[1]);
	//	std::list<Vector2*> rayPath;
	//	std::vector<MeshNode*> portalPath;

	//	Triangle* previous = nullptr;
	//	for (auto tri : funnel)
	//	{
	//		if (previous == nullptr)
	//			previous = tri;
	//		else
	//		{
	//			for (auto pv : previous->vertices)
	//				for (auto nv : tri->vertices)
	//					if (pv == nv)
	//					{
	//						bool dupe = false;
	//						for (auto node : portalPath)
	//							if (node == pv)
	//							{
	//								dupe = true;
	//								break;
	//							}

	//						if (dupe == false)
	//							portalPath.push_back(pv);
	//					}
	//		}
	//		previous = tri;
	//	}

	//	std::vector<Ray2D*> portalEdges;
	//	std::vector<Vector2*> ray1Path;
	//	std::vector<Vector2*> ray2Path;

	//	for (size_t i = 0; i < portalPath.size(); ++i)
	//		if (i % 2 == 0)
	//			ray2Path.push_back(new Vector2(portalPath.at(i)->position));
	//		else
	//			ray1Path.push_back(new Vector2(portalPath.at(i)->position));

	//	ray1Path.push_back(new Vector2(destination));
	//	ray2Path.push_back(new Vector2(destination));

	//	std::set<Vector2*>collided;
	//	auto ray1End = ray1Path.begin();
	//	auto ray2End = ray2Path.begin();
	//	auto ray1Prev = ray1End;
	//	auto ray2Prev = ray2End;

	//	while(**ray1End != destination && **ray2End != destination)
	//	{
	//		if (ray1End != ray1Path.end())
	//			ray1Prev = ray1End++;
	//		if (ray2End != ray2Path.end())
	//			ray2Prev = ray2End++;

	//		Ray2D r1Path(**ray1Prev, **ray1End, (**ray1End - **ray1Prev).magnitude());
	//		Ray2D r2Path(**ray2Prev, **ray2End, (**ray2End - **ray2Prev).magnitude());
	//		if (r1Path.checkCollision(r2Path) == true)
	//		{
	//			Vector2 temp1 = **ray1End;
	//			Vector2 temp2 = **ray2End;

	//			for (auto r1 : ray1Path)
	//				if (r1 == *ray1End)
	//				{
	//					*r1 = temp2;
	//					break;
	//				}
	//			for (auto r2 : ray2Path)
	//				if (r2 == *ray2End)
	//				{
	//					*r2 = temp1;
	//					break;
	//				}

	//			if (**ray1End != destination && **ray2End != destination)
	//			{
	//				ray1End = ray1Path.begin();
	//				ray2End = ray2Path.begin();
	//			}
	//		}
	//	}

	//	for (size_t i = 0; i < ray1Path.size(); ++i)
	//	{
	//		if (i != 0)
	//			portalEdges.push_back(new Ray2D(*ray1Path.at(i - 1), *ray1Path.at(i), (*ray1Path.at(i) - *ray1Path.at(i - 1)).magnitude()));
	//	}

	//	for (size_t i = 0; i < ray2Path.size(); ++i)
	//	{
	//		if (i != 0)
	//			portalEdges.push_back(new Ray2D(*ray2Path.at(i - 1), *ray2Path.at(i), (*ray2Path.at(i) - *ray2Path.at(i - 1)).magnitude()));
	//	}

	//	ray1End = ray1Path.begin();
	//	ray2End = ray2Path.begin();

	//	do
	//	{
	//		while (collided.size() != 2)
	//		{

	//			if (collided.find(*ray1End) != collided.end() == false)
	//			{
	//				Ray2D r1(rayOrigin, **ray1End, (**ray1End - rayOrigin).magnitude());

	//				for (auto plane : portalEdges)
	//					if (plane->getOrigin() != rayOrigin && plane->getEnd() != rayOrigin && plane->getOrigin() != **ray1End && plane->getEnd() != **ray1End)
	//						if (r1.checkCollision(*plane))
	//						{
	//							ray1End--;
	//							collided.insert(*ray1End);
	//							break;
	//						}

	//				if (**ray1End == destination)
	//					break;
	//				if (collided.find(*ray1End) != collided.end() == false)
	//					ray1End++;
	//			}

	//			if (collided.find(*ray2End) != collided.end() == false)
	//			{
	//				Ray2D r2(rayOrigin, **ray2End, (**ray2End - rayOrigin).magnitude());

	//				for (auto plane : portalEdges)
	//					if (plane->getOrigin() != rayOrigin && plane->getEnd() != rayOrigin && plane->getOrigin() != **ray2End && plane->getEnd() != **ray2End)
	//						if (r2.checkCollision(*plane))
	//						{
	//							ray2End--;
	//							collided.insert(*ray2End);
	//							break;
	//						}

	//				if (**ray2End == destination)
	//					break;
	//				if (collided.find(*ray2End) != collided.end() == false && **ray2End != destination)
	//					ray2End++;
	//			}
	//		}
	//		if (**ray1End != destination && **ray2End != destination)
	//		{
	//			ai->setPath().push_front(**collided.begin());
	//			rayOrigin = **collided.begin();
	//			collided.clear();
	//		}
	//		else
	//		{
	//			ai->setPath().push_front(destination);
	//			break;
	//		}

	//	} while (true);
	//} 


	for (auto openData : openNodes)
		delete openData;
	for (auto closedData : closedNodes)
		delete closedData;
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

bool SkyeNetDotNetApp::isConnectionValid(const MeshNode & from, const Vector2 & to)
{
	if (from.position[0] == to[0] && from.position[1] == to[1])
		return false;

	float destRadian = atan2(to[1] - from.position[1], to[0] - from.position[0]);
	if (destRadian < 0)
		destRadian += M_PI * 2;

	if (from.flipAngle == true)
	{
		if (destRadian <= from.lesserRadian)
			destRadian += M_PI * 2;
		if (destRadian >= from.greaterRadian || destRadian == 0)
			return true;
		else
			return false;
	}
	else
		if (destRadian >= from.lesserRadian && destRadian <= from.greaterRadian)
			return true;
		else
			return false;
}
