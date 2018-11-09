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

	SHierModelNode body;
	body.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 0.5, 0.3, 1.0))));
	body.port = 0;
	body.trans_s = glm::scale(body.trans, glm::vec3(0.5, 1.0, 1.0));
	body.trans = glm::rotate(body.trans, float(DTR(-90)), glm::vec3(0.0, 0.0, 1.0));

	SHierModelNode head;
	head.draw.reset(new CDrawing(temptemp("circle", T4Double(0.0, 0.5, 0.3, 1.0))));
	head.port = 0;
	head.trans_s = glm::scale(head.trans, glm::vec3(0.3, 0.5, 1.0));
	head.trans = glm::translate(head.trans, glm::vec3(0.0, 1.5, 0.0));

	//arms
	SHierModelNode larm1;
	larm1.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	larm1.port = 1;
	larm1.trans = glm::translate(larm1.trans, glm::vec3(-0.5, 0.8, 0.0));
	larm1.trans_s = glm::scale(larm1.trans_s, glm::vec3(0.5, 0.2, 1.0));
	larm1.trans_s = glm::translate(larm1.trans_s, glm::vec3(-1.0, 0.0, 0.0));

	SHierModelNode larm2;
	larm2.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	larm2.port = 1;
	larm2.trans = glm::translate(larm2.trans, glm::vec3(-1.0, 0.0, 0.0));
	larm2.trans_s = glm::scale(larm2.trans_s, glm::vec3(0.6, 0.15, 1.0));
	larm2.trans_s = glm::translate(larm2.trans_s, glm::vec3(-1.0, 0.0, 0.0));

	SHierModelNode rarm1;
	rarm1.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	rarm1.port = 2;
	rarm1.trans = glm::translate(rarm1.trans, glm::vec3(0.5, 0.8, 0.0));
	rarm1.trans_s = glm::scale(rarm1.trans_s, glm::vec3(0.5, 0.2, 1.0));
	rarm1.trans_s = glm::translate(rarm1.trans_s, glm::vec3(1.0, 0.0, 0.0));

	SHierModelNode rarm2;
	rarm2.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	rarm2.port = 2;
	rarm2.trans = glm::translate(rarm2.trans, glm::vec3(1.0, 0.0, 0.0));
	rarm2.trans_s = glm::scale(rarm2.trans_s, glm::vec3(0.6, 0.15, 1.0));
	rarm2.trans_s = glm::translate(rarm2.trans_s, glm::vec3(1.0, 0.0, 0.0));


	//legs
	SHierModelNode lleg1;
	lleg1.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	lleg1.port = 1;
	lleg1.trans = glm::translate(lleg1.trans, glm::vec3(-0.25, -1.0, 0.0));
	lleg1.trans = glm::rotate(lleg1.trans, float(DTR(-10)), glm::vec3(0.0, 0.0, 1.0));
	lleg1.trans_s = glm::scale(lleg1.trans_s, glm::vec3(0.25, 0.6, 1.0));
	lleg1.trans_s = glm::translate(lleg1.trans_s, glm::vec3(0.0, -1.0, 0.0));

	SHierModelNode lleg2;
	lleg2.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	lleg2.port = 1;
	lleg2.trans = glm::translate(lleg2.trans, glm::vec3(0.0, -1.2, 0.0));
	lleg2.trans_s = glm::scale(lleg2.trans_s, glm::vec3(0.2, 0.5, 1.0));
	lleg2.trans_s = glm::translate(lleg2.trans_s, glm::vec3(0.0, -1.0, 0.0));

	SHierModelNode rleg1;
	rleg1.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	rleg1.port = 1;
	rleg1.trans = glm::translate(rleg1.trans, glm::vec3(0.25, -1.0, 0.0));
	rleg1.trans = glm::rotate(rleg1.trans, float(DTR(10)), glm::vec3(0.0, 0.0, 1.0));
	rleg1.trans_s = glm::scale(rleg1.trans_s, glm::vec3(0.25, 0.6, 1.0));
	rleg1.trans_s = glm::translate(rleg1.trans_s, glm::vec3(0.0, -1.0, 0.0));

	SHierModelNode rleg2;
	rleg2.draw.reset(new CDrawing(temptemp("square", T4Double(1.0, 1.0, 0.3, 1.0))));
	rleg2.port = 1;
	rleg2.trans = glm::translate(rleg2.trans, glm::vec3(0.0, -1.2, 0.0));
	rleg2.trans_s = glm::scale(rleg2.trans_s, glm::vec3(0.2, 0.5, 1.0));
	rleg2.trans_s = glm::translate(rleg2.trans_s, glm::vec3(0.0, -1.0, 0.0));

	vector<SHierModelNode> S;
	S.push_back(body);
	S.push_back(head);
	S.push_back(larm1);
	S.push_back(larm2);
	S.push_back(rarm1);
	S.push_back(rarm2);

	S.push_back(lleg1);
	S.push_back(lleg2);
	S.push_back(rleg1);
	S.push_back(rleg2);

	S[0].left_child = 1;
	S[1].right_sibling = 2;

	S[2].left_child = 3;
	S[2].right_sibling = 4;
	S[4].left_child = 5; 
	S[4].right_sibling = 6;

	S[6].left_child = 7;
	S[6].right_sibling = 8;
	S[8].left_child = 9;

	vector<SHierModelNode> E = S;

	for (SHierModelNode& x : E) //deep copy
	{
		x.draw.reset(new CDrawing(*x.draw));
	}

	for (int i = 0; i < E.size(); i++)
	{
		E[i].draw->V_Color = T4Double(1.3, 1.3, 1.0, 2.0) - E[i].draw->V_Color;
	}

	V_Models["player"] = shared_ptr<CHierModel>(new CHierModel(S));
	V_Models["enemy"] = shared_ptr<CHierModel>(new CHierModel(E));
}