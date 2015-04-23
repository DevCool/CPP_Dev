#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>

void init();
void display();

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("First OpenGL Window");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();

	return 0;
}

void init() {
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glFlush();
}
