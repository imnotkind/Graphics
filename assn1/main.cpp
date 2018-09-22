

#include "CEngine.h"
#include "CGraphics.h"

CGraphics Graphics;
CEngine Engine;

CMath* CMath::Instance = NULL;
map<int, CMessageQueue<SScriptMessage>*> CMessageQueue<SScriptMessage>::V_Multiton = map<int, CMessageQueue<SScriptMessage>*>();


void cb_display()
{
	cout << "display" << endl;
	Graphics.M_CallbackDisplay();
}

void cb_reshape(int w, int h)
{
	cout << "reshape" << endl;
	Graphics.M_CallbackReshape(w,h);
}

void cb_key(unsigned char key, int x, int y)
{
	Engine.M_Event_KeyPress(key, false);
}
void cb_skey(int key, int x, int y)
{
	Engine.M_Event_KeyPress(key, true);
}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	Graphics.M_Initialize();

	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
	glutKeyboardFunc(cb_key);
	glutSpecialFunc(cb_skey);

	
	glewInit();

	
	//Engine.M_Initialize();

	glutMainLoop();

	return 0;
}