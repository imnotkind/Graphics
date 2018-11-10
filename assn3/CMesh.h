#pragma once
#include "CHandler.h"
#include "CHierModel.h"
class CMesh :
	public CHandler
{
	shared_ptr <CHierModel> V_Model;
public:
	CMesh(string obj, string meta);
	shared_ptr<CHierModel> M_GetHierModel(void) { return V_Model; }
	virtual ~CMesh() {}

};

