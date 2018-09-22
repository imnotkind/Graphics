#include "CUserInput.h"



CUserInput::CUserInput()
{
}


CUserInput::~CUserInput()
{
}

void CUserInput::M_PressDown(int key, bool special)
{
	auto iq = SIQueue::M_GetSingletone(0);
	SInputMessage s;
	s.key = key;
	s.special = 0;
	s.type = "down";
	iq->M_Push(s);

	//TODO : record somewhere

}
void CUserInput::M_PressUp(int key, bool special)
{
	auto iq = SIQueue::M_GetSingletone(0);
	SInputMessage s;
	s.key = key;
	s.special = 0;
	s.type = "up";
	iq->M_Push(s);

	//TODO : record somewhere
}
bool CUserInput::M_IfPressed(int key, bool special)
{
	//TODO
}