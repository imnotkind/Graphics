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

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(renderScene);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();

	return 0;
}

void myReshape(int w, int h) {
	glLoadIdentity();
	glViewport(0, 0, w, h); 
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glRectf(10.0, 10.0, 90.0, 90.0);
	glutSwapBuffers();
}