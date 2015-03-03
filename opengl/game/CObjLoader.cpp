#include "CObjLoader.h"

VERTEX::VERTEX(float a, float b, float c) {
	x = a;
	y = b;
	z = c;
}

FACE::FACE(int facenum, int f1, int f2, int f3) {
	faceNum = facenum;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	hasFour = false;
}

FACE::FACE(int facenum, int f1, int f2, int f3, int f4) {
	faceNum = facenum;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	hasFour = true;
}

// ====================================================================================
// [                                 Start of Class                                   ]
// ====================================================================================

CObjLoader::CObjLoader(void) {
}

CObjLoader::~CObjLoader(void) {
}

int CObjLoader::LoadObject(const char *filename) {
	ifstream in(filename);
	if(!in.is_open()) {
		cout << "Cannot open " << filename << endl;
		return -1;
	}
	
	char buf[256];
	while(!in.eof()) {
		in.getline(buf, 256);
		coords.push_back(new string(buf));
	}
	
	for(unsigned int i = 0; i < coords.size(); i++) {
		if((*coords[i])[0] == '#')
			continue;
		else if(((*coords[i])[0] == 'v') && ((*coords[i])[1] == ' ')) {
			float tmpx, tmpy, tmpz;
			sscanf(coords[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			verts.push_back(new vert(tmpx, tmpy, tmpz));
		}
		else if(((*coords[i])[0] == 'v') && ((*coords[i])[1] == 'n')) {
			float tmpx, tmpy, tmpz;
			sscanf(coords[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normals.push_back(new vert(tmpx, tmpy, tmpz));
		}
		else if((*coords[i])[0] == 'f') {
			int a, b, c, d, e;
			if(count(coords[i]->begin(), coords[i]->end(), ' ') == 3) {
				sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d", &b, &a, &c, &a, &d, &a);
				faces.push_back(new face(a, b, c, d));
			}
			else if(count(coords[i]->begin(), coords[i]->end(), ' ') == 4) {
				sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &b, &a, &c, &a, &d, &a, &e, &a);
				faces.push_back(new face(a, b, c, d, e));
			}
		}
	}
	
	int num;
	num = glGenLists(1);
	
	glNewList(num, GL_COMPILE);
		for(unsigned int i = 0; i < faces.size(); i++) {
			if(faces[i]->hasFour) {
				glBegin(GL_QUADS);
				glNormal3f(normals[faces[i]->faceNum-1]->x, normals[faces[i]->faceNum-1]->y, normals[faces[i]->faceNum-1]->z);
				glVertex3f(verts[faces[i]->faces[0]-1]->x, verts[faces[i]->faces[0]-1]->y, verts[faces[i]->faces[0]-1]->z);
				glVertex3f(verts[faces[i]->faces[1]-1]->x, verts[faces[i]->faces[1]-1]->y, verts[faces[i]->faces[1]-1]->z);
				glVertex3f(verts[faces[i]->faces[2]-1]->x, verts[faces[i]->faces[2]-1]->y, verts[faces[i]->faces[2]-1]->z);
				glVertex3f(verts[faces[i]->faces[3]-1]->x, verts[faces[i]->faces[3]-1]->y, verts[faces[i]->faces[3]-1]->z);
				glEnd();
			}
			else {
				glNormal3f(normals[faces[i]->faceNum-1]->x, normals[faces[i]->faceNum-1]->y, normals[faces[i]->faceNum-1]->z);
				glVertex3f(verts[faces[i]->faces[0]-1]->x, verts[faces[i]->faces[0]-1]->y, verts[faces[i]->faces[0]-1]->z);
				glVertex3f(verts[faces[i]->faces[1]-1]->x, verts[faces[i]->faces[1]-1]->y, verts[faces[i]->faces[1]-1]->z);
				glVertex3f(verts[faces[i]->faces[2]-1]->x, verts[faces[i]->faces[2]-1]->y, verts[faces[i]->faces[2]-1]->z);
			}
		}
	glEndList();
	
	Cleanup();

	return num;
}

void CObjLoader::Cleanup(void) {
	for(unsigned int i = 0; i < verts.size(); i++)
		delete verts[i];
	
	for(unsigned int i = 0; i < normals.size(); i++)
		delete normals[i];
	
	for(unsigned int i = 0; i < faces.size(); i++)
		delete faces[i];
	
	for(unsigned int i = 0; i < coords.size(); i++)
		delete coords[i];
	
	verts.clear();
	normals.clear();
	faces.clear();
	coords.clear();
}
