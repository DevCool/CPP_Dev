#ifndef RenderSystem_hpp
#define RenderSystem_hpp

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <iostream>


// Render System Class
class RenderSystem {

private:
	RenderSystem(void);
	~RenderSystem(void);

public:
	static RenderSystem& getRenderSystem(void);
	static void destroyRenderSystem(void);

	bool InitGL(sf::Window& window, sf::Event& event);
	void Render(void);
	void Update(void);

};


#endif

