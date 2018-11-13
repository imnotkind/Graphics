#pragma once
#include "CHandler.h"
#include "CHierModel.h"
class CMesh :
	public CHandler
{
	shared_ptr <CHierModel> V_Model;
	int V_group_num;
	vector<set<int>> V_group_info;
	vector<glm::vec3> V_group_translation;
	vector<pair<float, glm::vec3>> V_group_rotation;
	vector<int> V_parent_info;
	vector<pair<float, glm::vec3>> V_parent_rotation;
	vector<glm::vec3> V_parent_translation;
public:
	CMesh(string obj, string meta);
	shared_ptr<CHierModel> M_GetHierModel(void) { return V_Model; }
	virtual ~CMesh() {}

};

