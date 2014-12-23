#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

int main () {

	// Initialize GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x antialiasing
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 ); // I want OpenGL 3.3
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	// Make MacOS happy
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	// Want newer OpenGL
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	// Open a window and create its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow( 1024, 768, "Tutorial - Opening Window", NULL, NULL );
	if( window == NULL )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have\nan Intel GPU, they are not 3.3 compatible." );
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent( window ); // Initialize GLEW
	glewExperimental = true; // Needed in core profile

	if( glewInit() != GLEW_OK )
	{
		fprintf( stderr, "Failed to initialize GLEW\n" );
		return -1;
	}

	// Ensure I capture the escape key being pressed
	glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

	do {
		// TODO: Draw code here

		// Swap Buffers
		glfwSwapBuffers( window );
		glfwPollEvents();
	} while( glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose( window ) == 0 );

	glfwTerminate();

	return 0;

}

