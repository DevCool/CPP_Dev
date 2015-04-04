#ifndef COBJLOADER_H
#define COBJLOADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

typedef struct COORDINATE {
	float x, y, z;
	COORDINATE(float a, float b, float c);
} coordinate;

typedef struct FACE {
	int faceNum;
	bool hasFour;
	int faces[4];
	int texcoord[4];
	int mat;
	FACE(int facenum, int f1, int f2, int f3);
	FACE(int facenum, int f1, int f2, int f3, int f4);
	FACE(int facenum, int f1, int f2, int f3, int t1, int t2, int t3, int m);
	FACE(int facenum, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m);
} face;

typedef struct MATERIAL {
  string name;
	float alpha, ns, ni;
	float dif[3], amb[3], spec[3];
	int illum;
	int texture;
	MATERIAL(const char *na, float al, float Ns, float Ni, float *a, float *d, float *s, int i, int t);
} material;

typedef struct TEXCOORD {
	float u, v;
	TEXCOORD(float a, float b);
} texcoord;

class CObjLoader {

private:
	vector<string*> coords;
	vector<coordinate*> verts;
	vector<face*> faces;
	vector<coordinate*> normals;
	vector<unsigned int> texture;
	vector<unsigned int> lists;
	vector<material*> materials;
	vector<texcoord*> texcoords;
	bool ismaterial, isnormals, istexture;
	
	unsigned int LoadTexture(const char *directory, const char *filename);
	void Cleanup(void);
	
public:
	CObjLoader(void);
	~CObjLoader(void);
	
	int LoadObject(const char *directory, const char *filename);
	void Destroy(void);

};

#endif
