#pragma once
#include "MainHeader.h"
#include "CMath.h"
#include "MessageQueue.h"

struct SScriptMessage
{
	int from;
	string type;
	void* content;
};
typedef CMessageQueue<SScriptMessage> SMQueue;

class CSomething
{
protected:
	T2Double V_Position;
	Type_Not_Determined V_Image;
	T4Int V_Color;

	double V_Rotate;
	double V_Radius;

public:
	virtual void M_Loop(double t) {}

	void M_Move(T2Double d);
	double M_GetRadius(void) { return V_Radius; }

	CSomething(T2Double p, Type_Not_Determined i, T4Int c, double r) : V_Position(p), V_Image(i), V_Color(c), V_Radius(r) {}

	~CSomething();
};

