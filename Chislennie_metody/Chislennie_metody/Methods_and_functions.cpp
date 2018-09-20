#include "Methods_and_functions.h"
#include <math.h>

double myFunction::Count(double xi, double ui)
{
	double R;
	R = -(a1*ui + a3*pow(ui,3));
	return R/m;
}
myFunction::myFunction(double mas, double par1, double par2) {
	m = mas;
	a1 = par1;
	a3 = par2;
}
void myFunction::Set_Start_Condition(double uStart) {
	u0 = uStart;
}
myFunction::myFunction(const myFunction& G)
{
	m = G.m;
	a1 = G.a1;
	a3 = G.a3;
}
myFunction& myFunction::operator=(const myFunction& G) {
	m = G.m;
	a1 = G.a1;
	a3 = G.a3;
	return *this;
}