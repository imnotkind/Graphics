#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::M_Initialize()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello OpenGL");
	glClearColor(1, 1, 1, 1);
	glShadeModel(GL_FLAT);
}

void CGraphics::M_CallbackDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(0, 0, 0);
	this->M_DrawPolygon(Vec2d(25,25), 25, 3, 0.5*PI);
	this->M_DrawPolygon(Vec2d(25, 75), 25, 4, 1.25*PI);
	this->M_DrawPolygon(Vec2d(75, 25), 25, 5, 0.5*PI);
	this->M_DrawPolygon(Vec2d(75, 75), 25, 100, 0);

	glColor3ub(255, 0, 0);
	
	this->M_DrawLine(Vec2d(0, 50), Vec2d(100, 50));
	this->M_DrawLine(Vec2d(50, 0), Vec2d(50, 100));

	glutSwapBuffers();
}

void CGraphics::M_CallbackReshape(int w, int h)
{
	cout << "reshape" << endl;

	glViewport(0, 0, w, h);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}


//every shape is based on square block unit : (x : left coord of block, y : bottom coord of block, size : length of square block's edge)



void CGraphics::M_DrawStar(Vec2d p, double size)
{
	double r = size * 0.52;
	//this->M_DrawPolygon(x + size / 2.0, y + size / 2.4, r, 5, 0.5);
}

void CGraphics::M_DrawLine(Vec2d p1, Vec2d p2)
{
	glBegin(GL_LINES);
	glVertex2d(p1[0], p1[1]);
	glVertex2d(p2[0], p2[1]);
	glEnd();
}


void CGraphics::M_DrawPolygon(Vec2d p, double r, int bump, double rotate)
{

	glBegin(GL_POLYGON);
	for (int i = 0; i < bump; i++) {
		double theta = (2.0 * PI * double(i) / double(bump)) + (rotate);
		double x = r * cosl(theta);
		double y = r * sinl(theta);
		glVertex2d(p[0] + x, p[1] + y);
	}
	glEnd();
}

