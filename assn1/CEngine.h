#pragma once
#include "CCharacter.h"
#include "CItem.h"
#include "CEnemy.h"
#include "TGrid.h"

#include <set>

class CGraphics;

class CEngine
{
	TGrid<int, 2> V_Map;

	double M_Grid_Size;
	friend CGraphics;

	CCharacter V_Player;
	set <CEnemy*> V_Enemies;
	set <CItem*> V_Items;
	
public:

	void M_CollisionTest(void);

	void M_Initialize(void);
	void M_Event_KeyPress(int key, bool special);

	CEngine();
	~CEngine();
};

