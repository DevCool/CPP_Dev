#include "RenderSystem.h"

RenderSystem::RenderSystem(): _window(glfwGetCurrentContext())
{
	shaderArray = new std::vector<ShaderInterface *>;
	ShaderInterface *shader = new ShaderInterface("game/RenderSystem/Shaders/ColorShader.vsh", "game/RenderSystem/Shaders/ColorShader.fsh");
	shaderArray->push_back(shader);
}

RenderSystem::~RenderSystem()
{
	delete shaderArray->at(0);
	delete shaderArray;
}

void RenderSystem::render(VertexBuffer *vertexBuffer)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(1);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glUniform4f(0, 1.0, 0.0, 0.0, 1.0);

	vertexBuffer->configureVertexAttributes(0);
	vertexBuffer->renderVertexBuffer();

	glfwSwapBuffers(_window);
	glfwPollEvents();
}

RenderSystem& RenderSystem::getRenderSystem()
{
	static RenderSystem *renderSystem = NULL;

	if (renderSystem == NULL )
	{
		renderSystem = new RenderSystem();

		glClearColor(0.65,0.65,1,1);

		glMatrixMode(GL_PROJECTION);
		gluPerspective(75.0, 800.0/600.0, 1, 1000);
		glViewport(0.0, 0.0, 800.0, 600.0);
		glMatrixMode(GL_MODELVIEW);

		std::cout << "RenderSystem created" << std::endl;
	}

	return *renderSystem;
}

void RenderSystem::destroyRenderSystem()
{
	RenderSystem *renderSystem = &getRenderSystem();
	delete renderSystem;

	std::cout << "RenderSystem destroyed" << std::endl;
}

