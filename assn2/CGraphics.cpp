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
	V_CrazyParam += 0.05;

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
				auto p = cen.convert_gl();
				M_DrawPolygon(p, "square", gsize / 2, 0, T4Int(125, 30, 255, 255));
			}
		}
	}

	auto am1 = glm::rotate(glm::mat4(1.0), (float)(cos(anim) * 0.2 * PI), glm::vec3(0.0, 0.0, 1.0));
	auto am2 = glm::rotate(glm::mat4(1.0), (float)(sin(anim) * 0.2 * PI), glm::vec3(0.0, 0.0, 1.0));

	V_Hiers["player"]->M_RegisterTrans2(1, am1);
	V_Hiers["player"]->M_RegisterTrans2(2, am2);

	V_Hiers["enemy"]->M_RegisterTrans2(1, am2);
	V_Hiers["enemy"]->M_RegisterTrans2(2, am1);

	//render objects
	for (auto x : V_PEngine->V_Objects)
	{
		auto d = x->M_GetDrawData();
		
		if (3 <= d.img && d.img <= 7 ) //item
		{
			M_DrawItem(d.pos.convert_gl(), d.size, d.img - 3);
		}
		else if(d.img == 1)
		{
			M_DrawHier(d.pos.convert_gl(), "enemy", d.size * 0.8,  d.rotate, d.color);
		}
		else
		{
			M_DrawPolygon(d.pos.convert_gl(), "square", d.size, d.rotate, d.color);
		}
		
	}
	//render player

	auto d = V_PEngine->V_Player->M_GetDrawData();

	if (V_PEngine->V_Animation_Temp > 0)
	{
		am1 = glm::rotate(glm::mat4(1.0), (float)(0.5 * PI *(V_PEngine->V_Animation_Temp) / 30), glm::vec3(0.0, 0.0, 1.0));
		am2 = glm::rotate(glm::mat4(1.0), (float)(0.5 * PI *(V_PEngine->V_Animation_Temp) / 30), glm::vec3(0.0, 0.0, 1.0));
	}

	V_Hiers["player"]->M_RegisterTrans2(1, am1);
	V_Hiers["player"]->M_RegisterTrans2(2, am2);
	
	M_DrawHier(d.pos.convert_gl(), "player", d.size * 1.0, d.rotate, d.color);
}

