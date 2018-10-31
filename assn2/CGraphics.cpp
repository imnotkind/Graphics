#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::M_RenderGame(void)
{
	static double anim = 0.0;
	anim += 0.05;
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
				M_DrawPolygon(cen.convert_gl(), "triangle", gsize * sqrt(2) / 2, 0, T4Int(125, 30, 255, 255));
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
			M_DrawPolygon(d.pos.convert_gl(), "polygon", d.size,  d.rotate, d.color);
		}
		
	}
	//render player

	auto am1 = glm::rotate(glm::mat4(1.0), (float)(cos(anim) * 0.2 * PI), glm::vec3(0.0, 0.0, 1.0));
	auto am2 = glm::rotate(glm::mat4(1.0), (float)(sin(anim) * 0.2 * PI), glm::vec3(0.0, 0.0, 1.0));

	auto d = V_PEngine->V_Player->M_GetDrawData();

	V_Hiers["player"]->M_RegisterTrans2(1, am1);
	V_Hiers["player"]->M_RegisterTrans2(2, am2);
	M_DrawHier(d.pos.convert_gl(), "player", d.size * 1.0, d.rotate, d.color);
}

void CGraphics::M_RenderUI(void)
{
	/*
	ostringstream s;
	s << "Enemies : " << V_PEngine->V_PEnemies.size();
	M_DrawFont(Vec2d(100, 100), s.str(), T4Int(0, 0, 0, 255));

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
		glColor4ub(200, 200, 200, 200);
		glRectd(0,0,V_Screen_Size[0], V_Screen_Size[1]);

		Vec2d p = Vec2d(V_Screen_Size[0] / 2 - 400, V_Screen_Size[1] / 2.0);
		M_DrawFontBig(p, "Game Over!", 1, T4Int(255, 0, 0, 255));
		p[0] += 300;
		p[1] -= 200;
		M_DrawFont(p, "Press R to restart", T4Int(0, 0, 0, 255));
	}
	if (V_PEngine->V_GameEnd == 2)
	{
		glColor4ub(200, 200, 200, 200);
		glRectd(0, 0, V_Screen_Size[0], V_Screen_Size[1]);

		Vec2d p = Vec2d(V_Screen_Size[0] / 2 - 400, V_Screen_Size[1] / 2.0);
		M_DrawFontBig(p, "Game Clear!", 1, T4Int(255, 0, 0, 255));
		p[0] += 300;
		p[1] -= 200;
		M_DrawFont(p, "Press R to restart", T4Int(0, 0, 0, 255));
	}
	*/


}


void CGraphics::M_Initialize(CEngine * P)
{

	V_PEngine = P;
	V_Screen_Size = T2Double(1080, 1080);
	V_Camera_Pos = T2Double(0, 0);
	V_Camera_Speed.set(0.0, 0.0);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1080, 1080);

	int id = glutCreateWindow("Graphics Assn1");
	cout << id << endl;

	glClearColor(1, 1, 1, 1); //background white
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
}

void CGraphics::M_Initialize2(void)
{
	glEnable(GL_DEPTH_TEST);
	V_SM = CShaderManager::getInstance();

	M_SetupHieraModels();

	
}

void CGraphics::M_MoveCamera(void)
{
	auto p = V_PEngine->V_Player->M_GetPosition();
	auto c = V_Camera_Pos;
	
	V_Camera_Height = 250 + 150 * sin(V_PEngine->V_IS_Camera / 600.0*PI);

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
	M_MoveCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	V_SM->M_UseProgram("prg1");
	
	V_CTM = glm::mat4(1.0f);
	V_CTM = glm::translate(V_CTM, glm::vec3(-1.0, -1.0, 0.0));
	V_CTM = glm::scale(V_CTM, glm::vec3(2.0 / V_Screen_Size[0], 2.0 / V_Screen_Size[1], 1)); 
	// screen coord -> cvc
	M_RenderUI();


	V_CTM = glm::mat4(1.0f);
	auto pers = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 300.0f);
	auto view = glm::lookAt(glm::vec3(V_Camera_Pos[0], V_Camera_Pos[1], V_Camera_Height),
		glm::vec3(V_Camera_Pos[0], V_Camera_Pos[1], 0), glm::vec3(0, 1, 0));

	V_CTM = pers * view;
	M_RenderGame();
	

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

void CGraphics::M_DrawLine(Vec3d p1, Vec3d p2, T4Int rgba)
{
	glm::mat4 m;
	m = V_CTM;
	m = glm::translate(V_CTM, glm::vec3(p1));
	m = glm::scale(V_CTM, glm::vec3(p2 - p1));
	V_BasicPolygons["line"]->M_Draw(m);
}

void CGraphics::M_DrawPolygon(Vec3d p, string name, double r, double rotate, T4Int rgba)
{
	glm::mat4 m;
	m = V_CTM;
	m = glm::translate(m, glm::vec3(p));
	m = glm::rotate(m, float(rotate), glm::vec3(0.0f,0.0f,1.0f));
	m = glm::scale(m, glm::vec3(r, r, r));

	V_BasicPolygons[name]->M_Draw(m);
}
void CGraphics::M_DrawHier(Vec3d p, string name, double r, double rotate, T4Int rgba)
{
	glm::mat4 m;
	m = V_CTM;
	m = glm::translate(m, glm::vec3(p));
	m = glm::rotate(m, float(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, glm::vec3(r, r, r));

	V_Hiers[name]->M_Draw(m);
}

void CGraphics::M_DrawFont(Vec2d p, string str, T4Int rgba)
{
	return;
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
	return;
	//CAUTION : Font size DOES get influenced by screen size
	//Font position is world coordinate (most recent gluortho2D)
	glColor4ub(rgba[0], rgba[1], rgba[2], rgba[3]);
	glLineWidth(4);
	glPushMatrix();
	glTranslated(p[0], p[1], 0);
	glScaled(scale, scale, 0);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)str.c_str());
	glPopMatrix();
	glLineWidth(1);
}

void CGraphics::M_DrawItem(Vec2d p, double r, int z)
{
}

