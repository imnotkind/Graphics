#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "Opengl32.lib")

using namespace std;

#include "CEngine.h"
#include "CGraphics.h"

CGraphics Graphics;
CEngine Engine;

void cb_draw(void) {

	Graphics.M_Draw();
	//glClear(GL_COLOR_BUFFER_BIT); move to graphics
	//glFlush();
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
	glutMainLoop();

	return 0;
}