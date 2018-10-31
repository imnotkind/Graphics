#pragma once
#include "CHandler.h"
#include <stack>

struct SHierModelNode
{
	GLuint draw;
	glm::mat4 trans;

	unique_ptr<SHierModelNode> left_child;
	unique_ptr<SHierModelNode> right_sibling;
};
class CHierModel :
	public CHandler
{
	stack<Type_Not_Determined> V_MatrixStack;

	unique_ptr<SHierModelNode> V_Root;
	void M_Release(void);

	void M_Draw_Rec(const unique_ptr<SHierModelNode>& node, Type_Not_Determined CTM);
public:
	void M_Draw(Type_Not_Determined CTM);
	CHierModel(unique_ptr<SHierModelNode>& root) { V_Root = move(root); }
	~CHierModel();
};

