

#include "CEngine.h"
#include "CGraphics.h"

CGraphics Graphics;
CEngine Engine;

CMath* CMath::Instance = NULL;
map<int, CMessageQueue<SScriptMessage>*> CMessageQueue<SScriptMessage>::V_Multiton = map<int, CMessageQueue<SScriptMessage>*>();

void cb_draw(void) {

	Graphics.M_Draw();
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Hello OpenGL");

	glutDisplayFunc(cb_draw);
	glutKeyboardFunc(cb_key);
	glutSpecialFunc(cb_skey);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();

	Graphics.M_Initialize();
	Engine.M_Initialize();

	glutMainLoop();

	return 0;
}