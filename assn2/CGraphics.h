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
	CShaderManager* V_SM;

	T2Double V_Screen_Size;

	T2Double V_Camera_Pos;
	T2Double V_Camera_Speed;
	double V_Camera_Height;

	glm::mat4 V_CTM;

	
	double V_CrazyParam;
	bool V_CurrentDrawing; //ui : false
	
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
	void M_DrawHier(Vec3d p, string name, double r, double rotate, T4Int rgba); 

	void M_DrawFont(Vec2d p, string str, T4Int rgba);
	void M_DrawFontBig(Vec2d p, string str, double scale, T4Int rgba);
	void M_DrawItem(Vec3d p, double r, int z);

	void M_DrawNumber(Vec3d p, double r, int num, T4Int rgba);

	void M_SetupHieraModels(void);

	map<string, shared_ptr<CSinglePolygon>> V_BasicPolygons;
	map<string, shared_ptr<CHierModel>> V_Hiers;

public:

	void M_CallbackDisplay();
	void M_CallbackReshape(int w, int h);
	void M_CallbackIdle();

	void M_Initialize(CEngine * P);
	void M_Initialize2(void);

	CGraphics();
	~CGraphics();

	

	
};

