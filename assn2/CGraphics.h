#pragma once
#include "MainHeader.h"
#include "CGraphics.h"
#include "CEngine.h"
#include "CHandler.h"
#include "CShaderManager.h"
#include "CSinglePolygon.h"

#include <ctime>

class CGraphics : public CHandler
{
	CEngine * V_PEngine;

	T2Double V_Screen_Size;

	T2Double V_Camera_Pos;
	T2Double V_Camera_Speed;
	double V_Camera_Height;

	glm::mat4 V_CTM;

	

	
	//
	double fps = 0;

	LARGE_INTEGER old_count;
	LARGE_INTEGER new_count;
	LARGE_INTEGER freq;

	void M_RenderGame(void);
	void M_RenderUI(void);
	void M_MoveCamera(void);

	void M_DrawLine(Vec3d p1, Vec3d p2, T4Int rgba);
	void M_DrawPolygon(Vec3d p, string name, double r, double rotate, T4Int rgba); //lying on xy

	void M_DrawFont(Vec2d p, string str, T4Int rgba);
	void M_DrawFontBig(Vec2d p, string str, double scale, T4Int rgba);
	void M_DrawItem(Vec2d p, double r, int z);

	void M_SetupHieraModels(void);

	map<string, shared_ptr<CSinglePolygon>> V_BasicPolygons;

public:

	void M_CallbackDisplay();
	void M_CallbackReshape(int w, int h);
	void M_CallbackIdle();

	void M_Initialize(CEngine * P);
	void M_Initialize2(void);

	CGraphics();
	~CGraphics();

	

	
};

