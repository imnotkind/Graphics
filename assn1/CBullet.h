#pragma once
#include "CSomething.h"
class CBullet :
	public CSomething
{
	T2Double V_Velocity;
public:

	virtual void M_Loop(double t);

	CBullet(T2Double p, Type_Not_Determined i, T4Int c, double r, T2Double v) : CSomething(p,i,c,r) { V_Velocity = v; }
	virtual ~CBullet();
};

