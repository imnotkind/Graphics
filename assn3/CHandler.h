#pragma once
#include "CMath.h"
#include "CError.h"
#include "CGeneral.h"
class CHandler
{
protected:
	CGeneral * V_General;
	CMath * V_Math;
public:
	CHandler();
	virtual ~CHandler();
};
