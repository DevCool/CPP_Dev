#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>

const int width = 800;
const int height = 600;

bool *keyStates = new bool [256];

void init();
void handleKeyboard();
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void display();
void reshape(int w, int h);

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("First OpenGL Window");

	init();

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyUp);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0, (GLfloat)(width/height), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
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

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glFlush();
}

void reshape(int w, int h) {
	// Set viewport to the size of the window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)(w/h), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
