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

FACE::FACE(int facenum, int f1, int f2, int f3, int t1, int t2, int t3, int m) {
	faceNum = facenum;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	tex[0] = t1;
	tex[1] = t2;
	tex[2] = t3;
	hasFour = false;
}

FACE::FACE(int facenum, int f1, int f2, int f3, int f4, int t1, int t2, int t3, int t4, int m) {
	faceNum = facenum;
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
	tex[0] = t1;
	tex[1] = t2;
	tex[2] = t3;
	tex[3] = t4;
	hasFour = true;
}

MATERIAL::MATERIAL(const char *na, float al, float Ns, float Ni, float *a, float *d, float *s, int i, int t) {
	name = na;
	alpha = al;
	ns = Ns;
	ni = Ni;
	
	amb[0] = a[0];
	amb[1] = a[1];
	amb[2] = a[2];
	
	dif[0] = d[0];
	dif[1] = d[1];
	dif[2] = d[2];
	
	spec[0] = s[0];
	spec[1] = s[1];
	spec[2] = s[2];
	
	illum = i;
	texture = t;
}

TEXCOORD::TEXCOORD(float a, float b) {
	u = a;
	v = b;
}

// ====================================================================================
// [                                 Start of Class                                   ]
// ====================================================================================

CObjLoader::CObjLoader(void) {
  ismaterial = isnormals = istexture = false;
}

CObjLoader::~CObjLoader(void) {
	for(vector<unsigned int>::const_iterator it = texture.begin(); it != texture.end(); it++) {
		glDeleteTextures(1, &(*it));
	}
	for(vector<unsigned int>::const_iterator it = lists.begin(); it != lists.end(); it++) {
		glDeleteLists(*it, 1);
	}
}

