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


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(770, 320);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(display);
	glutReshapeFunc(myReshape);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();

	return 0;
}