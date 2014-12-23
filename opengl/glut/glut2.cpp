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

// Camera Variables
float angle=0.0;
float lx=0.0f,lz=-1.0f;
float x=0.0f,z=0.0f;

void pressKey(int key,int xx,int yy);
void releaseKey(int key,int x,int y);
void computePos(float pos);
void computeDir(float dir);
void updateMovement(void);
void updateScene(void);
void drawSnowman(void);
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

	// Register Handler Functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// Enter GLUT mainloop
	glutMainLoop();
	
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

void computeDir(float deltaAngle)
{
	angle+=deltaAngle;
	lx=sin(angle);
	lz=-cos(angle);
}

// KeyState Variables
float deltaAngle = 0.0f;
float deltaMove = 0.0f;

void updateMovement(void)
{
	if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);
}

void updateScene(void)
{
	// Update the displayed scene here
}

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
		case GLUT_KEY_LEFT:
			angle-=0.01f;
			lx=sin(angle);
			lz=-cos(angle);
		break;
		case GLUT_KEY_RIGHT:
			angle+=0.01f;
			lx=sin(angle);
			lz=-cos(angle);
		break;
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
		case GLUT_KEY_LEFT: deltaAngle=-0.01f; break;
		case GLUT_KEY_RIGHT: deltaAngle=0.01f; break;
		case GLUT_KEY_UP: deltaMove=0.5f; break;
		case GLUT_KEY_DOWN: deltaMove=-0.5f; break;
	}
}

void releaseKey(int key,int x,int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT: deltaAngle=0.0f; break;
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
