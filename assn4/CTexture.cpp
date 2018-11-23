#include "CTexture.h"
#include "CImg.h"


CTexture::CTexture()
{
}


CTexture::~CTexture()
{
}

void CTexture::Image_Load(string path)
{
	CImg<unsigned char> src(path);
	int width = src.width();
	int height = src.height();

	cout << width << "/" << height << endl;
	unsigned char* ptr = src.data(10, 10); // get pointer to pixel @ 10,10
	unsigned char pixel = *ptr;
}