void CGraphics::M_RenderUI(void)
{

	
	if (V_PEngine->V_GameEnd == 1)
	{
		M_DrawNumber(Vec3d(V_Screen_Size[0] / 2 - 150, V_Screen_Size[1] / 2, 0), 100, V_PEngine->V_PEnemies.size(), T4Int(255, 0, 0, 255));
		M_DrawPolygon(Vec3d(V_Screen_Size[0] / 2, V_Screen_Size[1] / 2, 0), "square", 250, 0, T4Int(240, 240, 240, 200));
	}
	if (V_PEngine->V_GameEnd == 2)
	{
		M_DrawNumber(Vec3d(V_Screen_Size[0] / 2 - 150, V_Screen_Size[1] / 2, 0), 100, V_PEngine->V_LeftTime, T4Int(125, 255, 0, 255));
		M_DrawPolygon(Vec3d(V_Screen_Size[0] / 2, V_Screen_Size[1] / 2, 0), "square", 250, 0, T4Int(240, 240, 240, 200));
	}
	

	M_DrawNumber(Vec3d(100, 100, 0), 10, V_PEngine->V_PEnemies.size(), T4Int(255,0,0,255));
	M_DrawNumber(Vec3d(100, 150, 0), 10, V_PEngine->V_LeftTime, T4Int(125,255,0,255));
	M_DrawNumber(Vec3d(100, 200, 0), 10, V_PEngine->V_Life, T4Int(255, 255, 0, 255));
	M_DrawPolygon(Vec3d(100, 150, 0), "rectangle", 100, 0, T4Int(180, 240, 240, 100));
	
	
	auto l = V_PEngine->V_Player->M_GetItemList();

	auto n = std::min(4, (int)l.size());
	auto it = l.begin();

	switch (n)
	{
		case 4:
			M_DrawItem(Vec3d(300, V_Screen_Size[1] - 40, 0), 30, *next(it, 3));
		case 3:
			M_DrawItem(Vec3d(230, V_Screen_Size[1] - 40, 0), 30, *next(it, 2));
		case 2:
			M_DrawItem(Vec3d(160, V_Screen_Size[1] - 40, 0), 30, *next(it, 1));
		case 1:
			M_DrawItem(Vec3d(70, V_Screen_Size[1] - 60, 0), 50,*it);
		case 0:
			break;
	}

	M_DrawPolygon(Vec3d(70, V_Screen_Size[1] - 60, 0), "square", 50, 0, T4Int(240, 240, 240, 200));
	M_DrawPolygon(Vec3d(160, V_Screen_Size[1] - 40, 0), "square", 30, 0, T4Int(240, 240, 240, 200));
	M_DrawPolygon(Vec3d(230, V_Screen_Size[1] - 40, 0), "square", 30, 0, T4Int(240, 240, 240, 200));
	M_DrawPolygon(Vec3d(300, V_Screen_Size[1] - 40, 0), "square", 30, 0, T4Int(240, 240, 240, 200));

	


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
	glClearColor(0.8f, 0.8f, 0.8f, 0.5f);
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);

	V_CrazyParam = 0.0;
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
	
	V_Camera_Height = 200 +200 * sin(V_PEngine->V_IS_Camera / 300.0*PI);

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
	static double count = 0;
	count += 0.02;
	M_MoveCamera();

	V_CurrentDrawing = false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	V_SM->M_UseProgram("prg1");
	
	V_CTM = glm::mat4(1.0f);
	V_CTM = glm::translate(V_CTM, glm::vec3(-1.0, -1.0, 0.0));
	V_CTM = glm::scale(V_CTM, glm::vec3(2.0 / V_Screen_Size[0], 2.0 / V_Screen_Size[1], 1));
	M_RenderUI();

	V_CurrentDrawing = true;

	glm::vec3 v(0.0f);
	glm::vec3 up(0, 1, 0);
	if (V_PEngine->V_CrazyMod)
	{
		v[0] = 100 * cos(count);
		v[1] = 100 * sin(count);

		up[1] = cos(DTR(30)*sin(count));
		up[0] = sin(DTR(30)*sin(count));
	}
	V_CTM = glm::mat4(1.0f);
	auto pers = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f);
	auto view = glm::lookAt(glm::vec3(V_Camera_Pos[0], V_Camera_Pos[1], V_Camera_Height) + v,
		glm::vec3(V_Camera_Pos[0], V_Camera_Pos[1], 0), up);
	
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
	V_BasicPolygons["line"]->M_Draw(m, rgba);
}

