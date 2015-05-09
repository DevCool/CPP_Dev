#include "GameClass.hpp"

// Constructor
GameClass::GameClass(void) {

	// Initialize private variables
	_running = true;
	_settings.antialiasingLevel = 4;
	_settings.depthBits = 32;
	_settings.stencilBits = 8;
	_settings.majorVersion = 3;
	_settings.minorVersion = 0;

	_window.create(sf::VideoMode(640, 480), "OpenGL Game Window",
			sf::Style::Default, _settings);
	_window.setVerticalSyncEnabled(true);

	std::cout << "Game Object Created!" << std::endl;
	_renderSystemObj = &RenderSystem::getRenderSystem();

}

// Destructor
GameClass::~GameClass(void) {

	// Delete resources and free memory here
	if(_renderSystemObj != NULL) {
		_renderSystemObj->destroyRenderSystem();
	}

	std::cout << "Game Object Destroyed!" << std::endl;

}

////////////////////////////////////////////////
// getGameClass() function
//
// note: Gets the object if one is created
//       else if it isn't created, this also creates
//       an object for it.
////////////////////////////////////////////////
GameClass& GameClass::getGameClass(void) {

	static GameClass* gameClassObj = NULL;

	if(gameClassObj == NULL) {
		gameClassObj = new GameClass();
	}

	return *gameClassObj;

}

/////////////////////////////////////////////////
// destroyGameClass() function
//
// note: This function is meant to free up
//       memory.
/////////////////////////////////////////////////
void GameClass::destroyGameClass(void) {

	GameClass* gameClassObj = &getGameClass();
	delete gameClassObj;

}

// Start() function : Main Game Loop resides in
// this function.
int GameClass::Start(void) {

	_renderSystemObj->InitGL(_window, _event);

	while(_running) {
		while(_window.pollEvent(_event)) {
			if((_event.type == sf::Event::Closed) ||
			   ((_event.type == sf::Event::KeyPressed) &&
			   (_event.key.code == sf::Keyboard::Escape))) {
				_running = false;
			}
			else if(_event.type == sf::Event::Resized) {
				glViewport(0, 0, _event.size.width, _event.size.height);
			}
		}

		_renderSystemObj->Update();
		_renderSystemObj->Render();
		_window.display();
	}

	destroyGameClass();

	return 0;

}

