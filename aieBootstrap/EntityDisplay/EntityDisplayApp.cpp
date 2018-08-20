#include "EntityDisplayApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


EntityDisplayApp::EntityDisplayApp() {

}

EntityDisplayApp::~EntityDisplayApp() {

}

bool EntityDisplayApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	setBackgroundColour(1, 1, 1);

	// Display is a client, therefor it must use "OpenFileMapping" to access the virtual memory
	m_EntityCountMemory = OpenFileMapping(
		FILE_MAP_ALL_ACCESS, false, 
		L"EntityCountMemory"); // name of the memory block it needs to access

	// "mapped" a pointer so that the Display app can read/write the virtual memory
	m_EntityCounterPtr = (int*)MapViewOfFile(
		m_EntityCountMemory,
		FILE_MAP_ALL_ACCESS,
		0, 0, sizeof(int));

	m_entities.resize(*m_EntityCounterPtr);


	m_EntityDataMemory = OpenFileMapping(
		FILE_MAP_ALL_ACCESS, false,
		L"EntityDataMemory");

	m_EntityDataPtr = (Entity*)MapViewOfFile(
		m_EntityDataMemory,
		FILE_MAP_ALL_ACCESS,
		0, 0, m_entities.size() * sizeof(Entity));

	return true;
}

void EntityDisplayApp::shutdown() 
{
	// REMEMBER to "unmap" the pointer and "close" the HANDLE
	CloseHandle(m_EntityCountMemory);
	UnmapViewOfFile(m_EntityCounterPtr);
	UnmapViewOfFile(m_EntityDataPtr);
	CloseHandle(m_EntityDataMemory);

	delete m_font;
	delete m_2dRenderer;
}

void EntityDisplayApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// old C memory copy
	//memcpy(&m_entities[0], m_EntityDataPtr, m_entities.size() * sizeof(Entity));

	// new C++ memory copy
	std::copy(m_EntityDataPtr, m_EntityDataPtr + m_entities.size(), &m_entities[0]);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (*m_EntityCounterPtr == 0)
		quit();
}

void EntityDisplayApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw entities
	for (auto& entity : m_entities) {
		m_2dRenderer->setRenderColour(entity.r, entity.g, entity.b);
		m_2dRenderer->drawBox(entity.x, entity.y, entity.size, entity.size, entity.rotation);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}