#pragma once
#include "CHierModel.h"
class CSinglePolygon
{
	unique_ptr<CHierModel> V_Hier;
public:
	CSinglePolygon(GLuint draw, T4Int C);
	~CSinglePolygon(void);
	void M_SetTrans(glm::mat4 m);
	void M_Draw(glm::mat4 ctm) { V_Hier->M_Draw(ctm); }
};

