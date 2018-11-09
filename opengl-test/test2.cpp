#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

// Include all GLM core / GLSL features
#include <glm/glm.hpp> // vec2, vec3, mat4, radians

// Include all GLM extensions
#include <glm/ext.hpp> // perspective, translate, rotate
#include <glm/gtc/matrix_transform.hpp>
#include "OBJ_Loader.h"


#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "Opengl32.lib")

using namespace std;
using namespace glm;

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

GLuint VertexShaderID;
GLuint FragmentShaderID;

GLuint default_program;

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	default_program = glCreateProgram();

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

	glBindFragDataLocation(ProgramID, 0, "color");
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	return ProgramID;
}





void reshape1(int w, int h) {
	cout << "reshapefunc1" << endl;
	glViewport(0, 0, w, h);
}

void idle1()
{
	glutPostRedisplay();
}

GLuint programID;
GLuint vertexLoc;


GLuint vertexbuffer;
GLuint vertexbuffer2;

GLuint VertexArrayID;
GLuint VertexArrayID2;

GLuint MatrixID;

void display1() {

	static double k = 0.0;
	k += 0.01;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(10*cos(k), 20, 10*sin(k)), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 mvp = Projection * View * Model;

	glm::mat4 iden = glm::mat4(1.0f);

	
	

	glBindVertexArray(VertexArrayID);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &iden[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(VertexArrayID2);

	Model = glm::mat4(1.0f);
	Model = glm::rotate(Model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::scale(Model, glm::vec3(1.0f, 10.0f, 1.0f));

	for (int i = -10; i <= 10; i++)
	{
		mvp = Projection * View * glm::translate(glm::mat4(1.0f), glm::vec3((float)i*0.5, 0.0f, -5.0f)) * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	Model = glm::mat4(1.0f);
	Model = glm::rotate(Model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Model = glm::scale(Model, glm::vec3(1.0f, 10.0f, 1.0f));

	for (int i = -10; i <= 10; i++)
	{
		mvp = Projection * View * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, (float)i*0.5)) * Model;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glDrawArrays(GL_LINES, 0, 2);
	}

	

	

	glutSwapBuffers();
}


void init_shader(void)
{
	static const GLfloat g_vertex_buffer_data[] = {
		-0.0f, -0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	static const GLfloat g_vertex_buffer_data2[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

	};

	programID = LoadShaders("ver.glsl", "frag.glsl");

	MatrixID = glGetUniformLocation(programID, "trans");
	vertexLoc = glGetAttribLocation(programID, "position");

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	

	glGenVertexArrays(1, &VertexArrayID2);
	glBindVertexArray(VertexArrayID2);
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data2), g_vertex_buffer_data2, GL_STATIC_DRAW);



	glBindVertexArray(VertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(VertexArrayID2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
}


void loadobjfile(string filename)
{
	objl::Loader loader;
	bool loadsuccess = loader.LoadFile(filename+".obj");
	if (loadsuccess)
	{
		// Create/Open e1Out.txt
		std::ofstream file(filename+"_data.txt");

		// Go through each loaded mesh and out its contents
		for (int i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = loader.LoadedMeshes[i];

			// Print Mesh Name
			file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

			// Print Vertices
			file << "Vertices:\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				file << "V" << j << ": " <<
					"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
					"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
					"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";
			}

			// Print Indices
			file << "Indices:\n";

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				file << "T" << j / 3 << ": " << curMesh.Indices[j] << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
			}

			// Print Material
			file << "Material: " << curMesh.MeshMaterial.name << "\n";
			file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
			file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
			file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
			file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
			file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
			file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
			file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
			file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
			file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
			file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
			file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
			file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";

			// Leave a space to separate from the next mesh
			file << "\n";
		}

		// Close File
		file.close();

	}
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(400, 400);
	glutInitWindowSize(800, 800);
	cout << glutCreateWindow("Hello OpenGL") << endl;

	
	loadobjfile("OBJ files/M1911");
	loadobjfile("OBJ files/dummy_obj");
	loadobjfile("OBJ files/dummy_obj_red");
	loadobjfile("OBJ files/Skeleton");
	

	glutReshapeFunc(reshape1);
	glutDisplayFunc(display1);
	glutIdleFunc(idle1);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create and compile our GLSL program from the shaders

	init_shader();
	

	

	glutMainLoop();


	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	glDetachShader(programID, VertexShaderID);
	glDetachShader(programID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return 0;
}

