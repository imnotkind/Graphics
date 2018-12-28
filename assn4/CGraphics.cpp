#include "CGraphics.h"



CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}


void CGraphics::M_RenderUI(void)
{

	
	if (V_PEngine->V_GameEnd == 1)
	{
		M_DrawNumber(Vec3d(V_Screen_Size[0] / 2 - 150, V_Screen_Size[1] / 2, 0), 100, V_PEngine->V_PEnemies.size(), T4Int(255, 0, 0, 255));
		M_DrawModel(Vec3d(V_Screen_Size[0] / 2, V_Screen_Size[1] / 2, 0), "square", 250, 0, T4Int(130, 100, 100, 255));
	}
	if (V_PEngine->V_GameEnd == 2)
	{
		M_DrawNumber(Vec3d(V_Screen_Size[0] / 2 - 150, V_Screen_Size[1] / 2, 0), 100, V_PEngine->V_LeftTime, T4Int(125, 255, 0, 255));
		M_DrawModel(Vec3d(V_Screen_Size[0] / 2, V_Screen_Size[1] / 2, 0), "square", 250, 0, T4Int(100, 130, 100, 255));
	}
	

	M_DrawNumber(Vec3d(50, 100, 0), 10, V_PEngine->V_PEnemies.size(), T4Int(255,0,0,255));
	M_DrawNumber(Vec3d(50, 150, 0), 10, V_PEngine->V_LeftTime, T4Int(125,255,0,255));
	M_DrawNumber(Vec3d(50, 200, 0), 10, V_PEngine->V_Life, T4Int(255, 255, 0, 255));
	M_DrawModel(Vec3d(50, 150, 0), "square", 80, 0, T4Int(100, 100, 100, 200));
	
	
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

	M_DrawModel(Vec3d(70, V_Screen_Size[1] - 60, 0), "square", 50, 0, T4Int(100, 170, 170, 200));
	M_DrawModel(Vec3d(160, V_Screen_Size[1] - 40, 0), "square", 30, 0, T4Int(100, 170, 170, 200));
	M_DrawModel(Vec3d(230, V_Screen_Size[1] - 40, 0), "square", 30, 0, T4Int(100, 170, 170, 200));
	M_DrawModel(Vec3d(300, V_Screen_Size[1] - 40, 0), "square", 30, 0, T4Int(100, 170, 170, 200));



}


int CGraphics::M_Initialize(CEngine * P)
{
	V_PEngine = P;
	V_Screen_Size = T2Double(1080, 1080);
	auto ui = CUserInput::getInstance();
	ui->M_SetWinSize(V_Screen_Size);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1080, 1080);

	int id = glutCreateWindow("Graphics Assn3");
	cout << id << endl;

	glClearColor(1, 1, 1, 1); //background white
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);

	return id;

}

void CGraphics::M_Initialize2(void)
{
	glEnable(GL_DEPTH_TEST);
	V_SM = CShaderManager::getInstance();

	V_ViewMode = false;
	V_CurrentDrawing = false;

	V_Lights.resize(3);
	for (auto& l : V_Lights)
		l.dif = Vec4d(0, 0, 0, 0), l.spc = Vec4d(0, 0, 0, 0);
	M_SetupHieraModels();

	V_PartyMode = false;

}

void CGraphics::M_ListenMessages(void)
{
	auto iq = SIQueue::M_GetSingletone(0);
	auto rq = SIQueue::M_GetSingletone(1);
	while (!iq->M_Empty())
	{
		auto m = iq->M_Pop();
		if (m.type == "down")
		{
			if (!M_Event_KeyPress(m.key, m.special)) rq->M_Push(m); //not mine!
		}
	}
	while (!rq->M_Empty())
	{
		iq->M_Push(rq->M_Pop());
	}
}

