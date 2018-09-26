#include "Tochnoe_reshenie.h"
#include <math.h>

mySolution::mySolution(double mas, double par1, double par2, double uStart, double shag) { //�����, �1, �2, ��(��������), ���
	m = mas;
	i = 0;
	a1 = par1;
	a3 = par2;
	h = shag;
	u0 = uStart;
	xi = x0;
	ui = u0;
	Const = log(a1/(m*u0*u0)+a3*m)/(2*a1);
}
int mySolution::Tochnoe_vichislenie() {
	double xj, uj;
	xj = xi + h;
	uj = pow(a1/m,0.5)/(pow(exp((Const+xj)*2*a1)-a3*m,0.5));
    //������� � ��������� �����
	xi = xj;
	ui = uj;
	i++;
	return 0;
}