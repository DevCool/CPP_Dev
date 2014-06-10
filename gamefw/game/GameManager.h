#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>

#include "RenderSystem.h"

class GameManager
{
private:

	bool _running;
	GLFWwindow *_window;
	RenderSystem *_renderSystem;

	VertexBuffer *vertexBuffer;

	GameManager(bool _running);
	~GameManager();

public:

	void runGameLoop();

	static GameManager& getGameManager();
	static void destroyGameManager();
};

#endif
