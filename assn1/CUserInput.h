#pragma once
#include "CHandler.h"
#include "MessageQueue.h"

struct SInputMessage
{
	string type;
	int key;
	bool special;
};
typedef CMessageQueue<SInputMessage> SIQueue;

class CUserInput : public CHandler
{
	static CUserInput* Instance;
	
	CUserInput();
public:
	set<pair<int,bool>> V_pressingkeys;

	static CUserInput* getInstance(void)
	{
		if (Instance == NULL)Instance = new CUserInput;
		return Instance;
	}
	static void freeInstance(void)
	{
		if (Instance) delete Instance;
	}


	void M_PressDown(int key, bool special);
	void M_PressUp(int key, bool special);

	bool M_IfPressed(int key, bool special);

	
	
	~CUserInput();
};

