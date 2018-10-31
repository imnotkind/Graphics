#include "CGraphics.h"

void CGraphics::M_SetupHieraModels(void)
{
	auto p = CShaderManager::getInstance();
	V_BasicPolygons["triangle"] = 
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("triangle"), T4Int(255, 0, 255, 255)));
	V_BasicPolygons["square"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("square"), T4Int(0, 0, 255, 255)));
}