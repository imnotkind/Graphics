#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "Opengl32.lib")

using namespace std;
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void mytest1(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		cout << "q!" << endl;
		while (true)
		{
			cout << "hihihi" << endl;
			Sleep(1000);
		}
	}
	cout << "No!" << endl;
}
void mytest2(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		cout << "hmm??" << endl;
	}
	cout << "wtf" << endl;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(renderScene);

	glutKeyboardFunc(mytest1);
	glutSpecialFunc(mytest2);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();

	return 0;
}