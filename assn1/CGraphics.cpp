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
	this->M_DrawPolygon(Vec2d(25, 75), 25, 4, 0);
	this->M_DrawPolygon(Vec2d(75, 25), 25, 5, 0.5*PI);
	this->M_DrawPolygon(Vec2d(75, 75), 25, 100, 0);

	glColor3ub(255, 0, 0);
	
	this->M_DrawLine(Vec2d(0, 50), Vec2d(100, 50));
	this->M_DrawLine(Vec2d(50, 0), Vec2d(50, 100));

	glutSwapBuffers();
}

void CGraphics::M_CallbackReshape(int w, int h)
{

	glViewport(0, 0, w, h);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}


void CGraphics::M_DrawLine(Vec2d p1, Vec2d p2)
{
	glBegin(GL_LINES);
	glVertex2d(p1[0], p1[1]);
	glVertex2d(p2[0], p2[1]);
	glEnd();
}


void CGraphics::M_DrawStar(Vec2d p, double size)
{
	//TODO
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


void CGraphics::M_DrawFont(Vec2d p, const char *string)
{
	const char *c;
	glRasterPos2d(p[0], p[1]);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}
