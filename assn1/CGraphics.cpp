#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::RenderGame(void)
{
	//render map
	double gsize = V_PEngine->V_Grid_Size;
	auto s = V_PEngine->V_Map.size;
	for (int i = 0; i < s[0]; i++)
	{
		for (int j = 0; j < s[1]; j++)
		{
			if (V_PEngine->V_Map[T2Int(i, j)] == 1)
			{
				T2Double cen = T2Double(i, j)*gsize;
				M_DrawPolygon(cen.convert_gl(), gsize * sqrt(2) / 2, 4, DTR(45), T4Int(125, 30, 255, 255));
			}
		}
	}

	//render player
	for (auto x : V_PEngine->V_Objects)
	{
		auto d = x->M_GetDrawData();
		M_DrawPolygon(d.pos.convert_gl(), d.size, 5, d.rotate, d.color);
	}
	auto d = V_PEngine->V_Player->M_GetDrawData();
	M_DrawPolygon(d.pos.convert_gl(), d.size, 3, d.rotate, d.color);
}

void CGraphics::RenderUI(void)
{
	//glViewport(0, 0, 200, 40);
	glutCreateSubWindow(1, 10, 10, 100, 100);
}


void CGraphics::M_Initialize(CEngine * P)
{
	count = 0;
	fps = 0.0;
	old = GetTickCount();

	V_PEngine = P;
	V_Camera_Pos = T2Double(0, 0);
	V_Camera_Height = 80;
	V_Camera_Speed.set(0.0, 0.0);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1080, 1080);

	glEnable(GL_MULTISAMPLE);

	int id = glutCreateWindow("Hello OpenGL");
	cout << id << endl;
	glClearColor(1, 1, 1, 1); //background white
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void CGraphics::M_MoveCamera(void)
{
	auto elapse = GetTickCount() - old;
	old = GetTickCount();

	double q = std::min((1.0 / (0.001*elapse)), 1000.0);
	
	fps = fps * 0.9 + q *0.1;
	count += 0.01;

	auto p = V_PEngine->V_Player->M_GetPosition();
	auto c = V_Camera_Pos;
	
	V_Camera_Height = 80;

	auto a = p - c;
	a = V_Math->M_2TV_Normalize(a);
	auto d = V_Math->M_2TV_Angle(p, c);
	a *=  + d[1];
	a *= 0.001;

	V_Camera_Speed += a;
	V_Camera_Speed *= 0.9;
	
	V_Camera_Pos += V_Camera_Speed;

}
void CGraphics::M_CallbackDisplay()
{
	M_MoveCamera();
	glLoadIdentity();
	gluOrtho2D(V_Camera_Pos[0] - V_Camera_Height, V_Camera_Pos[0] + V_Camera_Height,
		V_Camera_Pos[1] - V_Camera_Height, V_Camera_Pos[1] + V_Camera_Height);

	glClear(GL_COLOR_BUFFER_BIT);

	M_DrawPolygon(Vec2d(25,25), 50, 3, 0.25*PI, T4Int(0, 0, 0, 205));
	M_DrawPolygon(Vec2d(25, 75), 50, 4, 0, T4Int(0, 0, 0, 205));
	M_DrawStar(Vec2d(70, 30), 20, 0, T4Int(0, 0, 0, 205));

	M_DrawLine(Vec2d(0, 50), Vec2d(100, 50), T4Int(255, 0, 0, 255));
	M_DrawLine(Vec2d(50, 0), Vec2d(50, 100), T4Int(255, 0, 0, 255));

	ostringstream s;
	s << fps;
	M_DrawFont(Vec2d(40, 76), s.str(), T4Int(0, 255, 0, 105));

	RenderGame();
	//RenderUI();

	glutSwapBuffers();
}

void CGraphics::M_CallbackReshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void CGraphics::M_CallbackIdle()
{
	
	glutPostRedisplay();
}

void CGraphics::M_DrawLine(Vec2d p1, Vec2d p2, T4Int rgba)
{
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glBegin(GL_LINES);
	glVertex2d(p1[0], p1[1]);
	glVertex2d(p2[0], p2[1]);
	glEnd();
}


void CGraphics::M_DrawStar(Vec2d p, double r, double rotate, T4Int rgba)
{
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 10; i++) {
		double theta = (2.0 * PI * double(i) / double(10)) + (rotate);
		double x, y;
		if (i % 2 != 0) {
			x = r * cosl(theta);
			y = r * sinl(theta);
		}
		else {
			x = r * 0.5 * cosl(theta);
			y = r * 0.5 * sinl(theta);
		}
		glVertex2d(p[0] + x, p[1] + y);
	}
	glEnd();
}


void CGraphics::M_DrawPolygon(Vec2d p, double r, int bump, double rotate, T4Int rgba)
{
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < bump; i++) {
		double theta = (2.0 * PI * double(i) / double(bump)) + (rotate);
		double x = r * cosl(theta);
		double y = r * sinl(theta);
		glVertex2d(p[0] + x, p[1] + y);
	}
	glEnd();
}


void CGraphics::M_DrawFont(Vec2d p, string str, T4Int rgba)
{
	//CAUTION : Font size does not get influenced by screen size
	//Font position is world coordinate
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glRasterPos2d(p[0], p[1]);
	for (int i=0; i < str.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str.at(i));
	}
}