void CGraphics::M_DrawPolygon(Vec3d p, string name, double r, double rotate, T4Int rgba)
{
	if (V_PEngine->V_CrazyMod && V_CurrentDrawing)
	{
		p[2] += 15 * (sin(p[0]*0.05 + V_CrazyParam) + sin(p[1]*0.05 + V_CrazyParam));
	}

	glm::mat4 m;
	m = V_CTM;
	m = glm::translate(m, glm::vec3(p));
	m = glm::rotate(m, float(rotate), glm::vec3(0.0f,0.0f,1.0f));
	m = glm::scale(m, glm::vec3(r, r, r));
	V_BasicPolygons[name]->M_Draw(m, rgba);
}
void CGraphics::M_DrawHier(Vec3d p, string name, double r, double rotate, T4Int rgba)
{
	if (V_PEngine->V_CrazyMod && V_CurrentDrawing)
	{
		p[2] += 15 * (sin(p[0] * 0.05 + V_CrazyParam) + sin(p[1] * 0.05 + V_CrazyParam));
	}

	glm::mat4 m;
	m = V_CTM;
	m = glm::translate(m, glm::vec3(p));
	m = glm::rotate(m, float(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, glm::vec3(r, r, r));

	T4Double c;
	for (int i = 0; i < 4; i++) c[i] = rgba[i] / 255.0;
	V_Hiers[name]->M_Draw(m, c);
}

void CGraphics::M_DrawFont(Vec2d p, string str, T4Int rgba)
{
}

void CGraphics::M_DrawFontBig(Vec2d p, string str, double scale, T4Int rgba)
{
}

void CGraphics::M_DrawItem(Vec3d p, double r, int z)
{
	if (z == 0) // Mega fire
	{
		for (int i = 0; i < 10; i++)
		{
			M_DrawPolygon(p, "diamond", r*0.5, (2 * PI / 10.0)*i, T4Int(255, 255, 0, 255));
		}
		for (int i = 0; i < 10; i++)
		{
			M_DrawPolygon(p, "diamond", r, (2 * PI / 10.0)*i, T4Int(255, 0, 0, 255));
		}
		
	}
	if (z == 1) // Camera up
	{
		M_DrawPolygon(p, "circle", r*0.4, 0, T4Int(255, 255, 255, 255));
		M_DrawPolygon(p + Vec3d(r*0.7, r*0.5, 0), "circle", r*0.1, 0, T4Int(255, 255, 255, 255));
		M_DrawPolygon(p, "rectangle", r, 0, T4Int(90, 90, 90, 255));

	}
	if (z == 2) // Invincible
	{
		M_DrawPolygon(p, "star", r*0.8, 0, T4Int(255, 255, 0, 255));
		M_DrawPolygon(p, "star", r, 0, T4Int(255, 204, 0, 255));
		
	}
	if (z == 3) // Speed up
	{
		for (int i = 0; i < 3; i++)
		{
			M_DrawPolygon(p+Vec3d(r*0.1,0,0), "diamond", r, PI/12 + (PI/12)*i, T4Int(255, 255, 255, 255));
			M_DrawPolygon(p-Vec3d(r*0.1,0,0), "diamond", r, PI - (PI / 12 + (PI / 12)*i), T4Int(255, 255, 255, 255));
		}
	}
	if (z == 4) // SuperFire
	{
		for (int i = 0; i < 4; i++)
		{
			M_DrawPolygon(p, "diamond", r, (2*PI/4.0)*i, T4Int(30, 30, 30, 255));
		}
	}
}

void CGraphics::M_DrawNumber(Vec3d p, double r, int num, T4Int rgba)
{
	string str = to_string(num);
	Vec3d i = Vec3d(0, 0, 0);
	for (auto c : str)
	{
		int k = c - '0';

		if (k == 0 || k == 2 || k == 3 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9)
		{
			M_DrawPolygon(p+i, "A", r, 0.0, rgba);
		}

		if (k == 0 || k == 1 || k == 2 || k == 3 || k == 4 || k == 7 || k == 8 || k == 9)
		{
			M_DrawPolygon(p+i, "B", r, 0.0, rgba);
		}

		if (k == 0 || k == 1 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9)
		{
			M_DrawPolygon(p+i, "C", r, 0.0, rgba);
		}

		if (k == 0 || k == 2 || k == 3 || k == 5 || k == 6 || k == 8 || k == 9)
		{
			M_DrawPolygon(p+i, "D", r, 0.0, rgba);
		}

		if (k == 0 || k == 2 || k == 6 || k == 8)
		{
			M_DrawPolygon(p+i, "E", r, 0.0, rgba);
		}

		if (k == 0 || k == 4 || k == 5 || k == 6 || k == 8 || k == 9)
		{
			M_DrawPolygon(p+i, "F", r, 0.0, rgba);
		}
		if (k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 8 || k == 9)
		{
			M_DrawPolygon(p+i, "G", r, 0.0, rgba);
		}

		i += Vec3d(r*1.5, 0, 0);
	}
}