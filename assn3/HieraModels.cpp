#include "CGraphics.h"


SDrawingInfo temptemp(string s, T4Double c)
{
	SDrawingInfo d;
	d.DrawMode = 3;
	d.Global_Color = c;
	d.PolygonName = s;
	d.Program = "prg1";
	d.Line_Color.set(1.0, 0.0, 0.0, 1.0);

	return d;
}

void CGraphics::M_SetupHieraModels(void)
{
	auto p = CShaderManager::getInstance();

	for (auto k : p->M_GetPolygonList())
	{
		SDrawingInfo di;
		di.DrawMode = 2;
		di.Global_Color = T4Double(1.0, 1.0, 1.0, 1.0);
		di.PolygonName = k.first;
		di.Program = "prg1";

		SHierModelNode node;
		node.draw.reset(new CDrawing(di));
		V_Models[k.first] = shared_ptr<CHierModel>(new CHierModel(node));
	}

}