#pragma once
#include "CHierModel.h"
class CSinglePolygon
{
	unique_ptr<CHierModel> V_Hier;
public:
	CSinglePolygon(SVerArray draw, T4Int C);
	~CSinglePolygon(void);
	void M_SetTrans(glm::mat4 m);
	void M_Draw(glm::mat4 ctm, T4Int color) { T4Double p; for (int i = 0; i < 4; i++) p[i] = color[i]/255.0; V_Hier->M_Draw(ctm, p); }
};

