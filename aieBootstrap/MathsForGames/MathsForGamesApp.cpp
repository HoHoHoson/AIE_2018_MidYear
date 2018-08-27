#include "MathsForGamesApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>

MathsForGamesApp::MathsForGamesApp() {

}

MathsForGamesApp::~MathsForGamesApp() {

}

bool MathsForGamesApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// testing my Vector3 class's functions
	Vector3 v1(1, 2, 3);
	Vector3 v2(4, 5, 6);
	Vector3 v3(0);
	v3 = v1 / 2;
	// drawing the test Vector3s
	std::cout << "Vector3 One\n";
	for (size_t i = 0; i < 3; ++i)
		std::cout << v1[i] << std::endl;
	std::cout << "Vector3 Two\n";
	for (size_t i = 0; i < 3; ++i)
		std::cout << v2[i] << std::endl;
	std::cout << "Vector3 Three\n";
	for (size_t i = 0; i < 3; ++i)
		std::cout << v3[i] << std::endl;


	return true;
}

void MathsForGamesApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void MathsForGamesApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void MathsForGamesApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}