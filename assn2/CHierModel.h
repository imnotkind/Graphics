#pragma once
#include "CHandler.h"
#include "CShaderManager.h"
#include <stack>

struct SHierModelNode
{
	GLuint draw;
	glm::mat4 trans;
	unique_ptr<SHierModelNode> left_child;
	unique_ptr<SHierModelNode> right_sibling;
	int port;
};
class CHierModel :
	public CHandler
{
protected:
	GLuint V_Program;

	map<int, glm::mat4> V_Trans2; //transforms applied after hiera transform, according to port. (for animation)
	stack<glm::mat4> V_MatrixStack;
	unique_ptr<SHierModelNode> V_Root;
	void M_Release(void);

	void M_Draw_Rec(const unique_ptr<SHierModelNode>& node, glm::mat4 CTM);

public:
	void M_RegisterTrans2(int port, glm::mat4 t);
	void M_Draw(glm::mat4 CTM);

	CHierModel(unique_ptr<SHierModelNode>&& root) { V_Root = move(root); }

	virtual ~CHierModel();
};

