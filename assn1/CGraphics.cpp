#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::M_Initialize(void)
{
	glClearColor(1, 1, 1, 1);
	glShadeModel(GL_FLAT);
}

void CGraphics::M_RenderGame()
{

	glColor3ub(0, 0, 0);
	this->M_DrawCircle(20, 20, 50);
	this->M_DrawSquare(50, 0, 50);
	this->M_DrawTriangle(0, 0, 50);
	this->M_DrawPentagon(0, 50, 50);

	glColor3ub(255, 0, 0);
	this->M_DrawLine(0, 50, 100, 50);
	this->M_DrawLine(50, 0, 50, 100);
	this->M_DrawLine(0, 0, 0, 100);
	this->M_DrawLine(0, 0, 100, 0);
	this->M_DrawLine(100, 0, 100, 100);
	this->M_DrawLine(0, 100, 100, 100);

}

//every shape is based on square block unit : (x : left coord of block, y : bottom coord of block, size : length of square block's edge)

void CGraphics::M_DrawCircle(double x, double y, double size) //size = 2*r
{
	double r = size / 2.0;
	this->M_DrawPolygon(x + r, y + r, r, 100, 0);
}

void CGraphics::M_DrawTriangle(double x, double y, double size)
{
	double r = size * sqrt(3) / 3.0;
	this->M_DrawPolygon(x + size / 2.0, y + size * sqrt(3) / 6.0, r, 3, 0.5);
}

void CGraphics::M_DrawSquare(double x, double y, double size)
{
	double r = size / 2.0 * sqrt(2);
	this->M_DrawPolygon(x + size / 2.0, y + size / 2.0, r, 4, 1.25);
}

void CGraphics::M_DrawPentagon(double x, double y, double size)
{
	double r = size * 0.52;
	this->M_DrawPolygon(x + size / 2.0, y + size / 2.4, r, 5, 0.5);
}

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



//low level private method for Drawing shapes
void CGraphics::M_DrawPolygon(double cx, double cy, double r, int bump, double rotate)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < bump; i++) {
		double theta = (2.0 * PI * double(i) / double(bump)) + (rotate * PI);
		double x = r * cosl(theta);
		double y = r * sinl(theta);
		glVertex2d(cx + x, cy + y);
	}
	glEnd();
}

