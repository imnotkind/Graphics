#include "CShaderManager.h"


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
void CShaderManager::M_LoadMesh(string path)
{
	objl::Loader loader;
	loader.LoadFile(path);
	auto mesh = loader.LoadedMeshes;
	for (auto m : mesh)
	{
		m.Indices.size();
		for (auto i : m.Indices)
		{

		}
	}
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

	int n = positions.size() + 1;

	float * arr = (float *)malloc(n * sizeof(float));

	int i = 0;
	size_t prev = 0;
	for (auto p : positions)
	{
		arr[i] = atof(data.substr(prev, p - prev).c_str());
		i++;
		prev = p + 1;
	}
	arr[i] = atof(data.substr(prev, string::npos).c_str());

	GLuint vbid;
	GLuint vaid;

	glGenVertexArrays(1, &vaid);
	glBindVertexArray(vaid);
	glGenBuffers(1, &vbid);
	glBindBuffer(GL_ARRAY_BUFFER, vbid); // attach to currently bound vertex array
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n, arr, GL_STATIC_DRAW);

	SVerArray va; va.num = n / 4; va.aindex = vaid;
	V_Polygons[name] = va;
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
	auto vl = glGetAttribLocation(id, "position");
	for (auto p : V_Polygons)
	{
		auto a = p.second;
		auto b = V_Buffers[p.first];

		glBindVertexArray(a.aindex);
		glBindBuffer(GL_ARRAY_BUFFER, b);

		glEnableVertexAttribArray(vl);
		glVertexAttribPointer(vl, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

}


void CShaderManager::M_ParseData(string res_path, string line, map<string, string>& t, int mode)
{
	if (mode == 0) //direct
	{
		vector<string> l = StringHelper::M_split(line, ':');
		if (l.size() != 2)
			return;
		string name = StringHelper::M_trim(l[0]);
		string path = StringHelper::M_trim(l[1]);
		t[name] = res_path + path;
	}


	if (mode == 1) //indirect
	{
		ifstream is((res_path+line).c_str(), std::ios::in);
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


