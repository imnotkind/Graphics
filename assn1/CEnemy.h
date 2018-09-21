#pragma once
#include "CSomething.h"
class CEnemy :
	public CSomething
{
public:
	virtual void M_Loop(double t);

	CEnemy(T2Double p, Type_Not_Determined i, T4Int c, double r) : CSomething(p, i, c, r) {}
	virtual ~CEnemy(){}
};

