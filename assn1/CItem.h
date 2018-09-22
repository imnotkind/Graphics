#pragma once
#include "CSomething.h"
class CItem :
	public CSomething
{
public:

	virtual void M_Loop(double t);

	CItem(T2Double p, int i, T4Int c, double r) : CSomething(p, i, c, r, 0.0) {}

	virtual ~CItem() {}
};

