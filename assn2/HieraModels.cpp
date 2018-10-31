#include "CGraphics.h"

void CGraphics::M_SetupHieraModels(void)
{
	auto p = CShaderManager::getInstance();
	V_BasicPolygons["pol1"] = shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("pol1")));
}