#include "CShaderManager.h"
#include "StringHelper.h"


CShaderManager::CShaderManager(string res_path,string config_path)
{
	//parse well and
	map<string, string> VerShaderPaths;
	map<string, string> FragShaderPaths;
	map<string, string> PolygonData;
	map<string, string> ProgramData;
	string Line = "";

	ifstream is((res_path+config_path).c_str(), std::ios::in);
	if (is.is_open())
	{
		while (getline(is, Line))
		{
			if(Line == "%vs_start")
			{
				getline(is, Line);
				while (Line != "%vs_end")
				{
					M_ParseData(res_path, Line, VerShaderPaths, 0);
					getline(is, Line);
				}
			}

			if (Line == "%fs_start")
			{
				getline(is, Line);
				while (Line != "%fs_end")
				{
					M_ParseData(res_path, Line, FragShaderPaths, 0);
					getline(is, Line);
				}
			}

			if (Line == "%polygon_start")
			{
				getline(is, Line);
				while (Line != "%polygon_end")
				{
					
					M_ParseData(res_path, Line, PolygonData, 1);
					getline(is, Line);
				}
			}

			if (Line == "%program_start")
			{
				getline(is, Line);
				while (Line != "%program_end")
				{
					
					M_ParseData(res_path, Line, ProgramData, 1);
					getline(is, Line);
				}
			}
		}
		is.close();
	}
	else CError("Config file " + config_path + " not found.", true);

	for (auto p : VerShaderPaths)
	{
		M_LoadShader(p.second, p.first, GL_VERTEX_SHADER);
	}
	for (auto p : FragShaderPaths)
	{
		M_LoadShader(p.second, p.first, GL_FRAGMENT_SHADER);
	}
	for(auto p : PolygonData)
	{
		M_LoadPolygon(p.second, p.first);
	}
	for (auto p : ProgramData)
	{
		vector<string> v = StringHelper::M_split(p.second, ',');

		M_LoadProgram(p.first, StringHelper::M_trim(v[0]), StringHelper::M_trim(v[1]));
	}
}

CShaderManager::~CShaderManager()
{
	for (auto x : V_Polygons)
	{
		GLuint u = x.second.aindex;
		glDeleteVertexArrays(1, &u);
	}
	for (auto x : V_Buffers)
	{
		GLuint u = x.second;
		glDeleteBuffers(1, &u);
	}
	for (auto x : V_Programs) glDeleteProgram(x.second);
	for (auto x : V_VerShaders) glDeleteShader(x.second);
	for (auto x : V_FragShaders) glDeleteShader(x.second);

	freeInstance();

}


void CShaderManager::M_UseProgram(string name)
{ 
	if (V_CurrentProgram == V_Programs[name]) return; // no redundant binding
	V_CurrentProgram = V_Programs[name];
	glUseProgram(V_CurrentProgram); 
}