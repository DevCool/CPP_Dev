#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

ObjLoader& ObjLoader::getObjectLoader(void)
{
	static ObjLoader* myLoader = NULL;

	if (myLoader == NULL) {
		myLoader = new ObjLoader();

		cout << "Object Loader Started!" << endl;
	}

	return *myLoader;
}

void ObjLoader::destroyObjectLoader(void)
{
	ObjLoader* myLoader = &getObjectLoader();
	delete myLoader;

	cout << "Object Loader Destroyed!" << endl;
}

int ObjLoader::loadObject(const char* filename)
{
	ifstream in(filename);
	if (!in.is_open()) {
		cout << "Cannot open " << filename << endl;
		return -1;
	}

	char buf[256];
	while(!in.eof()) {
		in.getline(buf, 256);
		coords.push_back(new string(buf));
	}

	for (unsigned int i = 0; i < coords.size(); i++) {
		if ((*coords[i])[0] == '#')
			continue;
		else if (((*coords[i])[0] == 'v') && ((*coords[i])[1] == ' ')) {
			float tmpx, tmpy, tmpz;
			sscanf(coords[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
			vertices.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if (((*coords[i])[0] == 'v') && ((*coords[i])[1] == 'n')) {
			float tmpx, tmpy, tmpz;
			sscanf(coords[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normals.push_back(new coordinate(tmpx, tmpy, tmpz));
		}
		else if ((*coords[i])[0] == 'f') {
			int a, b, c, d, e;
			if (count(coords[i]->begin(), coords[i]->end(), ' ') == 4) {
				sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
				faces.push_back(new face(b, a, c, d, e));
			}
			else {
				sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
				faces.push_back(new face(b, a, c, d));
			}
		}
	}

	int num;
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);
		for (unsigned int i = 0; i < faces.size(); i++) {
			if(faces[i]->four) {
				glBegin(GL_QUADS);
					glNormal3f(normals[faces[i]->facenum-1]->x, normals[faces[i]->facenum-1]->y, normals[faces[i]->facenum-1]->z);
					glVertex3f(vertices[faces[i]->faces[0]-1]->x, vertices[faces[i]->faces[0]-1]->y, vertices[faces[i]->faces[0]-1]->z);
					glVertex3f(vertices[faces[i]->faces[1]-1]->x, vertices[faces[i]->faces[1]-1]->y, vertices[faces[i]->faces[1]-1]->z);
					glVertex3f(vertices[faces[i]->faces[2]-1]->x, vertices[faces[i]->faces[2]-1]->y, vertices[faces[i]->faces[2]-1]->z);
					glVertex3f(vertices[faces[i]->faces[3]-1]->x, vertices[faces[i]->faces[3]-1]->y, vertices[faces[i]->faces[3]-1]->z);
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
					glNormal3f(normals[faces[i]->facenum-1]->x, normals[faces[i]->facenum-1]->y, normals[faces[i]->facenum-1]->z);
					glVertex3f(vertices[faces[i]->faces[0]-1]->x, vertices[faces[i]->faces[0]-1]->y, vertices[faces[i]->faces[0]-1]->z);
					glVertex3f(vertices[faces[i]->faces[1]-1]->x, vertices[faces[i]->faces[1]-1]->y, vertices[faces[i]->faces[1]-1]->z);
					glVertex3f(vertices[faces[i]->faces[2]-1]->x, vertices[faces[i]->faces[2]-1]->y, vertices[faces[i]->faces[2]-1]->z);
				glEnd();
			}
		}
	glEndList();

	cleanup();

	return num;
}

void ObjLoader::cleanup()
{
	for (unsigned int i = 0; i < vertices.size(); i++)
		delete vertices[i];
	for (unsigned int i = 0; i < normals.size(); i++)
		delete normals[i];
	for (unsigned int i = 0; i < faces.size(); i++)
		delete faces[i];
	for (unsigned int i = 0; i < coords.size(); i++)
		delete coords[i];

	vertices.clear();
	normals.clear();
	faces.clear();
	coords.clear();
}
