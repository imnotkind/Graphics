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
	void M_LoadPolygon(string path, string name);
	void M_LoadProgram(string name, string ver, string frag);
public:
	CShaderManager(string config_path);
	virtual ~CShaderManager();
};

