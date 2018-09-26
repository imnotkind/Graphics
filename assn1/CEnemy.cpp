#include "CEnemy.h"



void CEnemy::M_ClearMove(void)
{
	while (!V_MoveQueue.empty())V_MoveQueue.pop();
}
void CEnemy::M_Loop(double t)
{
	if (V_MoveQueue.empty())
	{
		return;
	}

	auto math = CMath::getInstance();
	auto des = V_MoveQueue.front();

	if (math->M_2TV_Angle(V_Position, des)[1] < 0.01)
	{
		M_ClearMove();
		return;
	}
	M_Move(math->M_2TV_Normalize(des - V_Position) * V_Speed); //move by speed
}