bool CGraphics::M_Event_KeyPress(int key, bool special)
{
	if (key == 'v' && special == false)
	{
		V_ViewMode = !V_ViewMode;
		return true;
	}
	if (key == 'f' && special == false)
	{
		V_SM->Temp_Shading = !V_SM->Temp_Shading;
		return true;
	}
	if (key == 'p' && special == false)
	{
		V_PartyMode = !V_PartyMode;
		return true;
	}
	return false;
}

glm::mat4 CGraphics::M_GetBillboardMat(void)
{
	auto view = V_CTM_View;
	view = glm::transpose(view);
	for (int i = 0; i < 3; i++)
		view[i][3] = 0;
	view = glm::transpose(view); //inverse

	return glm::transpose(view);
}
void CGraphics::M_MoveCamera(void)
{
	double static olda = 0.0;
	V_Camera_Look_Angle = V_PEngine->V_Player->M_GetLook().convert_gl();
	olda = olda * 0.9 + V_Camera_Look_Angle[0]*0.1;

	
	if (V_ViewMode)
	{
		auto ui = CUserInput::getInstance();
		double d = 1-ui->M_MouseGet_Normalized()[1];
		d *= 2;
		auto p = V_PEngine->V_Player->M_GetPosition();
		V_Camera_Pos[0] = p[0] - cos(olda) * (15 + 15*d);
		V_Camera_Pos[1] = p[1] - sin(olda) * (15 + 15*d);
		V_Camera_Pos[2] = 20;

		V_Camera_Look = V_Camera_Pos;
		V_Camera_Look[0] += (20 + 15*d)*cos(V_Camera_Look_Angle[0]);
		V_Camera_Look[1] += (20 + 15 * d)*sin(V_Camera_Look_Angle[0]);
		V_Camera_Look[2] = 5;
	}
	else
	{
		auto p = V_PEngine->V_Player->M_GetPosition();
		V_Camera_Pos[0] = p[0] + 0.8*cos(V_Camera_Look_Angle[0]);
		V_Camera_Pos[1] = p[1] + 0.8*sin(V_Camera_Look_Angle[0]);
		V_Camera_Pos[2] = 3;

		V_Camera_Look = V_Camera_Pos;
		V_Camera_Look[0] += 5 * cos(V_Camera_Look_Angle[0]);
		V_Camera_Look[1] += 5 * sin(V_Camera_Look_Angle[0]);
		V_Camera_Look[2] += 2 * sin(V_Camera_Look_Angle[1]);
	}


	return;

}
void CGraphics::M_CallbackDisplay()
{
	V_KeepLight = false;
	M_ListenMessages();

	V_CTM_Temp = glm::mat4(1.0);

	static double count = 0;
	count += 0.02;
	M_MoveCamera();

	V_CurrentDrawing = false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	V_SM->M_UseProgram("prg1");
	
	V_CTM_Project = glm::mat4(1.0f);
	V_CTM_Project = glm::translate(V_CTM_Project, glm::vec3(-1.0, -1.0, 0.0));
	V_CTM_Project = glm::scale(V_CTM_Project, glm::vec3(2.0 / V_Screen_Size[0], 2.0 / V_Screen_Size[1], 1));
	V_CTM_View = glm::mat4(1.0f);
	M_RenderUI();

	
	V_CurrentDrawing = true;

	glm::vec3 v(0.0f);
	glm::vec3 up(0, 0, 1);

	V_CTM_Project = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 1000.0f);
	V_CTM_View = glm::lookAt(V_Camera_Pos, V_Camera_Look, up);

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
	SRenderInfo r;

	glm::mat4 m = V_CTM_View;
	m = V_CTM_View;
	m = glm::translate(m, glm::vec3(p1));
	m = glm::scale(m, glm::vec3(p2 - p1));

	r.modelview = m;
	r.projection = V_CTM_Project;
	
	for (int i = 0; i < 4; i++) r.color[i] = rgba[i] / 255.0;
	V_Models["line"]->M_Draw(r);
}

