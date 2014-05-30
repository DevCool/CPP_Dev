#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
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

