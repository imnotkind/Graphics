#pragma once
#include "CHandler.h"

#include <fstream>
#include <sstream>

class CShaderManager :
	public CHandler
{

	map<string, GLuint> V_Programs;
	map<string, GLuint> V_VerShaders;
	map<string, GLuint> V_FragShaders;
	map<string, GLuint> V_Polygons;
	map<string, GLuint> V_Buffers;

	void M_LoadShader(string path, string name, int type);
	void M_LoadPolygon(string data, string name);
	void M_LoadProgram(string name, string ver, string frag);

	GLuint V_CurrentProgram;

	static CShaderManager* Instance;
	CShaderManager(string config_path);
	~CShaderManager();
public:
	GLuint M_GetPolygon(string s) { return V_Polygons[s]; }
	void M_UseProgram(string name) {V_CurrentProgram = V_Programs[name]; glUseProgram(V_CurrentProgram);}
	GLuint M_GetProgram(void) { return V_CurrentProgram; }

	static CShaderManager* getInstance(void)
	{
		if (Instance == NULL)Instance = new CShaderManager("config.txt");
		return Instance;
	}
	static void freeInstance(void)
	{
		if (Instance) delete Instance;
	}
};

