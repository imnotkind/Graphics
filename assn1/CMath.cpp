#include "CMath.h"



CMath::CMath()
{
}


CMath::~CMath()
{
}


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