#include "CGraphics.h"

void CGraphics::M_SetupHieraModels(void)
{
	auto p = CShaderManager::getInstance();
	V_BasicPolygons["rect"] = shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("rect")));
}