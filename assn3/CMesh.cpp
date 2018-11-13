#include "CMesh.h"


//path of obj file and metadata file
CMesh::CMesh(string obj, string meta)
{
	//obj load
	objl::Loader loader;
	loader.LoadFile(obj);
	V_LoadedMeshes = loader.LoadedMeshes;

	//metadata load
	string Line = "";

	ifstream is((meta).c_str(), std::ios::in);
	if (is.is_open())
	{
		getline(is, Line);
		if (Line == "%group_number")
		{
			getline(is, Line);
			V_group_num = atoi(Line.c_str());
			if (V_group_num != V_LoadedMeshes.size())
				CError("Incorrect data format", true);
		}
		

		while (getline(is, Line))
		{
			if (Line == "%group_info")
			{
				for (int i = 0; i < V_group_num; i++)
				{
					getline(is, Line);
					vector<string> l = StringHelper::M_split(Line, ',');
					set<int> il;
					for (auto s : l)
					{
						il.insert(atoi(s.c_str()));
					}
					V_group_info.push_back(il);
				}
			}

			if (Line == "%group_translation")
			{
				for (int i = 0; i < V_group_num; i++)
				{
					getline(is, Line);
					vector<string> l = StringHelper::M_split(Line, ',');
					if (l.size() != 3)
						CError("Incorrect data format", true);

					glm::vec3 v(
						atof(l[0].c_str()), 
						atof(l[1].c_str()), 
						atof(l[2].c_str())
					);

					V_group_translation.push_back(v);
				}
			}

			if (Line == "%group_rotation")
			{
				for (int i = 0; i < V_group_num; i++)
				{
					getline(is, Line);
					vector<string> l = StringHelper::M_split(Line, ',');
					if (l.size() != 4)
						CError("Incorrect data format", true);

					glm::vec3 v(
						atof(l[1].c_str()),
						atof(l[2].c_str()),
						atof(l[3].c_str())
					);

					V_group_rotation.push_back(pair<float,glm::vec3>(atof(l[0].c_str()),v));
				}
			}

			if (Line == "%parent_info")
			{
				getline(is, Line);
				vector<string> l = StringHelper::M_split(Line, ',');
				if (l.size() != V_group_num)
					CError("Incorrect data format", true);

				for (string s : l)
				{
					V_parent_info.push_back(atoi(s.c_str()));
				}
			}

			if (Line == "%parent_rotation")
			{
				for (int i = 0; i < V_group_num; i++)
				{
					getline(is, Line);
					vector<string> l = StringHelper::M_split(Line, ',');
					if (l.size() != 4)
						CError("Incorrect data format", true);

					glm::vec3 v(
						atof(l[1].c_str()),
						atof(l[2].c_str()),
						atof(l[3].c_str())
					);

					V_parent_rotation.push_back(pair<float, glm::vec3>(atof(l[0].c_str()), v));
				}
			}

			if (Line == "%parent_translation")
			{
				for (int i = 0; i < V_group_num; i++)
				{
					getline(is, Line);
					vector<string> l = StringHelper::M_split(Line, ',');
					if (l.size() != 3)
						CError("Incorrect data format", true);

					glm::vec3 v(
						atof(l[0].c_str()),
						atof(l[1].c_str()),
						atof(l[2].c_str())
					);

					V_parent_translation.push_back(v);
				}
			}
		}
		is.close();
	}
	else CError("Config file " + meta + " not found.", true);

	//create V_Model


	Sleep(3000);
	
}

