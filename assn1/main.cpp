

#include "CEngine.h"
#include "CGraphics.h"

CGraphics Graphics;
CEngine Engine;

CMath* CMath::Instance = NULL;
CUserInput* CUserInput::Instance = NULL;

map<int, CMessageQueue<SScriptMessage>*> CMessageQueue<SScriptMessage>::V_Multiton = map<int, CMessageQueue<SScriptMessage>*>();
map<int, CMessageQueue<SInputMessage>*> CMessageQueue<SInputMessage>::V_Multiton = map<int, CMessageQueue<SInputMessage>*>();

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
	/*
	auto iq = CUserInput::getInstance();
	for (auto i = iq->V_pressingkeys.begin(); i != iq->V_pressingkeys.end(); i++)
		cout << i->first << i->second ;
	cout << endl;
	*/
	Graphics.M_CallbackIdle();
	Engine.M_Loop();
}

void cb_key(unsigned char key, int x, int y)
{
	//cout << key << endl;
	auto iq = CUserInput::getInstance();
	iq->M_PressDown(key, false);
}
void cb_skey(int key, int x, int y)
{
	//cout << key << endl;
	auto iq = CUserInput::getInstance();
	iq->M_PressDown(key, true);
}
void cb_upkey(unsigned char key, int x, int y)
{
	//cout << "up: " << key << endl;
	auto iq = CUserInput::getInstance();
	iq->M_PressUp(key, false);

}
void cb_supkey(int key, int x, int y)
{
	//cout << "up : " << key << endl;
	auto iq = CUserInput::getInstance();
	iq->M_PressUp(key, true);
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	Graphics.M_Initialize(&Engine);

	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
	glutIdleFunc(cb_idle);
	glutKeyboardFunc(cb_key);
	glutSpecialFunc(cb_skey);
	glutKeyboardUpFunc(cb_upkey);
	glutSpecialUpFunc(cb_supkey);
	
	glewInit();

	
	Engine.M_Initialize();

	glutMainLoop();

	return 0;
}