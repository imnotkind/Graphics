#pragma once
#include "CHandler.h"
#include "CImg.h"
class CTexture
{
public:
	CTexture();
	virtual ~CTexture();
	void Image_Load(string path);
};

