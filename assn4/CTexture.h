#pragma once
#include "CHandler.h"

class CTexture
{
private:
	GLuint textureID;
public:
	CTexture();
	virtual ~CTexture();
	void M_LoadBMP(string imagepath);
};

