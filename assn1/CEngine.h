#pragma once
#include "CCharacter.h"
#include "CItem.h"
#include "CEnemy.h"
#include "TGrid.h"
#include "CHandler.h"
#include <fstream>

#include <set>

class CGraphics;

class CEngine : public CHandler
{
	

	double M_Grid_Size;
	friend CGraphics;

	shared_ptr<CCharacter> V_Player;
	set <shared_ptr<CSomething>> V_Objects;
	

	T2Int M_GetEmptyPlace(void);
	void M_MoveRequest(T2Double d); //request for move character

	void M_ReadMap(string path);

	//map parameter
	int V_Max_Enemies;
	int V_Max_Items;
	TGrid<int, 2> V_Map;

public:

	void M_CollisionTest(void);

	void M_Loop(void);
	void M_ListenMessages(void);

	void M_Initialize(void);
	void M_Event_KeyPress(int key, bool special);

	CEngine();
	~CEngine();
};

