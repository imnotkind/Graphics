#pragma once
#include "CCharacter.h"
#include "CItem.h"
#include "CEnemy.h"
#include "TGrid.h"
#include "CHandler.h"

#include "CUserInput.h"
#include <fstream>

#include <set>
#include <list>

class CGraphics;

class CEngine : public CHandler
{
	void M_ListenMessages(void);
	bool M_Event_KeyPress(int key, bool special); //false : not mine

	friend class CGraphics;

public:

	void M_Loop(void);
	void M_CheckKeyPress();
	void M_Initialize(void);
	

	CEngine();
	~CEngine();
};

