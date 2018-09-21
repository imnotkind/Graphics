#pragma once
#include "CSomething.h"
#include "CBullet.h"

class CCharacter :
	public CSomething
{
public:
	virtual void M_Loop(double t);

	void M_Fire(void); //fire a bullet

	CCharacter(T2Double p, Type_Not_Determined i, T4Int c, double r) : CSomething(p, i, c, r) {}
	virtual ~CCharacter() {}
};

