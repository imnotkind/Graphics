#include "CMath.h"



double CMath::M_Num_dRandom(double min, double max)
{
	uniform_real_distribution<double> dis(min, max);
	return dis(M_Random);
}
int CMath::M_Num_iRandom(int min, int max)
{
	uniform_int_distribution<int> dis(min, max);
	return dis(M_Random);
}
double CMath::M_Num_Gaussian(double mean, double sigma)
{
	normal_distribution<double> distribution(mean, sigma);
	return distribution(M_Random);

}
int CMath::M_Num_Discretization(double src, double s, double e, int d)
{
	double R = (src - s) / (e - s) * d;
	return MC_R(R);

}
double CMath::M_Func_Sigmoid(double r)
{
	return 1.0 / (1 + pow(C_E, -r));
}

bool CMath::M_St_Frequency(double f)
{
	return M_Num_dRandom(0, 1) <= f;
}

T2Double CMath::M_2TV_Normalize(T2Double P)
{
	double d = sqrt(P[0] * P[0] + P[1] * P[1]);
	return P * (1 / d);
}
T2Double CMath::M_2TV_Angle(T2Double Start, T2Double End)
{
	End -= Start;
	return T2Double(atan2(End[1], End[0]), sqrt(End[0] * End[0] + End[1] * End[1]));
}