#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#define GLFW_INCLUDE_GLU

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "ShaderInterface.h"

class RenderSystem
{
private:

	GLFWwindow *_window;

	std::vector<ShaderInterface *> *shaderArray;

	RenderSystem();
	~RenderSystem();

public:

	void render(VertexBuffer *vertexBuffer);

	static RenderSystem& getRenderSystem();
	static void destroyRenderSystem();
};

#endif

