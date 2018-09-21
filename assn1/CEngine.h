#pragma once
#include "CCharacter.h"
#include "CItem.h"
#include "CEnemy.h"
#include "TGrid.h"
#include "CMath.h"

#include <set>

class CGraphics;

class CEngine
{
	TGrid<int, 2> V_Map;

	double M_Grid_Size;
	friend CGraphics;

	shared_ptr<CCharacter> V_Player;
	set <shared_ptr<CSomething>> V_Objects;
	

	T2Int M_GetEmptyPlace(void);
	void M_MoveRequest(Vec2f d); //request for move character


public:

	void M_CollisionTest(void);
	void M_Loop(void);

	void M_Initialize(void);
	void M_Event_KeyPress(int key, bool special);

	CEngine();
	~CEngine();
};

