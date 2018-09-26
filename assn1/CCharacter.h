#pragma once
#include "CSomething.h"
#include "CBullet.h"

class CCharacter :
	public CSomething
{
	list<int> V_Items;
	int V_Power;//bullet power
	int V_InvTime;
public:
	virtual void M_Loop(double t);

	void M_MegaFire(void);
	void M_Fire(void); //fire a bullet
	void M_GetInvincible(int t);

	list<int>& M_GetItemList(void) {return V_Items;}

	CCharacter(T2Double p, int i, T4Int c, double r) : CSomething(p, i, c, r, 0.0) { V_Power = 0; V_InvTime = 0; }
	virtual ~CCharacter() {}
};

