#pragma once
#include "MainHeader.h"
#include "CGraphics.h"
class CGraphics
{
public:
	void M_CallbackDisplay();
	void M_CallbackReshape(int w, int h);

	void M_DrawPolygon(double cx, double cy, double r, int bump, double rotate);
	void M_DrawStar(double x, double y, double size);
	void M_DrawLine(double x1, double y1, double x2, double y2);
	
	CGraphics();
	~CGraphics();

	void M_Initialize();

	
};

