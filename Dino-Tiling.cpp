#include <windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glut.h>

using namespace std;

double rotAngle = 10;

void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 'a':
	rotAngle += 5;			// increase rotation by 5 degrees
	break;
    case 'l':
	rotAngle -= 5;			// decrease rotation by 5 degrees
	break;
    case 'q':
	exit(0);			// exit
    }

    glutPostRedisplay();		// redraw the image now
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
	glColor3f(0.0f, 0.0f, 0.0f); // set the drawing color
	glPointSize(4.0); // a 'dot' is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION); // set up the system coordinate
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	glViewport(0, 0, 640, 480);
}

void drawPolyLine(void) {
	fstream inStream;
	inStream.open("dino.dat", ios::in);
	if (inStream.fail())
		return;
	//glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	GLint numPolys, numLines, x, y;
	inStream >> numPolys;
	for (int j = 0; j < numPolys; j++)
	{
		inStream >> numLines;
		glBegin(GL_LINE_STRIP);
		for (int i=0; i< numLines; i++)
		{
			inStream >> x >> y;
			glVertex2i(x, y); 
		}
		glEnd();
	}
	glRotated(rotAngle, 0, 1, 0);
	glFlush(); // send all output to display
	inStream.close();
}

void drawTiling(void) {
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	for (int i=0; i < 10; i++)
		for (int j=0; j<10; j++)
		{
			glViewport(i*64, j*44, 64, 44);
			drawPolyLine();
		}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("my dinosaurus");
	glutDisplayFunc(drawTiling);
	glutKeyboardFunc(keyboard);
	myInit();
	glutMainLoop();
}
