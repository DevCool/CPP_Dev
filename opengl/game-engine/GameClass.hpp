#ifndef GameClass_hpp
#define GameClass_hpp

#include <SFML/Window.hpp>
#include <iostream>

#include "RenderSystem.hpp"


// Game Class Definition
class GameClass {

private:
	sf::Window _window;
	sf::ContextSettings _settings;
	sf::Event _event;

	bool _running;

	RenderSystem* _renderSystemObj;

	GameClass(void);
	~GameClass(void);

public:
	static GameClass& getGameClass(void);
	static void destroyGameClass(void);

	int Start(void);

};


#endif

