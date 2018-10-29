#include "CHierModel.h"



CHierModel::~CHierModel()
{
	M_Release();
}

void CHierModel::M_Release(void)
{

}

void CHierModel::M_Draw_Rec(SHierModelNode* node, Type_Not_Determined CTM)
{
	V_MatrixStack.push(CTM);
	CTM = CTM * node->trans;
	node->draw; //call draw array or something
	if (node->left_child) M_Draw_Rec(node->left_child, CTM);

	CTM = V_MatrixStack.top();  V_MatrixStack.pop();

	if (node->right_sibling) M_Draw_Rec(node->right_sibling, CTM);
}

void CHierModel::M_Draw(Type_Not_Determined CTM)
{
	M_Draw_Rec(&V_Root, CTM);
}