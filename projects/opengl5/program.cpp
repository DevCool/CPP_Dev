#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "program.hpp"

using namespace std;

program::program()
{
	running=false;
	window=NULL;
	angle=0.0;
}

program::~program()
{
}

int program::Start()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "Error: cannot continue, initialization of SDL() failed." << endl;
		return -1;
	}
	window=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);
	SDL_WM_SetCaption("OpenGL Tutorial #5",NULL);
	running=true;
	Init();
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				running=false;
			Keyboard();
		}
		Update();
		Render();
		SDL_GL_SwapBuffers();
		if(1000/30>(SDL_GetTicks()-start))
			SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
	SDL_Quit();
	return 0;
}

void program::Init()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,640.0/480.0,1.0,500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	cube=LoadObject("test.obj");
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float col[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
}

void program::Update()
{
	angle+=0.5;
	if(angle>360)
		angle-=360;
}

void program::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float pos[]={-1.0,1.0,-2.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glTranslatef(0.0,0.0,-5.0);
	glRotatef(angle,1.0,1.0,1.0);
	glCallList(cube);
}

void program::Keyboard()
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					running=false;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

int program::LoadObject(const char* filename)
{
	vector<string*> coord;
	vector<coordinate*> vertex;
	vector<face*> faces;
	vector<coordinate*> normals;
	ifstream in(filename);
	if(!in.is_open())
	{
		cerr << "Not opened" << endl;
		return -1;
	}
	char buf[256];
	while(!in.eof())
	{
		in.getline(buf,256);
		coord.push_back(new string(buf));
	}
	for(unsigned int i=0;i<coord.size();i++)
	{
		if((*coord[i])[0] == '#')
			continue;
		else if((*coord[i])[0]=='v' && (*coord[i])[1]==' ')
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
			vertex.push_back(new coordinate(tmpx,tmpy,tmpz));
		}
		else if((*coord[i])[0]=='v' && (*coord[i])[1]=='n')
		{
			float tmpx,tmpy,tmpz;
			sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
			normals.push_back(new coordinate(tmpx,tmpy,tmpz));
		}
		else if((*coord[i])[0]=='f')
		{
			int a,b,c,d,e;
			if(count(coord[i]->begin(),coord[i]->end(),' ')==4)
			{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
				faces.push_back(new face(b,a,c,d,e));
			}
			else
			{
				sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
				faces.push_back(new face(b,a,c,d));
			}
		}
	}

	//draw
	int num;
	num=glGenLists(1);
	glNewList(num,GL_COMPILE);
	for(unsigned int i=0;i<faces.size();i++)
	{
		if(faces[i]->four)
		{
			glBegin(GL_QUADS);
				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
				glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
				glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
	for(unsigned int i=0;i<coord.size();i++)
		delete coord[i];
	for(unsigned int i=0;i<faces.size();i++)
		delete faces[i];
	for(unsigned int i=0;i<normals.size();i++)
		delete normals[i];
	for(unsigned int i=0;i<vertex.size();i++)
		delete vertex[i];
	return num;
}

