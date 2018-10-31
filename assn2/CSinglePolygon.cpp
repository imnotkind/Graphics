#include "CSinglePolygon.h"



CSinglePolygon::CSinglePolygon(GLuint draw)
{
	auto p = new SHierModelNode;
	p->draw = draw;
	p->trans = glm::mat4(1.0f);
	p->port = 0;
	V_Hier.reset(new CHierModel(unique_ptr<SHierModelNode>(p)));
}

CSinglePolygon::~CSinglePolygon()
{
}

void CSinglePolygon::M_SetTrans(glm::mat4 m)
{
	V_Hier->M_RegisterTrans2(0, m);
}