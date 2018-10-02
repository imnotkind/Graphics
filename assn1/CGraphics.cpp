#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::M_RenderGame(void)
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

	//render objects
	for (auto x : V_PEngine->V_Objects)
	{
		auto d = x->M_GetDrawData();
		
		if (3 <= d.img && d.img <= 7 ) //item
		{
			M_DrawItem(d.pos.convert_gl(), d.size, d.img - 3);
		}
		else //bullet, enemy
		{
			M_DrawPolygon(d.pos.convert_gl(), d.size, 5, d.rotate, d.color);
		}
		
	}
	//render player
	auto d = V_PEngine->V_Player->M_GetDrawData();
	M_DrawPolygon(d.pos.convert_gl(), d.size, 3, d.rotate, d.color);
}

void CGraphics::M_RenderUI(void)
{

	ostringstream s;
	s << "Enemies : " << V_PEngine->V_PEnemies.size();
	M_DrawFont(Vec2d(100, 100), s.str(), T4Int(0, 0, 0, 255));

	/*
	s.str("");
	s << "FPS of Engine : " << V_PEngine->fps;
	M_DrawFont(Vec2d(100, 180), s.str(), T4Int(0, 0, 0, 255));

	s.str("");
	s << "FPS of Graphic : " << this->fps;
	M_DrawFont(Vec2d(100, 230), s.str(), T4Int(0, 0, 0, 255));
	*/



	M_DrawPolygon(Vec2d(70, V_Screen_Size[1] - 60), 100 / sqrt(2), 4, DTR(45), T4Int(200,200,200,200));
	M_DrawPolygon(Vec2d(160, V_Screen_Size[1] - 40), 60 / sqrt(2), 4, DTR(45), T4Int(200, 200, 200, 200));
	M_DrawPolygon(Vec2d(230, V_Screen_Size[1] - 40), 60 / sqrt(2), 4, DTR(45), T4Int(200, 200, 200, 200));
	M_DrawPolygon(Vec2d(300, V_Screen_Size[1] - 40), 60 / sqrt(2), 4, DTR(45), T4Int(200, 200, 200, 200));

	auto l = V_PEngine->V_Player->M_GetItemList();


	
	auto n = std::min(4, (int)l.size());
	auto it = l.begin();

	switch (n)
	{
		case 4:
			M_DrawItem(Vec2d(300, V_Screen_Size[1] - 40), 60 / 2, *next(it, 3));
		case 3:
			M_DrawItem(Vec2d(230, V_Screen_Size[1] - 40), 60 / 2, *next(it, 2));
		case 2:
			M_DrawItem(Vec2d(160, V_Screen_Size[1] - 40), 60 / 2, *next(it, 1));
		case 1:
			M_DrawItem(Vec2d(70, V_Screen_Size[1] - 60), 100 / 2,*it);
		case 0:
			break;
	}

	if (V_PEngine->V_GameEnd == 1)
	{
		Vec2d p = Vec2d(0, V_Screen_Size[1] / 2.0);
		M_DrawFontBig(p, "Game Over!", 1, T4Int(255, 0, 0, 255));
		p[1] -= 200;
		M_DrawFont(p, "Press any button to restart", T4Int(0, 0, 0, 255));
	}
	if (V_PEngine->V_GameEnd == 2)
	{
		Vec2d p = Vec2d(0, V_Screen_Size[1] / 2.0);
		M_DrawFontBig(p, "Game Clear!", 1, T4Int(255, 0, 0, 255));
		p[1] -= 200;
		M_DrawFont(p, "Press any button to restart", T4Int(0, 0, 0, 255));
	}


}


void CGraphics::M_Initialize(CEngine * P)
{
	if (QueryPerformanceFrequency(&freq))
	{
		cout << freq.QuadPart << endl;
		if (!QueryPerformanceCounter(&old_count))
		{
			cout << "counter fail" << endl;
			exit(2);
		}
	}
	else
	{
		cout << "counter fail" << endl;
		exit(1);
	}
	

	V_PEngine = P;
	V_Screen_Size = T2Double(1080, 1080);
	V_Camera_Pos = T2Double(0, 0);
	V_Camera_Size = 80;
	V_Camera_Size_Acc = 0;
	V_Camera_Speed.set(0.0, 0.0);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1080, 1080);

	int id = glutCreateWindow("Graphics Assn1");
	cout << id << endl;
	glClearColor(1, 1, 1, 1); //background white
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
}

void CGraphics::M_MoveCamera(void)
{


	auto p = V_PEngine->V_Player->M_GetPosition();
	auto c = V_Camera_Pos;
	
	
	if (V_PEngine->V_IS_Camera > 0)
	{
		double u = V_PEngine->V_IS_Camera / 600.0 * 2 * PI;
		V_Camera_Size_Acc = 0.5 * pow(-sin(u), 1);
	}
	else
	{
		V_Camera_Size = 80;
	}

	V_Camera_Size += V_Camera_Size_Acc;

	if (V_Camera_Size < 80)
	{
		V_Camera_Size = 80;
		V_Camera_Size_Acc = 0;
	}
	if (V_Camera_Size > 130)
	{
		V_Camera_Size = 130;
	}

	auto a = p - c;
	a = V_Math->M_2TV_Normalize(a);
	auto d = V_Math->M_2TV_Angle(p, c);
	a *=  d[1];
	a *= 0.003;

	V_Camera_Speed += a;
	V_Camera_Speed *= 0.9;
	
	V_Camera_Pos += V_Camera_Speed;

}
void CGraphics::M_CallbackDisplay()
{
	/*
	if (QueryPerformanceCounter(&new_count)) {
		auto elapse_micro = (new_count.QuadPart - old_count.QuadPart) / (freq.QuadPart / 1000000.0);
		old_count = new_count;
		fps = 1000000.0 / (elapse_micro);
	}
	else {
		cout << "counter fail" << endl;
	}
	*/

	
	

	glClear(GL_COLOR_BUFFER_BIT);

	M_MoveCamera();
	glLoadIdentity();
	gluOrtho2D(V_Camera_Pos[0] - V_Camera_Size, V_Camera_Pos[0] + V_Camera_Size,
		V_Camera_Pos[1] - V_Camera_Size, V_Camera_Pos[1] + V_Camera_Size);

	M_RenderGame();

	glLoadIdentity();
	gluOrtho2D(0,V_Screen_Size[0],0,V_Screen_Size[1]);
	M_RenderUI();

	glutSwapBuffers();
}

