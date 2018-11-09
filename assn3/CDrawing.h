#pragma once
#include "CHandler.h"
class CDrawing :
	public CHandler
{
	GLuint V_ArrayIndex;
	GLuint V_Program; // what program should be used for this drawing

public:
	CDrawing();
	virtual ~CDrawing() {}
};

