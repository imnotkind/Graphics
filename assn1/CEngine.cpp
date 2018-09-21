#include "CEngine.h"



CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}

void CEngine::M_Event_KeyPress(int key, bool special)
{

}
T2Int CEngine::M_GetEmptyPlace(void)
{
	auto math = CMath::getInstance();
	while (true)
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

	for (int i = 0; i < n_itm; i++)
	{
		V_Map[M_GetEmptyPlace()] = 2;
	}
	for (int i = 0; i < n_enm; i++)
	{
		auto p = V_Enemies.insert(unique_ptr<CEnemy>(new CEnemy));
		//p.first->get()->~~ : some initialization
	}

}