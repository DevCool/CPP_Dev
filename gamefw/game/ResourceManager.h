#ifndef ResourceManager_h
#define ResourceManager_h

#include <iostream>
#include <vector>

#include "ShaderInterface.h"
#include "VertexBuffer.h"

class ResourceManager
{
private:

	std::vector<ShaderInterface *> *_shaderArray;
	std::vector<VertexBuffer *> *_vertexBufferArray;

	ResourceManager();
	~ResourceManager();

public:

	std::vector<ShaderInterface *>* getShaderArray();
	std::vector<VertexBuffer *>* getVertexBufferArray();

	static ResourceManager& getResourceManager();
	static void destroyResourceManager();

};

#endif

