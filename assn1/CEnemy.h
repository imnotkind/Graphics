#pragma once
#include "CSomething.h"
class CEnemy :
	public CSomething
{
	queue<T2Double> V_MoveQueue;
	double V_Speed;


public:
	virtual void M_Loop(double t);

	void M_ClearMove(void);
	void M_PushMove(T2Double k) { V_MoveQueue.push(k); }

	CEnemy(T2Double p, int i, T4Int c, double r, double s) : CSomething(p, i, c, r, 0.0), V_Speed(s) {}
	virtual ~CEnemy(){}
};

