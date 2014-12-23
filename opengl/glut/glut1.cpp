#include <cstdio>
#include <cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#elifdef __LINUX__
#include <GL/freeglut.h>
#else
#include <GL/glut.h>
#endif

float angle1=0.0,angle2=0.0,angle3=360.0;
int red=1,green=1,blue=1;

void update(void) {

	if(red<255)
		red++;
	else if(red>0)
		red--;

	if(green<255)
		green++;
	else if(green>0)
		green--;

	if(blue<250)
		blue++;
	else if(blue>0)
		blue--;

	if(angle1>=0.0) angle1++;
	else if(angle1<=360.0) angle1--;

	if(angle2>=0.0) angle2++;
	else if(angle2<=360.0) angle2--;

	if(angle3>=0.0) angle3++;
	else if(angle3<=360.0) angle3--;

}

void renderScene( void ) {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	gluLookAt(	0.0,0.0,10.0,
			0.0,0.0,0.0,
			0.0,1.0,0.0 );

	glPushMatrix();
	glTranslatef(-1.5,0.0,0.0);
	glRotatef(angle1, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
		glColor3i(red,green,blue);
		glVertex3f( -1.0, -1.0, 0.0 );
		glColor3i(red,green,blue);
		glVertex3f( 1.0, 0.0, 0.0 );
		glColor3i(red,green,blue);
		glVertex3f( 0.0, 1.0, 0.0 );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5,0.0,0.0);
	glRotatef(angle1, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f( -1.0, -1.0, 0.0 );
		glColor3f(0.0,1.0,0.0);
		glVertex3f( 1.0, 0.0, 0.0 );
		glColor3f(0.0,0.0,1.0);
		glVertex3f( 0.0, 1.0, 0.0 );
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,1.5,0.0);
	glRotatef(angle1, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f( -1.0, -1.0, 0.0 );
		glColor3f(0.0,1.0,0.0);
		glVertex3f( 1.0, 0.0, 0.0 );
		glColor3f(0.0,0.0,1.0);
		glVertex3f( 0.0, 1.0, 0.0 );
	glEnd();
	glPopMatrix();

	update();

	glutSwapBuffers();

}

void changeSize( int w, int h ) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0*w/h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

}

void keyboardHandler(unsigned char key, int x, int y) {
	if(key==27)
		exit(0);
}

int main( int argc, char **argv ) {

	// init GLUT and create window
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 800, 600 );
	glutCreateWindow( "GLUT Tutorial #1" );

	// register callbacks
	glutDisplayFunc( renderScene );
	glutIdleFunc( renderScene );
	glutReshapeFunc( changeSize );
	glutKeyboardFunc( keyboardHandler );

	// enter GLUT event processing cycle
	glutMainLoop();

	return true;

}
