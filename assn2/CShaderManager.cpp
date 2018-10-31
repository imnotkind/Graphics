#include "CShaderManager.h"
#include "StringHelper.h"


CShaderManager::CShaderManager(string config_path)
{
	//parse well and
	map<string, string> VerShaderPaths;
	map<string, string> FragShaderPaths;
	map<string, string> PolygonData;
	map<string, string> ProgramData;
	string Line = "";


	ifstream is(config_path.c_str(), std::ios::in);
	if (is.is_open())
	{
		while (getline(is, Line))
		{
			if(Line == "%vs_start")
			{
				getline(is, Line);
				while (Line != "%vs_end")
				{
					M_ParseData(Line, VerShaderPaths, 0);
					getline(is, Line);
				}
			}

			if (Line == "%fs_start")
			{
				getline(is, Line);
				while (Line != "%fs_end")
				{
					M_ParseData(Line, FragShaderPaths, 0);
					getline(is, Line);
				}
			}

			if (Line == "%polygon_start")
			{
				getline(is, Line);
				while (Line != "%polygon_end")
				{
					
					M_ParseData(Line, PolygonData, 1);
					getline(is, Line);
				}
			}

			if (Line == "%program_start")
			{
				getline(is, Line);
				while (Line != "%program_end")
				{
					
					M_ParseData(Line, ProgramData, 1);
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
		GLuint u = x.second;
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

void CShaderManager::M_LoadPolygon(string data, string name)
{
	//parse data string to float array
	size_t start = data.find("{");
	size_t end = data.find("}", start + 1);
	data = data.substr(start + 1, end - start - 1);

	vector<size_t> positions;
	size_t pos = data.find(",");
	while (pos != string::npos)
	{
		positions.push_back(pos);
		pos = data.find(",", pos + 1);
	}

	int n = positions.size()+1;

	float * arr = (float *)malloc(n*sizeof(float));

	int i = 0;
	size_t prev = 0;
	for (auto p : positions)
	{
		arr[i] = atof(data.substr(prev,p-prev).c_str());
		i++;
		prev = p+1;
	}
	arr[i] = atof(data.substr(prev, string::npos).c_str());

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


void CShaderManager::M_ParseData(string line, map<string,string>& t, int mode)
{
	if (mode == 0) //direct
	{
		vector<string> l = StringHelper::M_split(line, ':');
		if (l.size() != 2)
			return;
		string name = StringHelper::M_trim(l[0]);
		string path = StringHelper::M_trim(l[1]);
		t[name] = path;
	}
	

	if (mode == 1) //indirect
	{
		ifstream is(line.c_str(), std::ios::in);
		if (is.is_open())
		{
			string subLine = "";
			while (getline(is, subLine))
			{
				vector<string> l = StringHelper::M_split(subLine, ':');

				if (l.size() != 2)
				{
					is.close();
					return;
				}
				string name = StringHelper::M_trim(l[0]);
				string data = StringHelper::M_trim(l[1]);

				//invalid string error catch
				t[name] = data;
			}
			is.close();
		}
		else CError("file " + line + " not found.", true);
	}
}


