#include "Tochnoe_reshenie.h"
#include <math.h>

mySolution::mySolution(double mas, double par1, double par2, double uStart, double shag) { //Масса, а1, а2, ну(скорость), шаг
	m = mas;
	i = 0;
	a1 = par1;
	a3 = par2;
	h = shag;
	u0 = uStart;
	xi = x0;
	ui = u0;
	Const = m / (2 * a1)*log((a1+a3*pow(u0,2)) / pow(u0, 2)) - x0;
}
int mySolution::Tochnoe_vichislenie() {
	double xj, uj;
	xj = xi + h;
	uj = sqrt(a1/(exp(2*a1/m*(xj+Const))-a3));
    //переход в следующую точку
	xi = xj;
	ui = uj;
	i++;
	return 0;
}