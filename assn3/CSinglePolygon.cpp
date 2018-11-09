#include "CSinglePolygon.h"



CSinglePolygon::CSinglePolygon(SVerArray draw, T4Int C)
{
	SHierModelNode p;
	p.draw = draw;
	p.trans = glm::mat4(1.0f);
	p.port = 0;
	for(int i = 0; i < 4; i++) p.color[i] = C[i]/255.0;

	vector<SHierModelNode> s; s.push_back(p);
	V_Hier.reset(new CHierModel(s));
}

CSinglePolygon::~CSinglePolygon()
{
}

void CSinglePolygon::M_SetTrans(glm::mat4 m)
{
	V_Hier->M_RegisterTrans2(0, m);
}