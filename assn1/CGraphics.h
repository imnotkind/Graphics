#pragma once
#include "MainHeader.h"
#include "CGraphics.h"
#include "CEngine.h"
#include "CHandler.h"

#include <ctime>

class CGraphics : public CHandler
{
	CEngine * V_PEngine;

	T2Double V_Screen_Size;

	T2Double V_Camera_Pos;
	double V_Camera_Size;
	double V_Camera_Size_Acc;
	T2Double V_Camera_Speed;

	
	//
	double fps = 0;
	unsigned long old;

	void RenderGame(void);
	void RenderUI(void);
	void M_MoveCamera(void);

	void M_DrawLine(Vec2d p1, Vec2d p2, T4Int rgba);
	void M_DrawStar(Vec2d p, double r, double rotate, T4Int rgba);
	void M_DrawPolygon(Vec2d p, double r, int bump, double rotate, T4Int rgba);
	void M_DrawFont(Vec2d p, string str, T4Int rgba);
	void M_DrawFontBig(Vec2d p, string str, double scale, T4Int rgba);
	void M_DrawItem(Vec2d p, double r, int z);

public:

	void M_CallbackDisplay();
	void M_CallbackReshape(int w, int h);
	void M_CallbackIdle();

	void M_Initialize(CEngine * P);

	CGraphics();
	~CGraphics();

	

	
};

