#pragma once
#include "CHandler.h"
#include "CShaderManager.h"
#include <stack>

struct SHierModelNode
{
	SVerArray draw;
	glm::mat4 trans;
	glm::mat4 trans_s; // no inheritance

	int port;
	T4Double color;

	int left_child;
	int right_sibling;

	SHierModelNode() {
		draw.num = 0; trans = glm::mat4(1.0); trans_s = glm::mat4(1.0);  port = -1; color.set(1.0, 1.0, 1.0, 1.0);
	left_child = -1; right_sibling = -1;}
};
class CHierModel :
	public CHandler
{
protected:
	GLuint V_Program;

	map<int, glm::mat4> V_Trans2; //transforms applied after hiera transform, according to port. (for animation)
	stack<glm::mat4> V_MatrixStack;
	vector<SHierModelNode> V_Tree;
	void M_Release(void);

	void M_Draw_Rec(int index, glm::mat4 CTM);

public:
	void M_RegisterTrans2(int port, glm::mat4 t);
	void M_Draw(glm::mat4 CTM);

	CHierModel(vector<SHierModelNode>& t) { V_Tree = t; }

	virtual ~CHierModel();
};

