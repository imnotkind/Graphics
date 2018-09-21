#include "CSomething.h"



CSomething::~CSomething()
{
}

void CSomething::M_Move(T2Double d)
{
	auto math = CMath::getInstance();
	V_Rotate = math->M_2TV_Angle(V_Position, V_Position + d)[0];
	V_Position += d;
	
}