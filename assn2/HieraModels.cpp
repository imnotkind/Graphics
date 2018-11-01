#include "CGraphics.h"

void CGraphics::M_SetupHieraModels(void)
{
	auto p = CShaderManager::getInstance();
	V_BasicPolygons["triangle"] = 
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("triangle"), T4Int(255, 0, 255, 255)));
	V_BasicPolygons["square"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("square"), T4Int(255, 0, 255, 255)));
	V_BasicPolygons["pentagon"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("pentagon"), T4Int(255, 0, 255, 255)));
	V_BasicPolygons["star"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("star"), T4Int(255, 204, 0, 255)));
	V_BasicPolygons["circle"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("circle"), T4Int(255, 0, 255, 255)));
	V_BasicPolygons["A"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("A"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["B"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("B"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["C"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("C"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["D"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("D"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["E"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("E"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["F"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("F"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["G"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("G"), T4Int(0, 255, 0, 255)));
	V_BasicPolygons["diamond"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("diamond"), T4Int(30, 30, 30, 255)));
	V_BasicPolygons["rectangle"] =
		shared_ptr<CSinglePolygon>(new CSinglePolygon(p->M_GetPolygon("rectangle"), T4Int(90, 90, 90, 255)));

	SHierModelNode body;
	body.color = T4Double(1.0, 0.5, 0.3, 1.0);
	body.draw = V_SM->M_GetPolygon("square");
	body.port = 0;
	body.trans_s = glm::scale(body.trans, glm::vec3(0.5, 1.0, 1.0));

	SHierModelNode head;
	head.color = T4Double(0.0, 0.5, 0.3, 1.0);
	head.draw = V_SM->M_GetPolygon("circle");
	head.port = 0;
	head.trans_s = glm::scale(head.trans, glm::vec3(0.3, 0.5, 1.0));
	head.trans = glm::translate(head.trans, glm::vec3(0.0, 1.5, 0.0));

	//arms
	SHierModelNode larm1;
	larm1.color = T4Double(1.0, 1.0, 0.3, 1.0);
	larm1.draw = V_SM->M_GetPolygon("square");
	larm1.port = 1;
	larm1.trans = glm::translate(larm1.trans, glm::vec3(-0.5, 0.8, 0.0));
	larm1.trans_s = glm::scale(larm1.trans_s, glm::vec3(0.5, 0.2, 1.0));
	larm1.trans_s = glm::translate(larm1.trans_s, glm::vec3(-1.0, 0.0, 0.0));

	SHierModelNode larm2;
	larm2.color = T4Double(1.0, 1.0, 0.3, 1.0);
	larm2.draw = V_SM->M_GetPolygon("square");
	larm2.port = 1;
	larm2.trans = glm::translate(larm2.trans, glm::vec3(-1.0, 0.0, 0.0));
	larm2.trans_s = glm::scale(larm2.trans_s, glm::vec3(0.6, 0.15, 1.0));
	larm2.trans_s = glm::translate(larm2.trans_s, glm::vec3(-1.0, 0.0, 0.0));

	SHierModelNode rarm1;
	rarm1.color = T4Double(1.0, 1.0, 0.3, 1.0);
	rarm1.draw = V_SM->M_GetPolygon("square");
	rarm1.port = 2;
	rarm1.trans = glm::translate(rarm1.trans, glm::vec3(0.5, 0.8, 0.0));
	rarm1.trans_s = glm::scale(rarm1.trans_s, glm::vec3(0.5, 0.2, 1.0));
	rarm1.trans_s = glm::translate(rarm1.trans_s, glm::vec3(1.0, 0.0, 0.0));

	SHierModelNode rarm2;
	rarm2.color = T4Double(1.0, 1.0, 0.3, 1.0);
	rarm2.draw = V_SM->M_GetPolygon("square");
	rarm2.port = 2;
	rarm2.trans = glm::translate(rarm2.trans, glm::vec3(1.0, 0.0, 0.0));
	rarm2.trans_s = glm::scale(rarm2.trans_s, glm::vec3(0.6, 0.15, 1.0));
	rarm2.trans_s = glm::translate(rarm2.trans_s, glm::vec3(1.0, 0.0, 0.0));


	//legs
	SHierModelNode lleg1;
	lleg1.color = T4Double(1.0, 1.0, 0.3, 1.0);
	lleg1.draw = V_SM->M_GetPolygon("square");
	lleg1.port = 1;
	lleg1.trans = glm::translate(lleg1.trans, glm::vec3(-0.25, -1.0, 0.0));
	lleg1.trans = glm::rotate(lleg1.trans, float(DTR(-10)), glm::vec3(0.0, 0.0, 1.0));
	lleg1.trans_s = glm::scale(lleg1.trans_s, glm::vec3(0.25, 0.6, 1.0));
	lleg1.trans_s = glm::translate(lleg1.trans_s, glm::vec3(0.0, -1.0, 0.0));

	SHierModelNode lleg2;
	lleg2.color = T4Double(1.0, 1.0, 0.3, 1.0);
	lleg2.draw = V_SM->M_GetPolygon("square");
	lleg2.port = 1;
	lleg2.trans = glm::translate(lleg2.trans, glm::vec3(0.0, -1.2, 0.0));
	lleg2.trans_s = glm::scale(lleg2.trans_s, glm::vec3(0.2, 0.5, 1.0));
	lleg2.trans_s = glm::translate(lleg2.trans_s, glm::vec3(0.0, -1.0, 0.0));

	SHierModelNode rleg1;
	rleg1.color = T4Double(1.0, 1.0, 0.3, 1.0);
	rleg1.draw = V_SM->M_GetPolygon("square");
	rleg1.port = 1;
	rleg1.trans = glm::translate(rleg1.trans, glm::vec3(0.25, -1.0, 0.0));
	rleg1.trans = glm::rotate(rleg1.trans, float(DTR(10)), glm::vec3(0.0, 0.0, 1.0));
	rleg1.trans_s = glm::scale(rleg1.trans_s, glm::vec3(0.25, 0.6, 1.0));
	rleg1.trans_s = glm::translate(rleg1.trans_s, glm::vec3(0.0, -1.0, 0.0));

	SHierModelNode rleg2;
	rleg2.color = T4Double(1.0, 1.0, 0.3, 1.0);
	rleg2.draw = V_SM->M_GetPolygon("square");
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
	for (int i = 0; i < E.size(); i++)
	{
		E[i].color = T4Double(1.3, 1.3, 1.0, 2.0) - E[i].color;
	}


	V_Hiers["player"] = shared_ptr<CHierModel>(new CHierModel(S));
	V_Hiers["enemy"] = shared_ptr<CHierModel>(new CHierModel(E));
}