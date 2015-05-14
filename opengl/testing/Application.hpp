#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLuint WIDTH = 800, HEIGHT = 600;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

class Application
{
  
private:
  GLFWwindow* _window;
  
public:
  Application();
  ~Application();
  
  bool init(void);
  int start(void);
  void cleanup(void);

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
  
};

#endif
