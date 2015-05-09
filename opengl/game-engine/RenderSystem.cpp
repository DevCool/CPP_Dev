#include "RenderSystem.hpp"

RenderSystem::RenderSystem(void) {

	// Constructor
	std::cout << "Render System Created!" << std::endl;

}

RenderSystem::~RenderSystem(void) {

	// Destructor
	std::cout << "Render System Destroyed!" << std::endl;

}

RenderSystem& RenderSystem::getRenderSystem(void) {

	static RenderSystem* renderSystemObj = NULL;

	if(renderSystemObj == NULL) {
		renderSystemObj = new RenderSystem();
	}

	return *renderSystemObj;
}

void RenderSystem::destroyRenderSystem(void) {

	RenderSystem* renderSystemObj = &getRenderSystem();
	delete renderSystemObj;

}

bool RenderSystem::InitGL(sf::Window& window, sf::Event& event) {

	bool success = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(glGetError() != GL_NO_ERROR) { success = false; }

	glViewport(0, 0, event.size.width, event.size.height);
	gluLookAt(0.0f, 1.0f, -5.0f,
		 0.0f, 0.0f, 0.0f,
		 0.0f, 1.0f, 0.0f);
	gluPerspective(45.0f, (float)(window.getSize().x/window.getSize().y),
			1.0f, 500.0f);

	if(glGetError() != GL_NO_ERROR) { success = false; }

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0.2f, 0.2f, 0.6f, 1.0f);

	if(glGetError() != GL_NO_ERROR) { success = false; }

	return success;

}

void RenderSystem::Render(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();

}

void RenderSystem::Update(void) {

}

