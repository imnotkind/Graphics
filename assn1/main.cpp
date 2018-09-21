

#include "CEngine.h"
#include "CGraphics.h"

CGraphics Graphics;
CEngine Engine;

CMath* CMath::Instance = NULL;
map<int, CMessageQueue<SScriptMessage>*> CMessageQueue<SScriptMessage>::V_Multiton = map<int, CMessageQueue<SScriptMessage>*>();

void cb_display(void) {
	cout << "display" << endl;

	glClear(GL_COLOR_BUFFER_BIT);

	Graphics.M_RenderGame();

	glutSwapBuffers();
}

void cb_reshape(int w, int h) {
	cout << "reshape" << endl;

	glViewport(0, 0, w, h);
	glLoadIdentity(); 
	gluOrtho2D(0.0, 100.0, 0.0, 100.0); 
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello OpenGL");
	

	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
	glutKeyboardFunc(cb_key);
	glutSpecialFunc(cb_skey);

	
	glewInit();

	Graphics.M_Initialize();
	//Engine.M_Initialize();

	glutMainLoop();

	return 0;
}