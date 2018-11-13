#include <Windows.h>
#include <fstream>
#include <gl/GL.h>
#include <gl/glut.h>
#include <math.h>



using namespace std;
#define PI 3.14159

void myInit(void)
{
	glClearColor (1.0,1.0,1.0,0.0);
	glColor3f (0.0,0.0,0.0);
	glPointSize (4.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-2000.0,3000.0,-1000.0,3000.0);
	//glViewport(0,0,640,480);
}


void GambarDino (void)
{
	//using std::fstream;
	fstream inStream;
	inStream.open("dino.dat",ios::in);
	if (inStream.fail()) //jika tidak bisa membaca
		return;
	//glClear(GL_COLOR_BUFFER_BIT);
	GLint numPolys,numLines,x,y;
	inStream >> numPolys;
	for (int j=0;j<numPolys;j++)
	{
		inStream>>numLines;
		glBegin (GL_LINE_STRIP);
		for (int i=0;i<numLines;i++)
		{
			inStream >>x>>y;
			glVertex2i (x,y);
		}
		glEnd();
	}
	glFlush();
	inStream.close();


}


void Gambar()
{
	double result;
	float sudut;
	double transy;
	double transx;
	float nilai;
	glClear(GL_COLOR_BUFFER_BIT);
	
	transx=0;
	transy=1280;
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glTranslated (transx,transy,0.0);

	
	for (int i=0;i<360;i+=20)
	{
		transx=1280*sin(i*PI/180);
		transy=1280*cos(i*PI/180);

		
		printf ("\n");
		printf ("%d\n",transx);
		printf ("%d\n",transy);
		
	
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		
	      	
		glTranslated (transx,transy,0.0);
		glRotated(360-i,0.0,0.0,1.0);
	
		GambarDino();
		glPopMatrix();
	}
	
}

int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (480,480);
	glutInitWindowPosition (100,150);
	glutCreateWindow ("Menggambar Dinosaurus");
	glutDisplayFunc(Gambar);
	myInit();
	glutMainLoop();
	
   return 0;	
}
