#include <windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glut.h>

using namespace std;

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
	glFlush(); // send all output to display
	inStream.close();
}

void drawTiling(void) {
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	for (int i=0; i < 10; i++)
		for (int j=0; j<10; j++)
		{
			glMatrixMode(GL_PROJECTION); // set up the syst coordinate
			glLoadIdentity();
			if ((i+j)%2 == 0)
				gluOrtho2D(0, 640, 0, 440);
			else 
				gluOrtho2D(0, 640, 440, 0);
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
	myInit();
	glutMainLoop();
}