void CGraphics::M_DrawModel(Vec3d p, string name, double r, double rotate, T4Int rgba)
{

	SRenderInfo ri;

	glm::mat4 m = V_CTM_View;
	m = glm::translate(m, glm::vec3(p));
	m = glm::rotate(m, float(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	m = glm::scale(m, glm::vec3(r, r, r));
	m = m * V_CTM_Temp; //billboard

	ri.modelview = m;
	ri.projection = V_CTM_Project;

	ri.keeplight = V_KeepLight;
	ri.amb = Vec4d(0.0, 0.0, 0.0, 1.0);

	auto vt = V_CTM_View;
	ri.lights.resize(V_Lights.size());
	transform(V_Lights.begin(), V_Lights.end(), ri.lights.begin(),
		[vt](SLight x)->SLight {x.pos = vt * x.pos; return x; });

	ri.normtrans = m;
	

	for (int i = 0; i < 4; i++) ri.color[i] = rgba[i] / 255.0;
	V_Models[name]->M_Draw(ri);
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
			M_DrawModel(p, "diamond", r*0.5, (2 * PI / 10.0)*i, T4Int(255, 255, 0, 255));
		}
		for (int i = 0; i < 10; i++)
		{
			M_DrawModel(p, "diamond", r, (2 * PI / 10.0)*i, T4Int(255, 0, 0, 255));
		}
		
	}
	if (z == 1) // Camera up
	{
		M_DrawModel(p, "circle", r*0.4, 0, T4Int(255, 255, 255, 255));
		//M_DrawModel(p + Vec3d(r*0.7, r*0.5, 0), "circle", r*0.1, 0, T4Int(255, 255, 255, 255)); fix this
		M_DrawModel(p, "rectangle", r*0.9, 0, T4Int(90, 90, 90, 255));

	}
	if (z == 2) // Invincible
	{
		M_DrawModel(p, "star", r*0.8, 0, T4Int(255, 255, 0, 255));
		M_DrawModel(p, "star", r, 0, T4Int(255, 204, 0, 255));
		
	}
	if (z == 3) // Speed up
	{
		for (int i = 0; i < 3; i++)
		{
			M_DrawModel(p+Vec3d(r*0.1,0,0), "diamond", r, PI/12 + (PI/12)*i, T4Int(255, 255, 255, 255));
			M_DrawModel(p-Vec3d(r*0.1,0,0), "diamond", r, PI - (PI / 12 + (PI / 12)*i), T4Int(255, 255, 255, 255));
		}
	}
	if (z == 4) // SuperFire
	{
		for (int i = 0; i < 4; i++)
		{
			M_DrawModel(p, "diamond", r, (2*PI/4.0)*i, T4Int(30, 30, 30, 255));
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
			M_DrawModel(p+i, "A", r, 0.0, rgba);
		}

		if (k == 0 || k == 1 || k == 2 || k == 3 || k == 4 || k == 7 || k == 8 || k == 9)
		{
			M_DrawModel(p+i, "B", r, 0.0, rgba);
		}

		if (k == 0 || k == 1 || k == 3 || k == 4 || k == 5 || k == 6 || k == 7 || k == 8 || k == 9)
		{
			M_DrawModel(p+i, "C", r, 0.0, rgba);
		}

		if (k == 0 || k == 2 || k == 3 || k == 5 || k == 6 || k == 8 || k == 9)
		{
			M_DrawModel(p+i, "D", r, 0.0, rgba);
		}

		if (k == 0 || k == 2 || k == 6 || k == 8)
		{
			M_DrawModel(p+i, "E", r, 0.0, rgba);
		}

		if (k == 0 || k == 4 || k == 5 || k == 6 || k == 8 || k == 9)
		{
			M_DrawModel(p+i, "F", r, 0.0, rgba);
		}
		if (k == 2 || k == 3 || k == 4 || k == 5 || k == 6 || k == 8 || k == 9)
		{
			M_DrawModel(p+i, "G", r, 0.0, rgba);
		}

		i += Vec3d(r*1.5, 0, 0);
	}
}