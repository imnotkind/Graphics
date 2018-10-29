#pragma once
#include "CHandler.h"
#include <stack>

struct SHierModelNode
{
	Type_Not_Determined draw;
	Type_Not_Determined trans;

	SHierModelNode* left_child;
	SHierModelNode* right_sibling;
};
class CHierModel :
	public CHandler
{
	stack<Type_Not_Determined> V_MatrixStack;

	SHierModelNode V_Root;
	void M_Release(void);

	void M_Draw_Rec(SHierModelNode* node, Type_Not_Determined CTM);
public:
	void M_Draw(Type_Not_Determined CTM);
	CHierModel(const SHierModelNode& root) : V_Root(root) {}
	~CHierModel();
};

