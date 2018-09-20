#include "Method_RK.h"
#include "Methods_and_functions.h"

Method_Runge_Kutty::Method_Runge_Kutty(int Const, double shag, double nu, myFunction Fun)
{
	p = Const;
	h = shag;
	F = new myFunction(Fun);
	F->Set_Start_Condition(shag);
	i = 0;
	xi = 0;
	vi = F->GetNU();
}

int Method_Runge_Kutty::Podschet(double hkor, int N) // количество шагов
{
	//hkor - скорректированный шаг
	int j; //j == i+1
	double k1, k2, k3, k4;
	double xj, vj;
	j = i + 1;
	xj = xi + hkor;
	k1 = F->Count(xi, vi);
	k2 = F->Count(xi + hkor / 2, vi + hkor / 2 * k1);
	k3 = F->Count(xi + hkor / 2, vi + hkor / 2 * k2);
	k4 = F->Count(xi + hkor, vi + hkor*k3);
	vj = vi + hkor / 6 * (k1+2*k2+2*k3+k4);
	//перешли в следующую точку
	xi = xj;
	vi = vj;
	return 0;
}