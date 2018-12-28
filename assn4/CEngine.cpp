#include "CEngine.h"



CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::M_ListenMessages(void)
{
	//Input Messages;
	auto iq = SIQueue::M_GetSingletone(0);
	auto rq = SIQueue::M_GetSingletone(1);

	while (!iq->M_Empty())
	{
		auto m = iq->M_Pop();
		if (m.type == "down")
		{
			if (!M_Event_KeyPress(m.key, m.special)) rq->M_Push(m); //not mine!
		}
	}
	while (!rq->M_Empty())
	{
		iq->M_Push(rq->M_Pop());
	}

}


void CEngine::M_Loop(void)
{

	M_ListenMessages();
	M_CheckKeyPress();

}
void CEngine::M_CheckKeyPress()
{
	auto iq = CUserInput::getInstance();
	double speed = 0.1;
}

bool CEngine::M_Event_KeyPress(int key, bool special)
{

	if (key == KEY_LEFT_CLICK && special)
	{
	
		return true;
	}
	return false;
}

void CEngine::M_Initialize(void)
{
	for (int i = 0; i < 50; i++)
	{
		double x = V_Math->M_Num_Gaussian(0, 20);
		double y = V_Math->M_Num_Gaussian(0, 20);
		double h = std::max(50 - x*x - y*y, 1.0);

		SBuilding b;
		b.pos = Vec3d(x, y, 0);
		b.rotate = V_Math->M_Num_dRandom(0, 2 * PI);
		b.height = V_Math->M_Num_dRandom(1, h);
		b.w = V_Math->M_Num_dRandom(1, 5);
		b.h = V_Math->M_Num_dRandom(1, 5);

		V_Building.insert(b);
	}
	
}
