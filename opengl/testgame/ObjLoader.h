#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>

using namespace std;

struct coordinate
{
	float x, y, z;
	coordinate(float a, float b, float c) : x(a), y(b), z(c) { };
};

struct face
{
	int facenum;
	bool four;
	int faces[4];

	face(int facen, int f1, int f2, int f3) : facenum(facen) {
		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;
		four = false;
	}
	
	face(int facen, int f1, int f2, int f3, int f4) : facenum(facen) {
		faces[0] = f1;
		faces[1] = f2;
		faces[2] = f3;
		faces[3] = f4;
		four = true;
	}
};

class ObjLoader
{
	private:
		vector<string*> coords;
		vector<coordinate*> vertices;
		vector<face*> faces;
		vector<coordinate*> normals;

		ObjLoader();
		~ObjLoader();

		void cleanup();

	public:
		int loadObject(const char* filename);

		static ObjLoader& getObjectLoader();
		static void destroyObjectLoader();
};

#endif
