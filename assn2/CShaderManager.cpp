#include "CShaderManager.h"



CShaderManager::CShaderManager(string config_path)
{
	//parse well and
	map<string, string> VerShaderPaths;
	map<string, string> FragShaderPaths;

	ifstream is(config_path.c_str(), std::ios::in);
	if (is.is_open())
	{
		std::string Line = "";
		getline(is, Line);
		if (Line != "%%vs")
			CError("Config file " + config_path + " invalid.", true);

		while (getline(is, Line))
		{

			if(Line == "%%fs") 
			{
				break;
			}
			else //vertexshader
			{ 
				size_t ind = Line.find(":");
				if (ind == string::npos)
				{
					continue;
				}
				string name = Line.substr(0, ind);
				string path = Line.substr(ind+1, string::npos);

				size_t start = name.find("\"");
				size_t end = name.find("\"", start + 1);
				name = name.substr(start+1, end - start - 1);

				start = path.find("\"");
				end = path.find("\"", start + 1);
				path = path.substr(start + 1, end - start - 1);

				VerShaderPaths[name] = path;

			}
			
		}

		
		while (getline(is, Line))
		{

			if (Line == "%%polygon")
			{
				// iterate M_LoadShader
				for (auto p : VerShaderPaths)
				{
					M_LoadShader(p.second, p.first, GL_VERTEX_SHADER);
				}
				for (auto p : FragShaderPaths)
				{
					M_LoadShader(p.second, p.first, GL_VERTEX_SHADER);
				}

				//polygon
				getline(is, Line);

				size_t start = Line.find("\"");
				size_t end = Line.find("\"", start + 1);
				string polygonfilepath = Line.substr(start + 1, end - start - 1);

				ifstream is2(polygonfilepath.c_str(), std::ios::in);
				if (is2.is_open())
				{
					std::string Line = "";
					while (getline(is2, Line))
					{
						size_t ind = Line.find(":");
						if (ind == string::npos)
						{
							continue;
						}
						string name = Line.substr(0, ind);
						string data = Line.substr(ind + 1, string::npos);

						// iterate M_LoadPolygon
						M_LoadPolygon(data, name);

					}
					is2.close();
				}
				else CError("Polygon file" + polygonfilepath + " not found.", true);

				break;
			}
			else //fragmentshader
			{
				size_t ind = Line.find(":");
				if (ind == string::npos)
				{
					continue;
				}
				string name = Line.substr(0, ind);
				string path = Line.substr(ind + 1, string::npos);

				size_t start = name.find("\"");
				size_t end = name.find("\"", start + 1);
				name = name.substr(start + 1, end - start - 1);

				start = path.find("\"");
				end = path.find("\"", start + 1);
				path = path.substr(start + 1, end - start - 1);

				FragShaderPaths[name] = path;
			}

		}


		while (getline(is, Line))
		{

			if (Line == "%%program") //program
			{
				getline(is, Line);

				size_t start = Line.find("\"");
				size_t end = Line.find("\"", start + 1);
				string programfilepath = Line.substr(start + 1, end - start - 1);

				ifstream is3(programfilepath.c_str(), std::ios::in);
				if (is3.is_open())
				{
					std::string Line = "";
					while (getline(is3, Line))
					{
						size_t ind = Line.find(":");
						if (ind == string::npos)
						{
							continue;
						}
						string name = Line.substr(0, ind);
						string pair = Line.substr(ind + 1, string::npos);

						size_t ind2 = pair.find(",");
						string vs = pair.substr(0, ind2);
						string fs = pair.substr(ind2 + 1, string::npos);

						size_t start = vs.find("\"");
						size_t end = vs.find("\"", start + 1);
						vs = vs.substr(start + 1, end - start - 1);

						start = fs.find("\"");
						end = fs.find("\"", start + 1);
						fs = fs.substr(start + 1, end - start - 1);


						// iterate M_LoadProgram
						M_LoadProgram(name, vs, fs);
					}
					is3.close();
				}
				else CError("Program file" + programfilepath + " not found.", true);

				break;
			}

		}
		is.close();
	}
	else CError("Config file " + config_path + " not found.", true);



	
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