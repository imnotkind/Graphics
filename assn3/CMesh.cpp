#include "CMesh.h"


//path of obj file and metadata file
CMesh::CMesh(string meta)
{
	V_Name = meta; // TODO : FIX THIS

	int V_group_num;
	vector<set<int>> V_group_info;
	vector<glm::vec3> V_group_translation;
	vector<pair<float, glm::vec3>> V_group_rotation;

	vector<int> V_parent_info;
	vector<pair<float, glm::vec3>> V_parent_rotation;
	vector<glm::vec3> V_parent_translation;


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
			//if (V_group_num != V_LoadedMeshes.size())
				//CError("Incorrect data format", true);
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

	for (int i = 0; i < V_group_num; i++)
	{
		SMeshGroup G;
		G.group_members = V_group_info[i];
		G.group_parent = V_parent_info[i];
		G.trans_origin = V_group_translation[i];
		G.rotate_origin = V_group_rotation[i];
		G.trans_parent = V_parent_translation[i];
		G.rotate_parent = V_parent_rotation[i];

		V_Groups.emplace_back(G);
	}
	
}



void CMesh::M_Rec_Construct(vector<SHierModelNode>& all, vector<treenode>& treenodes, int root, int sibling)
{
	ostringstream os;
	os << V_Name << "_" << root;

	SHierModelNode N;
	SDrawingInfo D;
	D.DrawMode = 0; // FIX THIS
	D.Global_Color.set(1.0, 0.0, 1.0, 1.0);
	D.Line_Color.set(0.0, 1.0, 0.0, 1.0);
	D.PolygonName = os.str();
	D.Program = "prg1";

	N.draw.reset(new CDrawing(D));
	N.port = 0; //TODO
	N.trans = glm::translate(glm::mat4(1.0), V_Groups[root].trans_parent);
	N.trans = glm::rotate(N.trans,V_Groups[root].rotate_parent.first, V_Groups[root].rotate_parent.second);

	treenode& t = treenodes[root];
	N.left_child = t.second.empty() ? -1 : t.second[0];
	N.right_sibling = sibling;

	all.push_back(N);
	
	for (int i = 0; i < t.second.size(); i++)
	{
		int next = i == t.second.size() - 1 ? -1 : i + 1;
		M_Rec_Construct(all, treenodes, t.second[i], next);
	}
}

void CMesh::M_ConstructHierModel(void)
{
	int N = V_Groups.size();
	vector<treenode> treenodes;
	treenodes.resize(N);

	int root;
	for (int i = 0; i < N; i++)
	{
		treenodes[i].first = V_Groups[i].group_parent;
		if (V_Groups[i].group_parent == -1)
		{
			root = i;
			continue;
		}
		treenodes[V_Groups[i].group_parent].second.push_back(i);
	}
	vector<SHierModelNode> all;
	M_Rec_Construct(all, treenodes, root, -1);
	V_Model.reset(new CHierModel(all));
}