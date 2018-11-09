#pragma once
#include "CHandler.h"

#include <fstream>
#include <sstream>

struct SVerArray
{
	GLuint aindex;
	int num;
};
class CShaderManager :
	public CHandler
{

	map<string, GLuint> V_Programs;
	map<string, GLuint> V_VerShaders;
	map<string, GLuint> V_FragShaders;
	map<string, SVerArray> V_Polygons;
	map<string, GLuint> V_Buffers;

	void M_LoadShader(string path, string name, int type);
	void M_LoadPolygon(string data, string name);
	void M_LoadProgram(string name, string ver, string frag);

	void M_ParseData(string respath, string line, map<string, string>& t, int mode);


	GLuint V_CurrentProgram;

	static CShaderManager* Instance;
	CShaderManager(string config_path);
	CShaderManager(string res_path, string config_path);
	~CShaderManager();
public:
	SVerArray M_GetPolygon(string s) { return V_Polygons[s]; }
	const map<string, SVerArray>& M_GetPolygonList(void) { return V_Polygons; }

	void M_UseProgram(string name);
	GLuint M_GetProgram(void) { return V_CurrentProgram; }

	static CShaderManager* getInstance(void)
	{
		if (Instance == NULL)Instance = new CShaderManager("resource/","config.txt");
		return Instance;
	}
	static void freeInstance(void)
	{
		if (Instance) delete Instance;
	}
};

