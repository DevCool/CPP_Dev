#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderInterface.h"

class VertexBuffer
{
private:

	GLuint _vertexBufferID;

	GLenum _mode;
	GLsizei _count;
	GLsizei _stride;

	ShaderInterface *_shader;

public:

	GLuint getVertexBufferID();
	ShaderInterface *getShader();

	VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride, ShaderInterface *shader);
	~VertexBuffer();

	void configureVertexAttributes();
	void renderVertexBuffer();
};

#endif

