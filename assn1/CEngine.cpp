#include "CEngine.h"



CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::M_MoveRequest(Vec2f d)
{
	for (int x = 0; x < V_Map.size[0]; x++)
	{
		for (int y = 0; y < V_Map.size[1]; y++)
		{
			//TODO : implement collision test between character and block
			if (true)
			{
				V_Player.M_Move(d);
			}
			else
			{

			}
		}
	}
}

void CEngine::M_Event_KeyPress(int key, bool special)
{

}
T2Int CEngine::M_GetEmptyPlace(void)
{
	auto math = CMath::getInstance();
	while (true) // random try
	{
		int x = math->M_Num_iRandom(0, V_Map.size[0] - 1);
		int y = math->M_Num_iRandom(0, V_Map.size[1] - 1);

		if (V_Map[T2Int(x, y)] == 0)
		{
			return(T2Int(x, y));
		}
	}
}
void CEngine::M_Initialize(void)
{
	
	//TODO: load the map

	int n_enm = 50;
	int n_itm = 10;

	auto math = CMath::getInstance();

	//place items
	for (int i = 0; i < n_itm; i++)
	{
		V_Map[M_GetEmptyPlace()] = 2;
	}
	//place enemies
	for (int i = 0; i < n_enm; i++)
	{
		auto p = V_Enemies.insert(unique_ptr<CEnemy>(new CEnemy));
		//p.first->get()->~~ : some initialization
	}

}