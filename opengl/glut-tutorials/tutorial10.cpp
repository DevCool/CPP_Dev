#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>

const int width = 800;
const int height = 600;

bool *keyStates = new bool [256];
int myCube, myRoom;

bool movingUp = false;
bool rotateNegitive = false;
float yLocation = 0.0f;
float yRotationAngle = 0.0f;

bool init();
void handleKeyboard();
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void drawCube(int &list, float size);
void display();
void reshape(int w, int h);
void moveCubes();

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("First OpenGL Window");

	bool result = init();

	if(!result) return -1;

	drawCube(myCube, 2.0f);
	drawCube(myRoom, 5.0f);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}

bool init() {
	bool success = true;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, (GLfloat)(width/height), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	if(glGetError() != GL_NO_ERROR) success = false;

	GLuint res = glewInit();
	if(res != GLEW_OK) success = false;

	return success;
}

void handleKeyboard() {
	if(keyStates[27]) exit(0);
}

void keyPress(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void display() {
	handleKeyboard();
	moveCubes();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0f, 1.0f, -10.0f,
		  0.0f, 0.0f, 0.0f,
		  0.0f, 1.0f, 0.0);

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);
	glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, yLocation, 0.0f);
	glCallList(myCube);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.5f);
	glScalef(4.0f, 1.0f, 4.0f);
	glTranslatef(0.0f, 2.51f, 0.0f);
	glCallList(myRoom);
	glPopMatrix();

/*
	glColor3f(1.0f, 0.9f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(50.0f, 0.0f, -50.0f);
	glVertex3f(50.0f, 0.0f, 50.0f);
	glVertex3f(-50.0f, 0.0f, 50.0f);
	glVertex3f(-50.0f, 0.0f, -50.0f);
	glEnd();
 */

	glutSwapBuffers();
}

void reshape(int w, int h) {
	// Set viewport to the size of the window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)(w/h), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void moveCubes() {
	if(movingUp) yLocation -= 0.05f;
	else yLocation += 0.05f;

	if(yLocation <= -3.0f) movingUp = false;
	else if(yLocation >= 3.0f) movingUp = true;

	if(rotateNegitive) yRotationAngle -= 0.5f;
	else yRotationAngle += 0.5f; 

	if(yRotationAngle >= 360.0f) rotateNegitive = true;
	else if(yRotationAngle <= 0.0f) rotateNegitive = false;
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
