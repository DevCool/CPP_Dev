#include "GameManager.h"

GLfloat vertices[] =
{
	-0.5, -0.5, 0.0,
	 0.5, -0.5, 0.0,
	 0.0,  0.5, 0.0
};

GameManager::GameManager(bool running): _running(running), _window(glfwGetCurrentContext()), _renderSystem(&RenderSystem::getRenderSystem())
{
	vertexBuffer = new VertexBuffer(vertices, sizeof(vertices), GL_TRIANGLES, 3, sizeof(GLfloat)*3);
}

GameManager::~GameManager()
{
	_renderSystem->destroyRenderSystem();
}

void GameManager::runGameLoop()
{
	while (_running)
	{
		_running = !glfwWindowShouldClose(_window);
		_renderSystem->render(vertexBuffer);
	}
}

GameManager& GameManager::getGameManager()
{
	static GameManager *gameManager = NULL;

	if (gameManager == NULL) {
		glfwInit();

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		GLFWwindow *window = glfwCreateWindow(800, 600, "Simple FPS", NULL, NULL);
		
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();

		gameManager = new GameManager(true);
		std::cout << "GameManager created" << std::endl;
	}

	return *gameManager;
}

void GameManager::destroyGameManager()
{
	GameManager *gameManager = &getGameManager();
	delete gameManager;

	std::cout << "GameManager destroyed" << std::endl;

	GLFWwindow *window = glfwGetCurrentContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}

