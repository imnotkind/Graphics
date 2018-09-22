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
	//Script Messages
	auto mq = SMQueue::M_GetSingletone(0);
	while (!mq->M_Empty()) 
	{
		auto m = mq->M_Pop();
		if (m.type == "creation") // object creation request
		{
			V_Objects.insert(shared_ptr<CSomething>((CSomething*)m.content));
		}
	}

	//Input Messages;
	auto iq = SIQueue::M_GetSingletone(0);
	while (!iq->M_Empty())
	{
		auto m = iq->M_Pop();
		if(m.type == "down") M_Event_KeyPress(m.key, m.special);
	}

}
bool CEngine::M_CheckWallCollision(shared_ptr<CSomething> p)
{
	for (int x = 0; x < V_Map.size[0]; x++)
	{
		for (int y = 0; y < V_Map.size[1]; y++)
		{
			if (V_Map[T2Int(x, y)] == 1) // wall
			{
				T2Double cen = T2Double(x, y)*V_Grid_Size;
				T2Double wh = T2Double(V_Grid_Size, V_Grid_Size);

				if (V_Math->M_CircleRectCollisionTest(p->M_GetPosition(), p->M_GetRadius(), cen, wh)) 
				{
					return true;
				}
			}
		}
	}
	return false;
}
void CEngine::M_ObjectIndexing(void)
{
	V_PBullets.clear();
	V_PEnemies.clear();
	V_PItems.clear();

	for (auto p = V_Objects.begin(); p != V_Objects.end(); p++)
	{
		if (dynamic_cast<CBullet*> (p->get()) != NULL)
		{
			V_PBullets.emplace_back(p);
			continue;
		}
		if (dynamic_cast<CEnemy*> (p->get()) != NULL)
		{
			V_PEnemies.emplace_back(p);
			continue;
		}
		if (dynamic_cast<CItem*> (p->get()) != NULL)
		{
			V_PItems.emplace_back(p);
			continue;
		}
	}
}
void CEngine::M_CollisionTest(void)
{
	set<int> remove_list_bullet;
	set<int> remove_list_enemy;
	set<int> remove_list_item;

	//bullet - wall
	for (int i = 0; i < V_PBullets.size(); i++)
	{
		auto b = V_PBullets[i];
		if (M_CheckWallCollision(*b))
		{
			remove_list_bullet.insert(i);
		}
	}
	//bullet - enemy
	for (int i = 0; i < V_PBullets.size(); i++)
	{
		auto b = V_PBullets[i];
		for (int j = 0; j < V_PEnemies.size(); j++)
		{
			auto e = V_PEnemies[j];
			auto c1 = (*b)->M_GetPosition();
			auto c2 = (*e)->M_GetPosition();
			auto r1 = (*b)->M_GetRadius();
			auto r2 = (*e)->M_GetRadius();

			if (V_Math->M_2CirclesCollsionTest(c1, r1, c2, r2))
			{
				remove_list_enemy.insert(j);
				remove_list_bullet.insert(i);
			}
		}	
	}

	//item - character
	for (int i = 0; i < V_PItems.size(); i++)
	{
		auto t = V_PItems[i];
		auto c1 = V_Player->M_GetPosition();
		auto c2 = (*t)->M_GetPosition();
		auto r1 = V_Player->M_GetRadius();
		auto r2 = (*t)->M_GetRadius();

		if (V_Math->M_2CirclesCollsionTest(c1, r1, c2, r2))
		{
			remove_list_item.insert(i);
		}
	}

	//enemy - character
	for (auto e : V_PEnemies)
	{
		auto c1 = V_Player->M_GetPosition();
		auto c2 = (*e)->M_GetPosition();
		auto r1 = V_Player->M_GetRadius();
		auto r2 = (*e)->M_GetRadius();

		if (V_Math->M_2CirclesCollsionTest(c1, r1, c2, r2))
		{
			M_Defeat();
			return;
		}
	}

	for (auto i : remove_list_bullet) V_Objects.erase(V_PBullets[i]);
	for (auto i : remove_list_enemy) V_Objects.erase(V_PEnemies[i]);
	for (auto i : remove_list_item) V_Objects.erase(V_PItems[i]);

}

void CEngine::M_Defeat(void)
{
	cout << "you Lose!" << endl;
}
void CEngine::M_MoveRequest(T2Double d)
{
	V_Player->M_Move(d);

	if(M_CheckWallCollision(V_Player))
		V_Player->M_Move(d *(-1));
}
void CEngine::M_Loop(void)
{
	M_ObjectIndexing();

	//TODO : caculate time elapsed
	double t = 1.0;

	for (auto p : V_Objects)
	{
		p->M_Loop(t);
	}
	V_Player->M_Loop(t);
	M_CollisionTest();
	
	M_ListenMessages();
	M_CheckKeyPress();
}
void CEngine::M_CheckKeyPress()
{
	auto iq = CUserInput::getInstance();
	if (iq->M_IfPressed(GLUT_KEY_DOWN, true))
	{
		M_MoveRequest(T2Double(0, -V_Grid_Size * 0.1));
	}
	if (iq->M_IfPressed(GLUT_KEY_UP, true))
	{
		M_MoveRequest(T2Double(0, V_Grid_Size * 0.1));
	}
	if (iq->M_IfPressed(GLUT_KEY_LEFT, true))
	{
		M_MoveRequest(T2Double(-V_Grid_Size * 0.1, 0));
	}
	if (iq->M_IfPressed(GLUT_KEY_RIGHT, true))
	{
		M_MoveRequest(T2Double(V_Grid_Size * 0.1, 0));
	}
}
void CEngine::M_Event_KeyPress(int key, bool special)
{
	/*
	if (special)
	{
		if (key == GLUT_KEY_DOWN) M_MoveRequest(T2Double(0, -V_Grid_Size * 0.1));
		if (key == GLUT_KEY_UP) M_MoveRequest(T2Double(0, V_Grid_Size * 0.1));
		if (key == GLUT_KEY_LEFT) M_MoveRequest(T2Double(-V_Grid_Size * 0.1, 0));
		if (key == GLUT_KEY_RIGHT) M_MoveRequest(T2Double(V_Grid_Size * 0.1, 0));
	}
	else*/
	{
		if (key == 32) V_Player->M_Fire(); // Space bar
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