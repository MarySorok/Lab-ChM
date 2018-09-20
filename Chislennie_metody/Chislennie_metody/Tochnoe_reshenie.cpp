#include "Tochnoe_reshenie.h"

mySolution::mySolution(double mas, double par1, double par2, double uStart, double shag) {
	m = mas;
	i = 0;
	a1 = par1;
	a3 = par2;
	h = shag;
	u0 = uStart;
	xi = x0;
	ui = u0;
	Const = m / (2 * a1)*log(a1 / (pow(u0, 2)) + a3) - x0;
}
int mySolution::Tochnoe_vichislenie(double) {
	int j;
	j = i + 1;
	double xj, uj;
	xj = xi + h;


    //переход в следующую точку
	xi = xj;
	ui = uj;

	return 0;
}