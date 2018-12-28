#pragma once

#include "TGrid.h"
#include "CHandler.h"
#include "MessageQueue.h"
#include "CUserInput.h"
#include <fstream>

#include <set>
#include <list>

class CGraphics;

struct SBuilding
{
	Vec3d pos;


	double w;
	double h;

	double rotate;
	double height;

	bool operator<(const SBuilding& s) const
	{
		int a = *(((int*)this) + 2);
		int b = *(((int*)&s) + 2);

		return a < b;
	}
};

class CEngine : public CHandler
{
	void M_ListenMessages(void);
	bool M_Event_KeyPress(int key, bool special); //false : not mine

	friend class CGraphics;

	set<SBuilding> V_Building;

public:

	void M_Loop(void);
	void M_CheckKeyPress();
	void M_Initialize(void);
	

	CEngine();
	~CEngine();
};

