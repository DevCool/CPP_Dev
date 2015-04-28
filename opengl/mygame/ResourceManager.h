#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>
#include <vector>

#include "ObjLoader.h"

class ResourceManager {

private:
	ResourceManager();
	~ResourceManager();
	
public:
	static ResourceManager& getResourceManager(void);
	static void destroyResourceManager(void);
	
	ObjLoader& getObjLoader(void);
	
private:
	ObjLoader* _objLoader;

};

#endif
