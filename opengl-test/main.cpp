#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Include all GLM core / GLSL features
#include <glm/glm.hpp> // vec2, vec3, mat4, radians

// Include all GLM extensions
#include <glm/ext.hpp> // perspective, translate, rotate


#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "Opengl32.lib")

using namespace std;
using namespace glm;



glm::mat4 transform(glm::vec2 const& Orientation, glm::vec3 const& Translate, glm::vec3 const& Up)
{
	glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
	glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
	glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
	glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
	glm::mat4 Model = glm::mat4(1.0f);
	return Proj * View * Model;
}

void renderBitmapCharacter(double x, double y, void *font, const char *string)
{
	const char *c;
	glRasterPos2d(x, y);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}


/*
float angl = 0.0f;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glRotatef(angl, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(-2.0f, -2.0f, 0.0f);
	glVertex3f(2.0f, 0.0f, 0.0);
	glVertex3f(0.0f, 2.0f, 0.0);
	glEnd();

	angl += 0.1f;

	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 0.1, 100);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

*/

typedef struct rect {
	double x;
	double y;
	double width;
	double height;
} rect;
rect rectangle = { 50,50,10,20 };

void reshape1(int w, int h) {
	cout << "reshapefunc1" << endl;

	/*
	glMatrixMode(GL_PROJECTION); //matrix mode switchnot needed in 2d
	glLoadIdentity();


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

	//ordering essential
	glViewport(0, 0, w, h);
}

void display1() {
	cout << "displayfunc1" << endl;

	glutSetWindow(1);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity(); //essential for reload

	glColor3d(0, 0.5, 1);
	glBegin(GL_TRIANGLES);
	glVertex2d(0, 0);
	glVertex2d(1, 7);
	glVertex2d(7, 1);
	glEnd();

	
	gluOrtho2D(0.0, 100.0 + rectangle.x, 0.0, 100.0); //coordinate in virtual world


	glColor3d(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2d(-10, -10);
	glVertex2d(10, 70);
	glVertex2d(70, 10);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(rectangle.x, rectangle.y);
	glVertex2d(rectangle.x, rectangle.y + rectangle.height);
	glVertex2d(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
	glVertex2d(rectangle.x + rectangle.width, rectangle.y);
	glEnd();

	renderBitmapCharacter(50, 50, GLUT_BITMAP_HELVETICA_18, "PRESS ANY KEY");

	glutSwapBuffers();
}

//multiple viewport (screen split)
int width;
int height;
void reshape2(int w, int h) {
	cout << "reshapefunc2" << endl;

	width = w;
	height = h;



}





void idle1() {
	
	rectangle.x += 0.1;
	rectangle.y += 0.1;
	glutSetWindow(1);
	glutPostRedisplay();
	//glutSetWindow(2);
	//glutPostRedisplay();
}


void timer1(int value) { //auxiliary value, pass when registering callback
	cout << "3 sec elapsed, aux value : " << value << endl;
}

void mouse1(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		cout << "left mouse ";
	else if (button == GLUT_RIGHT_BUTTON)
		cout << "right mouse ";
	else if (button == GLUT_MIDDLE_BUTTON)
		cout << "middle mouse ";

	if (state == GLUT_UP)
		cout << "UP";
	else if (state == GLUT_DOWN)
		cout << "DOWN";

	cout << "(" << x << "," << y << ")" << endl;

}

void key1(unsigned char key, int x, int y)
{
	cout << "key : " << key << " | mousepos : (" << x << "," << y << ")" << endl;

	glLoadIdentity();
	gluOrtho2D(-10, 100.0, -10, 200.0); //coordinate in virtual world
	glutPostRedisplay();

}
void skey1(int key, int x, int y)
{
	cout << "specialkey : " << key << " | mousepos : (" << x << "," << y << ")" << endl;
}


void display_sub() {
	cout << "display sub func" << endl;
	glutSetWindow(2);
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(0, rectangle.y);
	glVertex2d(100, rectangle.y);
	glVertex2d(rectangle.x, 0);
	glVertex2d(rectangle.x, 100);
	glEnd();
	glutSwapBuffers();
}



int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //GLUT_DEPTH for 3D
	glutInitWindowPosition(400, 400);
	glutInitWindowSize(800, 800);
	cout << glutCreateWindow("Hello OpenGL") << endl;
	glClearColor(1, 1, 1, 1); //only needed once actually if you're going to clear with the same color
	glShadeModel(GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutReshapeFunc(reshape1);
	glutDisplayFunc(display1);
	glutIdleFunc(idle1);
	glutKeyboardFunc(key1);
	glutSpecialFunc(skey1);
	glutMouseFunc(mouse1);
	glutTimerFunc(3000, timer1, 444);

	glewInit();

	//cout << glutCreateSubWindow(1, 100, 100, 100, 100) << endl;
	//glutDisplayFunc(display_sub);

	//glewInit();

	glutMainLoop();



	return 0;
}