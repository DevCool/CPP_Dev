#ifndef COBJLOADER_H
#define COBJLOADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

typedef struct VERTEX {
	float x, y, z;
	VERTEX(float a, float b, float c);
} vert;

typedef struct FACE {
	int faceNum;
	bool hasFour;
	int faces[4];
	
	FACE(int facenum, int f1, int f2, int f3);
	FACE(int facenum, int f1, int f2, int f3, int f4);
} face;

class CObjLoader {

private:
	vector<string*> coords;
	vector<vert*> verts;
	vector<face*> faces;
	vector<vert*> normals;
	
	void Cleanup(void);
	
public:
	CObjLoader(void);
	~CObjLoader(void);
	
	int LoadObject(const char *filename);
	void Destroy(void);

};

#endif