void CGraphics::M_CallbackReshape(int w, int h)
{
	V_Screen_Size[0] = w;
	V_Screen_Size[1] = h;
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
	//CAUTION : Font size does NOT get influenced by screen size
	//Font position is world coordinate (most recent gluortho2D)
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glRasterPos2d(p[0], p[1]);
	for (int i=0; i < str.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str.at(i));
	}
}

void CGraphics::M_DrawFontBig(Vec2d p, string str, double scale, T4Int rgba)
{
	//CAUTION : Font size DOES get influenced by screen size
	//Font position is world coordinate (most recent gluortho2D)
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glLineWidth(60);
	glPushMatrix();
	glTranslated(p[0], p[1], 0);
	glScaled(scale, scale, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)str.c_str());
	glPopMatrix();
	glLineWidth(1);
}



void CGraphics::M_DrawItem(Vec2d p, double r, int z)
{
	if (z == 0) // Mega fire
	{
		double c = r / (sqrt(650)); //most far point : (30,-10)
		glColor4ub(255, 0, 0, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] - 25 * c, p[1] + 5 * c);
		glVertex2d(p[0] - 5 * c, p[1] + 25 * c);
		glVertex2d(p[0] + 25 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 25 * c);
		glEnd();

		c = c * 0.5;
		glColor4ub(255, 255, 0, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] - 25 * c, p[1] + 5 * c);
		glVertex2d(p[0] - 5 * c, p[1] + 25 * c);
		glVertex2d(p[0] + 25 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 25 * c);
		glEnd();
	}
	if (z == 1) // Camera up
	{
		double c = r / (25); //most far point : (20,15)

		glColor4ub(40, 40, 40, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] - 20 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 20 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 20 * c, p[1] + 15 * c);
		glVertex2d(p[0] - 20 * c, p[1] + 15 * c);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2d(p[0] + 6 * c, p[1] + 18 * c);
		glVertex2d(p[0] + 16 * c, p[1] + 18 * c);
		glVertex2d(p[0] + 16 * c, p[1] + 15 * c);
		glVertex2d(p[0] + 6 * c, p[1] + 15 * c);
		glEnd();

		M_DrawPolygon(p, r * 0.35, 100, 0, T4Int(255, 255, 255, 255));
	}
	if (z == 2) // Invincible
	{
		M_DrawStar(p, r, DTR(54), T4Int(255, 204, 0, 255));
		M_DrawStar(p, r * 0.8, DTR(54), T4Int(255, 255, 0, 255));
	}
	if (z == 3) // Speed up
	{
		double c = r / (20 * sqrt(13)); //most far point : (40,60)

		glColor4ub(150, 75, 0, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] - 15 * c, p[1] - 5 * c);
		glVertex2d(p[0] - 40 * c, p[1] + 20 * c);
		glVertex2d(p[0], p[1] + 60 * c);
		glVertex2d(p[0] + 50 * c, p[1] + 10 * c);
		glVertex2d(p[0] - 20 * c, p[1] - 60 * c);
		glVertex2d(p[0] - 40 * c, p[1] - 60 * c);
		glVertex2d(p[0] - 45 * c, p[1] - 50 * c);
		glVertex2d(p[0] - 40 * c, p[1] - 20 * c);
		glEnd();
		
		glColor4ub(240, 248, 255, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] + 10 * c, p[1]);
		glVertex2d(p[0] + 10 * c, p[1] + 30 * c);
		glVertex2d(p[0] + 40 * c, p[1] + 60 * c);
		glVertex2d(p[0] + 40 * c, p[1] + 30 * c);
		glEnd();
		
	}
	if (z == 4) // Super fire
	{
		double c = r / (sqrt(650)); //most far point : (30,-10)
		glColor4ub(100, 100, 100, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] - 25 * c, p[1] + 5 * c);
		glVertex2d(p[0] - 5 * c, p[1] + 25 * c);
		glVertex2d(p[0] + 25 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 25 * c);
		glEnd();

		c = c * 0.5;
		glColor4ub(230, 230, 230, 255);
		glBegin(GL_POLYGON);
		glVertex2d(p[0] - 25 * c, p[1] + 5 * c);
		glVertex2d(p[0] - 5 * c, p[1] + 25 * c);
		glVertex2d(p[0] + 25 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 5 * c);
		glVertex2d(p[0] + 15 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 15 * c);
		glVertex2d(p[0] + 5 * c, p[1] - 25 * c);
		glEnd();
	}
	
}

