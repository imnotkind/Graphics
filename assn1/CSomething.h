#pragma once
#include "MainHeader.h"

class CSomething
{
protected:
	Vec2f V_Position;
	Type_Not_Determined V_Image;
	Type_Not_Determined V_Color;

	double V_Rotate;
	double V_Radius;

public:
	void M_Move(Vec2f d);
	double M_GetRadius(void) { return V_Radius; }

	CSomething();
	~CSomething();
};

