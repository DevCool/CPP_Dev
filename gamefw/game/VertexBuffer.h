#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexBuffer
{
private:

	GLuint _vertexBufferID;

	GLenum _mode;
	GLsizei _count;
	GLsizei _stride;

public:

	GLuint getVertexBufferID();

	VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride);
	~VertexBuffer();

	void configureVertexAttributes(GLint vertexPosition);
	void renderVertexBuffer();
};

#endif

