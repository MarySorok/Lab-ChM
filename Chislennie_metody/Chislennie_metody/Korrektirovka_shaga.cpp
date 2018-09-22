#include "Korrektirovka_shaga.h"
#include <math.h>

LocalPogreshControl::LocalPogreshControl(int p, double Eps)
{
	E = Eps;
	Emin = E / pow(2, p + 1);
	S = 0;
}
double LocalPogreshControl::CountLP(int p,double vi2, double vi)
{
	S = (vi2 - vi) / (pow(2, p) - 1);
	return S;
}