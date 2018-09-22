#include "Method_RK.h"
#include "Methods_and_functions.h"

Method_Runge_Kutty::Method_Runge_Kutty(int Const, double shag, double nu, myFunction Fun) //порядок, шаг, ну(скорость), функция, где есть 3 параметра
{
	p = Const;
	h = shag;
	F = new myFunction(Fun);
	F->Set_Start_Condition(nu);
	i = 0;
	xi = 0;
	vi = F->GetNU();
	xPrev = -1;
	vPrev = -1;
}

int Method_Runge_Kutty::Podschet() 
{
	//hkor - скорректированный шаг
	//j == i+1
	double k1, k2, k3, k4;
	double xj, vj;
	xj = xi + h;
	k1 = F->Count(xi, vi);
	k2 = F->Count(xi + h / 2, vi + h / 2 * k1);
	k3 = F->Count(xi + h / 2, vi + h / 2 * k2);
	k4 = F->Count(xi + h, vi + h*k3);
	vj = vi + h / 6 * (k1+2*k2+2*k3+k4);
	//перешли в следующую точку
	xPrev = xi;
	vPrev = vi;
	xi = xj;
	vi = vj;
	i++;
	return 0;
}