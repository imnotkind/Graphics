#include "CCharacter.h"




void CCharacter::M_GetInvincible(int t)
{
	V_InvTime = t;
	V_Color.set(200, 200, 0, 100);
}
void CCharacter::M_Loop(double t)
{
	if (V_Power < 25) V_Power += 1;
	if (V_InvTime > 0)
	{
		V_InvTime--;
		if(V_InvTime == 0) V_Color.set(255, 0, 0, 255);
	}
}
void CCharacter::M_MegaFire(void)
{
	auto mq = SMQueue::M_GetSingletone(0);
	SScriptMessage message;
	auto math = CMath::getInstance();
	for (int i = 0; i < 30; i++)
	{
		double theta = DTR(math->M_Num_dRandom(0, 360));
		double speed = math->M_Num_dRandom(0.5, 3);

		message.type = "creation";
		message.content = (void*) new CBullet(V_Position, 4, T4Int(255, 0, 0, 255), 0.3, T2Double(cos(theta), sin(theta)) * speed);
		mq->M_Push(message);
	}

	
}
void CCharacter::M_Fire(void)
{
	if (V_Power < 25) return;
	auto mq = SMQueue::M_GetSingletone(0);

	SScriptMessage message;

	for (int i = -1; i <= 1; i++)
	{
		double theta = V_Rotate + DTR(10) * i;
		double speed = 1;

		message.type = "creation";
		message.content = (void*) new CBullet(V_Position, 4, T4Int(255, 0, 0, 255), 0.3, T2Double(cos(theta), sin(theta)) * speed);
		mq->M_Push(message);
	}
	V_Power = 0;
}
