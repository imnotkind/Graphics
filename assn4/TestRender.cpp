#include "CGraphics.h"

void CGraphics::M_RenderGame(void)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, V_SM->V_Textures["wall"].textureID);

	static double anim = 0.0;
	anim += 0.05;


}