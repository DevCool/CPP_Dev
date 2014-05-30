#ifndef SHADERINTERFACE_H
#define SHADERINTERFACE_H

#include <iostream>
#include "ShaderLoader.h"

class ShaderInterface
{
private:

	ShaderLoader *shader;

	GLint _aPositionVertex;
	GLint _uColor;

	char *_vertexShaderString;
	char *_fragmentShaderString;

	char *loadTextFromFile(const char *file);

public:

	GLuint getProgramHandle();
	GLint get_aPositionVertex();
	GLint get_uColor();

	ShaderInterface(const char *VS, const char *FS);
	~ShaderInterface();

};

#endif

