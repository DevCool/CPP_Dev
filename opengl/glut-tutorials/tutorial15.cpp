#include <cstdio>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/glu.h>

float angle = 0.0f;
float density = 0.2f;
float fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f};
bool tester = false;

void cube(void) {
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(2);
}

void init(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glFogf(GL_FOG_START, 5);
	glFogf(GL_FOG_END, 20);
	glHint(GL_FOG_HINT, GL_NICEST);
}

void update(void) {
	if((angle <= 360.0f) && (!tester)) {
		angle += (2.0f * 0.5f);
	}
	else if((angle >= 0.0f) && (tester)) {
		angle -= (2.0f * 0.5f);
	}

	if((angle >= 360.0) && (!tester)) { tester = true; }
	else if((angle <= 0.0) && (tester)) { tester = false; }
}	

void display(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	gluLookAt(0.0f, 0.0f, -15.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	cube();
	glPopMatrix();

	glutSwapBuffers();
	update();
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	gluPerspective(60.0f, (GLfloat)(w/h),
		0.05f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	if(key == 'a') {
		glFogi(GL_FOG_MODE, GL_EXP);
	}
	if(key == 's') {
		glFogi(GL_FOG_MODE, GL_EXP2);
	}
	if(key == 'd') {
		glFogi(GL_FOG_MODE, GL_LINEAR);
	}
	if(key == 27) {
		exit(0);
	}
}

int main(int argc, char *args[]) {
	glutInit(&argc, args);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Tutorial 15 - Different Fog Types [ by ThePlague ]");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

