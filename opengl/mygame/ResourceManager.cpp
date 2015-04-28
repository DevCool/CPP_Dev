#include "ResourceManager.h"

ResourceManager::ResourceManager() {
	std::cout << "Resource Manager Started!" << std::endl;
	_objLoader = &ObjLoader::getObjectLoader();
}

ResourceManager::~ResourceManager() {
	if (_objLoader != NULL) {
		_objLoader->destroyObjectLoader();
	}
}

ResourceManager& ResourceManager::getResourceManager() {
	static ResourceManager* resManager = NULL;
	
	if (resManager == NULL) {
		resManager = new ResourceManager();
	}
	
	return *resManager;
}

void ResourceManager::destroyResourceManager() {
	ResourceManager* resManager = &getResourceManager();
	delete resManager;
	
	std::cout << "Resource Manager Destroyed!" << std::endl;
}

ObjLoader& ResourceManager::getObjLoader() {
	if (_objLoader != NULL) {
		return *_objLoader;
	}
	else {
		std::cout << "There is no object loader created!" << std::endl;
		return *_objLoader;
	}
}
