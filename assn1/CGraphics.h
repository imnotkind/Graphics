#pragma once
#include "MainHeader.h"
#include "CGraphics.h"
class CGraphics
{
public:
	void M_CallbackDisplay();
	void M_CallbackReshape(int w, int h);

	void M_DrawStar(Vec2d p, double size);
	void M_DrawLine(Vec2d p1, Vec2d p2);
	void M_DrawPolygon(Vec2d p, double r, int bump, double rotate);
	void M_DrawFont(Vec2d p, const char * string);
	
	CGraphics();
	~CGraphics();

	void M_Initialize();

	
};

