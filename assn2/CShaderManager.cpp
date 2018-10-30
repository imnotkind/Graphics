#include "CShaderManager.h"



CShaderManager::CShaderManager(string config_path)
{
	//parse well and
	// iterate M_LoadShader
	// iterate M_LoadPolygon
	// itreate M_LoadProgram
}


CShaderManager::~CShaderManager()
{
	
}


void CShaderManager::M_LoadShader(string path, string name, int type)
{
	GLuint id = glCreateShader(type);

	string code;
	ifstream is(path.c_str(), std::ios::in);
	if (is.is_open()) 
	{
		std::string Line = "";
		while (getline(is, Line)) code += "\n" + Line;
		is.close();
	}
	else CError("Shader code " + path + " not found.", true);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	char const * sp = code.c_str();
	glShaderSource(id, 1, &sp, NULL);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> error_msg(InfoLogLength + 1);
		glGetShaderInfoLog(id, InfoLogLength, NULL, &error_msg[0]);
		printf("%s\n", &error_msg[0]);
		CError("Shader code " + path + " can't be compoiled", true);
	}
	
	if (type == GL_VERTEX_SHADER)
		V_VerShaders[name] = id;
	else
		V_FragShaders[name] = id;

}

void CShaderManager::M_LoadPolygon(string path, string name)
{
	//parse this!!!
	int n = 0;
	float * arr = NULL;
	//parse this!!!

	GLuint vbid;
	GLuint vaid;

	glGenVertexArrays(1, &vaid);
	glBindVertexArray(vaid);
	glGenBuffers(1, &vbid);
	glBindBuffer(GL_ARRAY_BUFFER, vbid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, arr, GL_STATIC_DRAW);

	V_Polygons[name] = vaid;
	V_Buffers[name] = vbid;
}
void CShaderManager::M_LoadProgram(string name, string ver, string frag)
{
	GLuint id = glCreateProgram();
	glAttachShader(id, V_VerShaders[ver]);
	glAttachShader(id, V_FragShaders[frag]);

	glBindFragDataLocation(id, 0, "color");
	glLinkProgram(id);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	glGetProgramiv(id, GL_LINK_STATUS, &Result);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		vector<char> error_msg(InfoLogLength + 1);
		glGetProgramInfoLog(id, InfoLogLength, NULL, &error_msg[0]);
		printf("%s\n", &error_msg[0]);
		CError("Program " + name + " can't be linked", true);
	}

	V_Programs[name] = id;
}