#include "CGraphics.h"

void CGraphics::M_SetupHieraModels(void)
{
	V_BasicPolygons["Rect"] = shared_ptr<CSinglePolygon>(new CSinglePolygon(0));
}