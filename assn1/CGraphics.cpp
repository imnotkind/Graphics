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
	this->M_DrawPolygon(25, 25, 25, 3, 0.5*PI);
	this->M_DrawPolygon(25, 75, 25, 4, 1.25*PI);
	this->M_DrawPolygon(75, 25, 25, 5, 0.5*PI);
	this->M_DrawPolygon(75, 75, 25, 100, 0);

	glColor3ub(255, 0, 0);
	this->M_DrawLine(0, 50, 100, 50);
	this->M_DrawLine(50, 0, 50, 100);
	this->M_DrawLine(0, 0, 0, 100);
	this->M_DrawLine(0, 0, 100, 0);
	this->M_DrawLine(100, 0, 100, 100);
	this->M_DrawLine(0, 100, 100, 100);

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



void CGraphics::M_DrawStar(double x, double y, double size)
{
	double r = size * 0.52;
	this->M_DrawPolygon(x + size / 2.0, y + size / 2.4, r, 5, 0.5);
}

void CGraphics::M_DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glEnd();
}


void CGraphics::M_DrawPolygon(double cx, double cy, double r, int bump, double rotate)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < bump; i++) {
		double theta = (2.0 * PI * double(i) / double(bump)) + (rotate);
		double x = r * cosl(theta);
		double y = r * sinl(theta);
		glVertex2d(cx + x, cy + y);
	}
	glEnd();
}

