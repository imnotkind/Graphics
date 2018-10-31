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
void CHierModel::M_Draw_Rec(int index, glm::mat4 CTM)
{
	V_MatrixStack.push(CTM);
	SHierModelNode& node = V_Tree[index];

	//not exist -> identity
	glm::mat4 trans2 = V_Trans2.find(node.port) == V_Trans2.end() ? glm::mat4(1.0f) : V_Trans2[node.port];
	CTM = CTM * node.trans * trans2;

	auto temp = CTM * node.trans_s;

	glBindVertexArray(node.draw.aindex);
	GLuint p = glGetUniformLocation(V_Program, "trans");
	GLuint q = glGetUniformLocation(V_Program, "vicolor");
	glUniformMatrix4fv(p, 1, GL_FALSE, &temp[0][0]);
	float col[4]; 
	for(int i = 0; i< 4; i++) col[i] = node.color[i]; 
	glUniform4fv(q, 1, col);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, node.draw.num);

	if (node.left_child != -1) M_Draw_Rec(node.left_child, CTM);
	CTM = V_MatrixStack.top();  V_MatrixStack.pop();
	if (node.right_sibling != -1) M_Draw_Rec(node.right_sibling, CTM);
}

void CHierModel::M_Draw(glm::mat4 CTM)
{
	auto s = CShaderManager::getInstance();
	V_Program = s->M_GetProgram();
	M_Draw_Rec(0, CTM);
}