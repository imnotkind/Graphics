#pragma once
#include "MainHeader.h"
#include "CGraphics.h"
#include "CEngine.h"

class CGraphics
{
	CEngine * V_PEngine;
	Vec2d V_Camera_p1; //bottom left point of rect
	Vec2d V_Camera_p2; //top right point of rect

	void RenderGame(void);
	void M_DrawLine(Vec2d p1, Vec2d p2, T4Int rgba);
	void M_DrawStar(Vec2d p, double r, double rotate, T4Int rgba);
	void M_DrawPolygon(Vec2d p, double r, int bump, double rotate, T4Int rgba);
	void M_DrawFont(Vec2d p, string str, T4Int rgba);

public:

	void M_CallbackDisplay();
	void M_CallbackReshape(int w, int h);
	void M_CallbackIdle();

	void M_ChangeCamera(Vec2d p1, Vec2d p2);
	void M_Initialize(CEngine * P);

	CGraphics();
	~CGraphics();

	

	
};

