#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>

bool *keyStates = new bool [256];

const int width = 800;
const int height = 600;

int myRoom, myCube;

bool angleSwitchDir = false;

// fog variables
float density = 0.047;
float fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};

// angle of rotation
float angle = 0.0f;

// diffuse light color variables
float dlr = 1.0f;
float dlg = 1.0f;
float dlb = 1.0f;

// ambient light color variables
float alr = 0.5f;
float alg = 0.5f;
float alb = 0.5f;

// light position variables
float lx = 0.0f;
float ly = 0.0f;
float lz = 1.0f;
float lw = 0.0f;

void drawCube(int &list, float size);
void drawCube(int &list, float size, float r, float g, float b, float r2, float g2, float b2);
void init();
void display();
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void handleKeyboard();
void update();
void idle();
void reshape(int w, int h);

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GLUT Tutorial 13");

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();
	glutMainLoop();

	return 0;
}

void drawCube(int &list, float size) {
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glBegin(GL_QUADS);

	// front
	glVertex3f(size/2, size/2, -size/2);
	glVertex3f(size/2, -size/2, -size/2);
	glVertex3f(-size/2, -size/2, -size/2);
	glVertex3f(-size/2, size/2, -size/2);

	// back
	glVertex3f(size/2, size/2, size/2);
	glVertex3f(size/2, -size/2, size/2);
	glVertex3f(-size/2, -size/2, size/2);
	glVertex3f(-size/2, size/2, size/2);

	// left
	glVertex3f(-size/2, size/2, size/2);
	glVertex3f(-size/2, -size/2, size/2);
	glVertex3f(-size/2, -size/2, -size/2);
	glVertex3f(-size/2, size/2, -size/2);

	// right
	glVertex3f(size/2, size/2, -size/2);
	glVertex3f(size/2, -size/2, -size/2);
	glVertex3f(size/2, -size/2, size/2);
	glVertex3f(size/2, size/2, size/2);

	// top
	glVertex3f(size/2, size/2, size/2);
	glVertex3f(size/2, size/2, -size/2);
	glVertex3f(-size/2, size/2, -size/2);
	glVertex3f(-size/2, size/2, size/2);

	// bottom
	glVertex3f(size/2, -size/2, size/2);
	glVertex3f(size/2, -size/2, -size/2);
	glVertex3f(-size/2, -size/2, -size/2);
	glVertex3f(-size/2, -size/2, size/2);
		
	glEnd();
	glEndList();
}

void drawCube(int &list, float size, float r, float g, float b, float r2, float g2, float b2) {
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glBegin(GL_QUADS);

	// front
	glVertex3f(size/2, size/2, -size/2);
	glVertex3f(size/2, -size/2, -size/2);
	glVertex3f(-size/2, -size/2, -size/2);
	glVertex3f(-size/2, size/2, -size/2);

	// back
	glVertex3f(size/2, size/2, size/2);
	glVertex3f(size/2, -size/2, size/2);
	glVertex3f(-size/2, -size/2, size/2);
	glVertex3f(-size/2, size/2, size/2);

	// left
	glVertex3f(-size/2, size/2, size/2);
	glVertex3f(-size/2, -size/2, size/2);
	glVertex3f(-size/2, -size/2, -size/2);
	glVertex3f(-size/2, size/2, -size/2);

	// right
	glVertex3f(size/2, size/2, -size/2);
	glVertex3f(size/2, -size/2, -size/2);
	glVertex3f(size/2, -size/2, size/2);
	glVertex3f(size/2, size/2, size/2);

	// top
	glColor3f(r, g, b);
	glVertex3f(size/2, size/2, size/2);
	glVertex3f(size/2, size/2, -size/2);
	glVertex3f(-size/2, size/2, -size/2);
	glVertex3f(-size/2, size/2, size/2);

	// bottom
	glColor3f(r2, g2, b2);
	glVertex3f(size/2, -size/2, size/2);
	glVertex3f(size/2, -size/2, -size/2);
	glVertex3f(-size/2, -size/2, -size/2);
	glVertex3f(-size/2, -size/2, size/2);
		
	glEnd();
	glEndList();
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);

	drawCube(myRoom, 10.0f, 0.0f, 0.0f, 0.6f, 0.2f, 0.4f, 0.6f);
	drawCube(myCube, 2.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
}

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLfloat DiffuseLight[] = {dlr, dlg, dlb};
	GLfloat AmbientLight[] = {alr, alg, alb};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);

	GLfloat LightPosition[] = {lx, ly, lz, lw};
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	gluLookAt(0.0f, 1.0f, -10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glColor3f(0.0f, 0.5f, 0.3f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 2.0f, 0.0f);
	glCallList(myCube);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.0f, 0.0f);
	glScalef(3.0f, 1.0f, 3.0f);
	glTranslatef(0.0f, (float)(10.0/2+0.000001), 0.0f);
	glCallList(myRoom);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2f, 0.6f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(50.0f, 0.0f, -50.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glVertex3f(-50.0f, 0.0f, 50.0f);
	glVertex3f(-50.0f, 0.0f, -50.0f);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void handleKeyboard() {
	if(keyStates[27]) {
		exit(0);
	}
}

void update() {
	if(angleSwitchDir) angle += 1.0f;
	else angle -= 1.0f;

	if(angle > 360.0f) angleSwitchDir = false;
	else if(angle < 0.0f) angleSwitchDir = true;

	handleKeyboard();
}

void idle() {
	update();
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(60.0f, (float)(w/h),
			0.1f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
}
