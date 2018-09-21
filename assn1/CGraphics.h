#pragma once
#include "MainHeader.h"
#include "CGraphics.h"
class CGraphics
{
public:
	void M_Initialize(void);
	void M_RenderGame(void);
	void M_DrawCircle(double x, double y, double size);
	void M_DrawTriangle(double x, double y, double size);
	void M_DrawSquare(double x, double y, double size);

	void M_DrawPentagon(double x, double y, double size);

	void M_DrawStar(double x, double y, double size);

	void M_DrawLine(double x1, double y1, double x2, double y2);

	
	
	CGraphics();
	~CGraphics();

private:
	void M_DrawPolygon(double cx, double cy, double r, int bump, double rotate);
};

