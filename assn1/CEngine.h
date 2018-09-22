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
	//Object Indexing cahces
	vector<set<shared_ptr<CSomething>>::iterator> V_PBullets;
	vector<set<shared_ptr<CSomething>>::iterator> V_PEnemies;
	vector<set<shared_ptr<CSomething>>::iterator> V_PItems;

	//

	double V_Grid_Size;
	friend CGraphics;

	shared_ptr<CCharacter> V_Player;
	set <shared_ptr<CSomething>> V_Objects;
	
	void M_Defeat(void);

	T2Int M_GetEmptyPlace(void);
	void M_MoveRequest(T2Double d); //request for move character

	void M_ReadMap(string path);

	//map parameter
	int V_Max_Enemies;
	int V_Max_Items;
	TGrid<int, 2> V_Map;

	bool M_CheckWallCollision(shared_ptr<CSomething> p);

	void M_CollisionTest(void);
	void M_ListenMessages(void);
	void M_Event_KeyPress(int key, bool special);

	void M_ObjectIndexing(void);

public:

	
	void M_Loop(void);
	void M_Initialize(void);
	

	CEngine();
	~CEngine();
};

