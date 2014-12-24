#include <cstdio>
#include <cstdlib>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#elifdef __LINUX__
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

//Menu IDs
/*
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4
#define SWITCH_OFF 5
*/
// Misc Variables
//float red=0.0f,green=0.0f,blue=0.0f;
//bool colorMode=false;

// Camera Variables
float angleX=0.0f;//,angleY=0.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f,z=0.0f;

// KeyState Variables
float deltaAngleX=0.0f;//,deltaAngleY=0.0f;
float deltaMove=0.0f;
int xOrigin=-1;

//void processMenuEvents(int option);
void pressKey(int key,int xx,int yy);
void releaseKey(int key,int x,int y);
void computePos(float pos);
//void computeDir(float dir);
void mouseButton(int button,int state,int x,int y);
void mouseMove(int x,int y);
void updateMovement(void);
void updateScene(void);
void drawSnowman(void);
//int createGLUTMenus(void);
void display(void);
void reshape(int w,int h);
void keyboard(unsigned char key,int x,int y);
//void specialKeys(int key,int x,int y);

int main(int argc,char** args)
{
	// Create window and init GLUT
	glutInit(&argc,args);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("GLUT Tutorial");

	// Register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	//int menuRes=createGLUTMenus();

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// Enter GLUT mainloop
	glutMainLoop();
	//glutDestroyMenu(menuRes);
	
	return 1;
}

void reshape(int w,int h)
{
	if(h==0) h=1;
	if(w==0) w=1;
	float ratio=1.0*w/h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove)
{
	x+=deltaMove*lx*0.1f;
	z+=deltaMove*lz*0.1f;
}

/*
void computeDir(float deltaAngle)
{
	angle+=deltaAngle;
	lx=sin(angle);
	lz=-cos(angle);
}
*/

void mouseButton(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_UP)
		{
			angleX+=deltaAngleX;
			xOrigin=-1;
		}
		else
			xOrigin=x;
	}
}

void mouseMove(int x,int y)
{
	if(xOrigin>=0)
	{
		deltaAngleX=(x-xOrigin)*0.001f;
		lx=sin(angleX+deltaAngleX);
		lz=-cos(angleX+deltaAngleX);
	}
}

void updateMovement(void)
{
	if (deltaMove)
		computePos(deltaMove);
}

void updateScene(void)
{
	// Update the displayed scene here
}


/*
int createGLUTMenus()
{
	int menu1;
	menu1=glutCreateMenu(processMenuEvents);

	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Green",GREEN);
	glutAddMenuEntry("Orange",ORANGE);
	glutAddMenuEntry("Off",SWITCH_OFF);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	return menu1;
}

void processMenuEvents(int option)
{
	switch(option)
	{
		case RED:
			red=1.0f;
			green=0.0f;
			blue=0.0f;
			colorMode=true;
		break;
		case GREEN:
			red=0.0f;
			green=1.0f;
			blue=0.0f;
			colorMode=true;
		break;
		case BLUE:
			red=0.0f;
			green=0.0f;
			blue=1.0f;
			colorMode=true;
		break;
		case ORANGE:
			red=1.0f;
			green=0.5f;
			blue=0.5f;
			colorMode=true;
		break;
		case SWITCH_OFF:
			colorMode=false;
		break;
	}
}
*/


void display(void)
{
	glClearColor(0.2,0.5,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x,1.0f,z,x+lx,1.0f,z+lz,0.0f,1.0f,0.0f);

	// Draw ground
	glColor3f(0.75f,0.75f,0.75f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f,0.0f,-100.0f);
		glVertex3f(-100.0f,0.0f,100.0f);
		glVertex3f(100.0f,0.0f,100.0f);
		glVertex3f(100.0f,0.0f,-100.0f);
	glEnd();

	// Draw 36 SnowMen
	for(int i=-3; i<3; i++) {
		for(int j=-3; j<3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j*10.0);
			drawSnowman();
			glPopMatrix();
		}
	}

	updateMovement();
	updateScene();

//	if(colorMode)
//		glColorMask(red,green,blue,1.0f);
//	else
//		glColorMask(1.0f,1.0f,1.0f,1.0f);

	glutSwapBuffers();
}

void keyboard(unsigned char key,int x,int y)
{
	if(key==27)
		exit(0);
}

/*
void specialKeys(int key,int x,int y)
{
	float fraction = 0.1f;

	switch(key)
	{
		case GLUT_KEY_UP:
			x+=lx*fraction;
			z+=lz*fraction;
		break;
		case GLUT_KEY_DOWN:
			x-=lx*fraction;
			z-=lz*fraction;
		break;
	}
}
*/

void pressKey(int key,int xx,int yy)
{
	switch(key)
	{
		//case GLUT_KEY_LEFT: deltaAngle=-0.01f; break;
		//case GLUT_KEY_RIGHT: deltaAngle=0.01f; break;
		case GLUT_KEY_UP: deltaMove=0.5f; break;
		case GLUT_KEY_DOWN: deltaMove=-0.5f; break;
	}
}

void releaseKey(int key,int x,int y)
{
	switch(key)
	{
		//case GLUT_KEY_LEFT:
		//case GLUT_KEY_RIGHT: deltaAngle=0.0f; break;
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN: deltaMove=0.0f; break;
	}
}

void drawSnowman(void)
{
	glColor3f(0.95f,0.95f,0.95f);

	// Draw Body
	glTranslatef(0.0f,0.75f,0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f,1.0f,0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f,0.10f,0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f,0.0f,0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f,0.5f,0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}
