#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <iostream>
#include <GLFW/glfw3.h>

class ShaderLoader
{
private:

	GLuint _programHandle;

	GLuint compileShader(GLenum shader, const char *source);

public:

	GLuint getProgramHandle();

	ShaderLoader(const char *sourceVS, const char *sourceFS);
	~ShaderLoader();
};

#endif

