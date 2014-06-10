#include "ResourceManager.h"
#include "TriangleVertices.h"

std::vector<ShaderInterface *>* ResourceManager::getShaderArray()
{
	return _shaderArray;
}

std::vector<VertexBuffer *>* ResourceManager::getVertexBufferArray()
{
	return _vertexBufferArray;
}

ResourceManager::ResourceManager()
{
	_shaderArray = new std::vector<ShaderInterface *>();
	ShaderInterface *shader = new ShaderInterface("ColorShader.vsh", "ColorShader.fsh");
	_shaderArray->push_back(shader);

	_vertexBufferArray = new std::vector<VertexBuffer *>();
	VertexBuffer *vertexBuffer = new VertexBuffer(vertices, sizeof(vertices), GL_TRIANGLES, 3, sizeof(GLfloat)*3, _shaderArray->at(0));
	_vertexBufferArray->push_back(vertexBuffer);
}

ResourceManager::~ResourceManager()
{

	for (std::vector<ShaderInterface *>::iterator iterator = _shaderArray->begin(); iterator != _shaderArray->end(); iterator++) {
		delete *iterator;
	}

	delete _shaderArray;

	for (std::vector<VertexBuffer *>::iterator iterator = _vertexBufferArray->begin(); iterator != _vertexBufferArray->end(); iterator++) {
		delete *iterator;
	}

	delete _vertexBufferArray;
}

ResourceManager& ResourceManager::getResourceManager()
{
	static ResourceManager *resourceManager = NULL;

	if (resourceManager == NULL) {
		resourceManager = new ResourceManager();

		std::cout << "ResourceManager created" << std::endl;
	}

	return *resourceManager;
}

void ResourceManager::destroyResourceManager()
{
	ResourceManager *resourceManager = &getResourceManager();
	delete resourceManager;

	std::cout << "ResourceManager destroyed" << std::endl;
}

