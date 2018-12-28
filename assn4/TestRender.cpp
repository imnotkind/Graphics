#include "CGraphics.h"

void CGraphics::M_RenderGame(void)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, V_SM->V_Textures["wall"].textureID);

	static double anim = 0.0;
	anim += 0.05;

	for (int i = -50; i <= 50; i++)
	{
		M_DrawLine(Vec3d(i, -50, 0), Vec3d(i, 50, 0), T4Int(84, 142, 253, 255));
		M_DrawLine(Vec3d(50,i , 0), Vec3d(-50, i , 0), T4Int(84, 142, 253, 255));
	}

	for (auto b : V_PEngine->V_Building)
	{	
		auto h = Vec3d(0, 0, b.height*0.5);
		M_DrawModel(b.pos + h, "cubeobj", Vec3d(b.w, b.h, b.height), b.rotate, T4Int(255, 255, 255, 255));
	}


}