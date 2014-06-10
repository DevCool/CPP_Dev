#include "VertexBuffer.h"

GLuint VertexBuffer::getVertexBufferID()
{
	return _vertexBufferID;
}

VertexBuffer::VertexBuffer(const GLvoid *data, GLsizeiptr size, GLenum mode, GLsizei count, GLsizei stride): _mode(mode), _count(count), _stride(stride)
{
	glGenBuffers(1, &_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &_vertexBufferID);
	_vertexBufferID = 0;
}

void VertexBuffer::configureVertexAttributes(GLint vertexPosition)
{
	if (vertexPosition != -1)
	{
		glEnableVertexAttribArray(vertexPosition);
		glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, _stride, NULL);
	}
}

void VertexBuffer::renderVertexBuffer()
{
	glDrawArrays(_mode, 0, _count);
}