unsigned int CObjLoader::LoadTexture(const char *filename) {
	unsigned int id;
	SDL_Surface *image;

	image = IMG_Load(filename);

	if (image == NULL) {
		printf("bad image\n");
		Cleanup();
		exit(-1);
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(image);
	texture.push_back(id);
	return id;
}

int CObjLoader::LoadObject(const char *filename) {
	ifstream in(filename);
	if(!in.is_open()) {
		cout << "Cannot open " << filename << endl;
		return -1;
	}
	
	char buf[256];
	int curmat = 0;
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
			if(count(coords[i]->begin(), coords[i]->end(), ' ') == 4) {
				if(coords[i]->find("//") != string::npos)
				{
					sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &b, &a, &c, &a, &d, &a, &e, &a);
					faces.push_back(new face(a, b, c, d, e, 0, 0, 0, 0, curmat));
				}
				else if(coords[i]->find("/") != string::npos)
				{
					int t[4];
					sscanf(coords[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &b, &t[0], &a, &c, &t[1], &a, &d, &t[2], &a, &e, &t[3], &a);
					faces.push_back(new face(a, b, c, d, e, t[0], t[1], t[2], t[3], curmat));
				}
				else {
					sscanf(coords[i]->c_str(), "f %d %d %d %d", &a, &b, &c, &d);
					faces.push_back(new face(-1, a, b, c, d));
				}
			}
			else {
				if(coords[i]->find("//") != string::npos)
				{
					sscanf(coords[i]->c_str(), "f %d//%d %d//%d %d//%d", &b, &a, &c, &a, &d, &a);
					faces.push_back(new face(a, b, c, d, 0, 0, 0, curmat));
				}
				else if(coords[i]->find("/") != string::npos)
				{
					int t[3];
					sscanf(coords[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &b, &t[0], &a, &c, &t[1], &a, &d, &t[2], &a);
					faces.push_back(new face(a, b, c, d, t[0], t[1], t[2], curmat));
				}
				else {
					sscanf(coords[i]->c_str(), "f %d %d %d", &a, &b, &c);
					faces.push_back(new face(-1, a, b, c));
				}
			}
		}
		else if(((*coords[i])[0] == 'u') && ((*coords[i])[1] == 's') && ((*coords[i])[2] == 'e')) {
			char matname[200];
			sscanf(coords[i]->c_str(), "usemtl %s", matname);
			for(unsigned int i = 0; i < materials.size(); i++) {
				if(strcmp(materials[i]->name.c_str(), matname) == 0) {
					curmat = i;
					break;
				}
			}
		}
		else if(((*coords[i])[0] == 'm') && ((*coords[i])[1] == 't') && ((*coords[i])[2] == 'l') && ((*coords[i])[3] == 'l')) {
			char filen[200];
			sscanf(coords[i]->c_str(), "mtllib %s", filen);
			ifstream matlib_in(filen);
			if(!matlib_in.is_open()) {
				cout << "Cannot open file: " << filen << endl;
				Cleanup();
				return -1;
			}
			ismaterial = true;
			vector<string> tmp;
			char buf[200];
			while(!matlib_in.eof()) {
				matlib_in.getline(buf, 200);
				tmp.push_back(buf);
			}
			char name[200];
			char filename[200];
			float amb[3], dif[3], spec[3], alpha, ns, ni;
			int illum;
			unsigned int tex = 0;
			bool ismat = false;
			strcpy(filename, "\0");
			for(unsigned int i = 0; i < tmp.size(); i++) {
				if(tmp[i][0] == '#')
					continue;
				else if((tmp[i][0] == 'n') && (tmp[i][1] == 'e') && (tmp[i][2] == 'w')) {
					ismat=false;
					sscanf(tmp[i].c_str(), "newmtl %s", name);
				}
				else if((tmp[i][0] == 'N') && (tmp[i][1] == 's')) {
					sscanf(tmp[i].c_str(), "Ns %f", &ns);
					ismat = true;
				}
				else if((tmp[i][0] == 'K') && (tmp[i][1] == 'a')) {
					sscanf(tmp[i].c_str(), "Ka %f %f %f", &amb[0], &amb[1], &amb[2]);
					ismat = true;
				}
				else if((tmp[i][0] == 'K') && (tmp[i][1] == 'd')) {
					sscanf(tmp[i].c_str(), "Kd %f %f %f", &dif[0], &dif[1], &dif[2]);
					ismat = true;
				}
				else if((tmp[i][0] == 'K') && (tmp[i][1] == 's')) {
					sscanf(tmp[i].c_str(), "Ks %f %f %f", &spec[0], &spec[1], &spec[2]);
					ismat = true;
				}
				else if((tmp[i][0] == 'N') && (tmp[i][1] == 'i')) {
					sscanf(tmp[i].c_str(), "Ni %f", &ni);
					ismat = true;
				}
				else if((tmp[i][0] == 'd') && (tmp[i][1] == ' ')) {
					sscanf(tmp[i].c_str(), "d %f", &alpha);
					ismat = true;
				}
				else if((tmp[i][0] == 'i') && (tmp[i][1] == 'l')) {
					sscanf(tmp[i].c_str(), "illum %d", &illum);
					ismat = true;
				}
				else if((tmp[i][0] == 'm') && (tmp[i][1] == 'a') && (tmp[i][2] == 'p')) {
					sscanf(tmp[i].c_str(), "map_Kd %s", filename);
					tex = LoadTexture(filename);
					ismat = true;
				}
				if(ismat) {
					if(strcmp(filename, "\0") != 0) {
						materials.push_back(new material(name, alpha, ns, ni, amb, dif, spec, illum, tex));
						strcpy(filename, "\0");
					}
					else {
						materials.push_back(new material(name, alpha, ns, ni, amb, dif, spec, illum, -1));
					}
				}
			}
		}
		else if(((*coords[i])[0] == 'v') && ((*coords[i])[1] == 't')) {
			float u, v;
			sscanf(coords[i]->c_str(), "vt %f %f", &u, &v);
			texcoords.push_back(new texcoord(u, v-1));
			istexture = true;
		}
		if(materials.size() == 0)
			ismaterial = false;
		else
			ismaterial = true;
	}
	
	int num;
	num = glGenLists(1);
	glNewList(num, GL_COMPILE);
		for(unsigned int i = 0; i < faces.size(); i++) {
			int lastmat = -1;
			if((lastmat != faces[i]->mat) && ismaterial) {
				float diffuse[] = {materials[faces[i]->mat]->dif[0], materials[faces[i]->mat]->dif[1], materials[faces[i]->mat]->dif[2], 1.0};
				float ambient[] = {materials[faces[i]->mat]->amb[0], materials[faces[i]->mat]->amb[1], materials[faces[i]->mat]->amb[2], 1.0};
				float specular[] = {materials[faces[i]->mat]->spec[0], materials[faces[i]->mat]->spec[1], materials[faces[i]->mat]->spec[2], 1.0};
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
				glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
				glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
				glMaterialf(GL_FRONT, GL_SHININESS, materials[faces[i]->mat]->ns);
				lastmat = faces[i]->mat;
				if(materials[faces[i]->mat]->texture == -1) {
					glDisable(GL_TEXTURE_2D);
				}
				else {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, materials[faces[i]->mat]->texture);
				}
			}
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
				glBegin(GL_QUADS);
				glNormal3f(normals[faces[i]->faceNum-1]->x, normals[faces[i]->faceNum-1]->y, normals[faces[i]->faceNum-1]->z);
				glVertex3f(verts[faces[i]->faces[0]-1]->x, verts[faces[i]->faces[0]-1]->y, verts[faces[i]->faces[0]-1]->z);
				glVertex3f(verts[faces[i]->faces[1]-1]->x, verts[faces[i]->faces[1]-1]->y, verts[faces[i]->faces[1]-1]->z);
				glVertex3f(verts[faces[i]->faces[2]-1]->x, verts[faces[i]->faces[2]-1]->y, verts[faces[i]->faces[2]-1]->z);
				glEnd();
			}
		}
	glEndList();
	lists.push_back(num);
		
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
	
	for(unsigned int i = 0; i < materials.size(); i++)
		delete materials[i];
	
	for(unsigned int i = 0; i < texcoords.size(); i++)
		delete texcoords[i];
		
	verts.clear();
	normals.clear();
	faces.clear();
	coords.clear();
	materials.clear();
	texcoords.clear();
}

void CObjLoader::Destroy(void) {
	Cleanup();
	delete this;
}
