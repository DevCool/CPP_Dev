#include "Application.hpp"

namespace
{
  Application *obj = NULL;
}

Application::Application(void)
{
  // Constructor
  obj = this;
  _window = NULL;
}

Application::~Application(void)
{
  // Destructor cleanup and free more resources
  // on destruction of class
  cleanup();
}

bool Application::init(void)
{
  bool success = GL_TRUE;
  
  // Create window and init GLFW/GLEW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  
  _window = glfwCreateWindow(WIDTH, HEIGHT,
			    "OpenGL 3.3+ Playground",
			    NULL, NULL);
  if (_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    success = false;
  }
  
  glfwMakeContextCurrent(_window);
  glfwSetKeyCallback(_window, keyCallback);
  
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    success = false;
  }
  
  glViewport(0, 0, WIDTH, HEIGHT);
  
  return success;
}

int Application::start(void)
{
  bool result = init();
  if (result == GL_FALSE) {
    std::cout << "Application failed to start!" << std::endl;
    return -1;
  }
  
  while (!glfwWindowShouldClose(_window)) {
    glfwPollEvents();
    
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glfwSwapBuffers(_window);
  }
  
  return 0;
}

void Application::cleanup(void)
{
  // Cleanup() function
  // Cleans up objects and frees resources
  std::cout << "Application destroyed!" << std::endl;
  glfwTerminate();
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  obj->key_callback(window, key, scancode, action, mode);
}
