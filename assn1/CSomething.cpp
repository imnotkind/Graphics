#include "CSomething.h"



CSomething::CSomething()
{
}


CSomething::~CSomething()
{
}

void CSomething::M_Move(Vec2f d)
{
	auto math = CMath::getInstance();
	V_Rotate = math->M_2TV_Angle(V_Position, V_Position + d)[0];
	V_Position += d;
	
}