#include "CEngine.h"



CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}
void CEngine::M_ReadMap(string path)
{
	ifstream fs;
	fs.open(path);

	int w, h;
	fs >> w >> h >> V_Max_Items >> V_Max_Enemies;
	string s;
	V_Map.resize(T2Int(w, h), -1);
	for (int i = 0; i < h; i++)
	{
		fs >> s;
		if (s.size() != w) CError("Invliad map data format", true);
		for (int j = 0; j < w; j++)
		{
			V_Map[T2Int(j, i)] = s[j] - '0';
		}
	}
}
void CEngine::M_ListenMessages(void)
{
	auto mq = SMQueue::M_GetSingletone(0);
	while (mq->M_Empty()) 
	{
		auto m = mq->M_Pop();
		if (m.type == "creation") // object creation request
		{
			V_Objects.insert(shared_ptr<CSomething>((CSomething*)m.content));
		}
	}
}
void CEngine::M_MoveRequest(T2Double d)
{
	auto p = V_Player->M_GetPosition() + d;
	double r = V_Player->M_GetRadius();

	for (int x = 0; x < V_Map.size[0]; x++)
	{
		for (int y = 0; y < V_Map.size[1]; y++)
		{
			if (V_Map[T2Int(x, y)] == 1) // wall
			{
				T2Double cen = T2Double(x, y)*V_Grid_Size;
				T2Double wh = T2Double(V_Grid_Size, V_Grid_Size);

				if (V_Math->M_CircleRectCollisionTest(p, r, cen, wh)) //if the request is onto not movable place
				{
					return;
				}
			}
		}
	}
	V_Player->M_Move(d);
}
void CEngine::M_Loop(void)
{
	//TODO : caculate time elapsed
	double t = 1.0;

	for (auto p : V_Objects)
	{
		p->M_Loop(t);
	}
	V_Player->M_Loop(t);

}
void CEngine::M_Event_KeyPress(int key, bool special)
{
	if (special)
	{
		if (key == GLUT_KEY_DOWN) M_MoveRequest(T2Double(0, -V_Grid_Size * 0.1));
		if (key == GLUT_KEY_UP) M_MoveRequest(T2Double(0, V_Grid_Size * 0.1));
		if (key == GLUT_KEY_LEFT) M_MoveRequest(T2Double(-V_Grid_Size * 0.1, 0));
		if (key == GLUT_KEY_RIGHT) M_MoveRequest(T2Double(V_Grid_Size * 0.1, 0));
	}
	else
	{
		if (key == 20) V_Player->M_Fire(); // Space bar
	}
}
T2Int CEngine::M_GetEmptyPlace(void)
{
	while (true) // random try
	{
		int x = V_Math->M_Num_iRandom(0, V_Map.size[0] - 1);
		int y = V_Math->M_Num_iRandom(0, V_Map.size[1] - 1);

		if (V_Map[T2Int(x, y)] == 0)
		{
			return(T2Int(x, y));
		}
	}
}
void CEngine::M_Initialize(void)
{

	V_Grid_Size = 6.0;
	
	M_ReadMap("map.txt");

	int n_enm = V_Max_Enemies;
	int n_itm = V_Max_Items;

	V_Player = shared_ptr<CCharacter>(new CCharacter(T2Double(1, 1) * V_Grid_Size, 2, T4Int(255, 0, 0, 255), V_Grid_Size * 0.3));

	//place items
	for (int i = 0; i < n_itm; i++)
	{
		auto p = M_GetEmptyPlace();
		V_Map[p] = 2;
		auto q = V_Objects.insert(shared_ptr<CItem>(new CItem(T2Double(p[0], p[1]) * V_Grid_Size, 0, T4Int(0,255,255,255), V_Grid_Size * 0.3)));
	}
	//place enemies
	for (int i = 0; i < n_enm; i++)
	{
		auto p = M_GetEmptyPlace();
		auto q = V_Objects.insert(shared_ptr<CEnemy>(new CEnemy(T2Double(p[0], p[1]) * V_Grid_Size, 1, T4Int(0, 255, 0, 255), V_Grid_Size * 0.3)));
		//p.first->get()->~~ : some initialization
	}

}