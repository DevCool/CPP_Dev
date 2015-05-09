#ifndef GameClass_hpp
#define GameClass_hpp

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <iostream>


// Game Class Definition
class GameClass {

private:
	sf::Window _window;
	sf::ContextSettings _settings;
	sf::Event _event;

	bool _running;

	GameClass(void);
	~GameClass(void);

public:
	static GameClass& getGameClass(void);
	static void destroyGameClass(void);

	int Start(void);

};


#endif

