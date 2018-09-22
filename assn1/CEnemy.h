#pragma once
#include "CSomething.h"
class CEnemy :
	public CSomething
{
public:
	virtual void M_Loop(double t);

	CEnemy(T2Double p, int i, T4Int c, double r) : CSomething(p, i, c, r, 0.0) {}
	virtual ~CEnemy(){}
};

