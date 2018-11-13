#pragma once
#include "CHandler.h"
#include "CHierModel.h"
#include "OBJ_Loader.h"

struct SMeshGroup
{
	set<int> group_members;
	int group_parent;
	glm::vec3 trans_origin;
	pair<float, glm::vec3> rotate_origin;
	glm::vec3 trans_parent;
	pair<float, glm::vec3> rotate_parent;
	
};
typedef pair<int, vector<int>> treenode;
class CMesh :
	public CHandler
{
	shared_ptr <CHierModel> V_Model;
	vector<SMeshGroup> V_Groups;

	string V_Name;

	void M_ConstructHierModel(void);
	void M_Rec_Construct(vector<SHierModelNode>& all, vector<treenode>& treenodes,
		int root, int sibling);
public:
	CMesh(string meta);
	shared_ptr<CHierModel> M_GetHierModel(void) { return V_Model; }
	virtual ~CMesh() {}

};

