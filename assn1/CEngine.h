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

	CCharacter V_Player;
	set <unique_ptr<CEnemy>> V_Enemies;
	set <unique_ptr<CItem>> V_Items;
	
	T2Int M_GetEmptyPlace(void);
	void M_MoveRequest(Vec2f d);


public:

	void M_CollisionTest(void);

	void M_Initialize(void);
	void M_Event_KeyPress(int key, bool special);

	CEngine();
	~CEngine();
};

