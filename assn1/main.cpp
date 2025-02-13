

#include "CEngine.h"
#include "CGraphics.h"

CGraphics Graphics;
CEngine Engine;

CMath* CMath::Instance = NULL;
CUserInput* CUserInput::Instance = NULL;
CGeneral* CGeneral::Instance = NULL;

map<int, CMessageQueue<SScriptMessage>*> CMessageQueue<SScriptMessage>::V_Multiton = map<int, CMessageQueue<SScriptMessage>*>();
map<int, CMessageQueue<SInputMessage>*> CMessageQueue<SInputMessage>::V_Multiton = map<int, CMessageQueue<SInputMessage>*>();

LARGE_INTEGER old_count;
LARGE_INTEGER new_count;
LARGE_INTEGER freq;

void cb_display()
{
	Graphics.M_CallbackDisplay();
}

void cb_reshape(int w, int h)
{
	cout << "reshape" << endl;
	Graphics.M_CallbackReshape(w,h);
}

void cb_idle()
{
	if (QueryPerformanceCounter(&new_count)) {

		//if ((new_count.QuadPart - old_count.QuadPart) / (freq.QuadPart/1000000.0) < 1000000.0 * (1 / 700.0)) return;
		if (((new_count.QuadPart - old_count.QuadPart) * 1000000) / freq.QuadPart < 1000000 / 90) return;

		old_count = new_count;

		Graphics.M_CallbackIdle();
		Engine.M_Loop();
	}
	else {
		cout << "counter fail" << endl;
	}
	
}

void cb_key(unsigned char key, int x, int y)
{
	auto iq = CUserInput::getInstance();
	iq->M_PressDown(key, false);
}
void cb_skey(int key, int x, int y)
{
	auto iq = CUserInput::getInstance();
	iq->M_PressDown(key, true);
}
void cb_keyup(unsigned char key, int x, int y)
{
	//cout << "up: " << key << endl;
	auto iq = CUserInput::getInstance();
	iq->M_PressUp(key, false);

}
void cb_skeyup(int key, int x, int y)
{
	//cout << "up : " << key << endl;
	auto iq = CUserInput::getInstance();
	iq->M_PressUp(key, true);
}


int main(int argc, char **argv) {

	if (QueryPerformanceFrequency(&freq))
	{
		cout << freq.QuadPart << endl;
		if (QueryPerformanceCounter(&new_count))
		{
			old_count = new_count;
		}
		else
		{
			cout << "counter fail" << endl;
			exit(2);
		}
	}
	else
	{
		cout << "counter fail" << endl;
		exit(1);
	}

	glutInit(&argc, argv);
	Graphics.M_Initialize(&Engine);

	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);

	glutIdleFunc(cb_idle);

	glutKeyboardFunc(cb_key);
	glutSpecialFunc(cb_skey);

	glutKeyboardUpFunc(cb_keyup);
	glutSpecialUpFunc(cb_skeyup);
	
	glewInit();

	
	Engine.M_Initialize();

	glutMainLoop();

	return 0;
}