#pragma once
#include "CHandler.h"

class CTexture
{
private:
	
public:
	GLuint textureID;
	CTexture();
	virtual ~CTexture();
	void M_LoadBMP(string imagepath);
};

