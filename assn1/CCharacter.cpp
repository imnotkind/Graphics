#include "CCharacter.h"



void CCharacter::M_Loop(double t)
{

}
void CCharacter::M_MegaFire(void)
{
	auto mq = SMQueue::M_GetSingletone(0);
	SScriptMessage message;
	auto math = CMath::getInstance();
	for (int i = 0; i < 10; i++)
	{
		double theta = DTR(math->M_Num_dRandom(0, 360));
		double speed = math->M_Num_dRandom(0.5, 3);

		message.type = "creation";
		message.content = (void*) new CBullet(V_Position, 0, T4Int(255, 0, 0, 255), 0.3, T2Double(cos(theta), sin(theta)) * speed);
		mq->M_Push(message);
	}

	
}
void CCharacter::M_Fire(void)
{
	auto mq = SMQueue::M_GetSingletone(0);

	SScriptMessage message;

	message.type = "creation";
	message.content = (void*) new CBullet(V_Position, 0, T4Int(255, 0, 0, 255), 0.3, T2Double(cos(V_Rotate), sin(V_Rotate)) * 1);
	mq->M_Push(message);

}
