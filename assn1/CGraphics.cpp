#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::M_Initialize(CEngine * P)
{
	this->V_PEngine = P;
	this->V_Camera_p1 = Vec2d(-20, -20);
	this->V_Camera_p2 = Vec2d(80, 80);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello OpenGL");
	glClearColor(1, 1, 1, 1); //background white
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void CGraphics::M_CallbackDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glColor4ub(0, 0, 0, 205);
	this->M_DrawPolygon(Vec2d(25,25), 50, 3, 0.25*PI);
	this->M_DrawPolygon(Vec2d(25, 75), 50, 4, 0);
	//this->M_DrawPolygon(Vec2d(75, 25), 25, 5, 0.5*PI);
	//this->M_DrawPolygon(Vec2d(75, 75), 25, 100, 0);

	glColor4ub(255, 0, 0 , 205);
	this->M_DrawLine(Vec2d(0, 50), Vec2d(100, 50));
	this->M_DrawLine(Vec2d(50, 0), Vec2d(50, 100));

	glutSwapBuffers();
}

void CGraphics::M_CallbackReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	gluOrtho2D(V_Camera_p1[0], V_Camera_p2[0], V_Camera_p1[1], V_Camera_p2[1]);
}

void CGraphics::M_CallbackIdle()
{

	glutPostRedisplay();
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


void CGraphics::M_ChangeCamera(Vec2d p1, Vec2d p2)
{
	cout << "changecam" << endl;
	this->V_Camera_p1 = p1;
	this->V_Camera_p2 = p2;

}