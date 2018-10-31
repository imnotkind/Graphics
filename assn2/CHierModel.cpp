#include "CHierModel.h"



CHierModel::~CHierModel()
{
	M_Release();
}

void CHierModel::M_Release(void)
{

}
void CHierModel::M_RegisterTrans2(int port, glm::mat4 t)
{
	V_Trans2[port] = t;
}
void CHierModel::M_Draw_Rec(const unique_ptr<SHierModelNode>& node, glm::mat4 CTM)
{
	V_MatrixStack.push(CTM);

	//not exist -> identity
	glm::mat4 trans2 = V_Trans2.find(node->port) == V_Trans2.end() ? glm::mat4(1.0f) : V_Trans2[node->port];
	CTM = CTM * trans2 * node->trans;

	GLuint p = glGetAttribLocation(V_Program, "position");
	GLuint q = glGetUniformLocation(V_Program, "trans");

	glEnableVertexAttribArray(p);
	glVertexAttribPointer(p, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(node->draw);

	glUniformMatrix4fv(q, 1, GL_FALSE, &CTM[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	if (node->left_child) M_Draw_Rec(node->left_child, CTM);
	CTM = V_MatrixStack.top();  V_MatrixStack.pop();
	if (node->right_sibling) M_Draw_Rec(node->right_sibling, CTM);
}

void CHierModel::M_Draw(glm::mat4 CTM)
{
	auto s = CShaderManager::getInstance();
	V_Program = s->M_GetProgram();
	M_Draw_Rec(V_Root, CTM);
}