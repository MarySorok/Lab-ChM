#pragma once
#include "Methods_and_functions.h"

class Method_Runge_Kutty
{
	int p; //порядок метода
	myFunction* F;
	double h;
	int i;//номер текущего шага
	double xPrev, vPrev;
	double xi, vi; //текущая точка метода
public:
	Method_Runge_Kutty() {};
	Method_Runge_Kutty(int, double, double, myFunction);
	int Podschet();
	void Goback() { xi = xPrev; vi = vPrev; i--; }
	double GetXi() { return xi; }
	double GetVi() { return vi; }
	void HalfH() { h = h/2; }
	void DoubleH() { h = h * 2; }
	void SetH(double step) { h = step; }
	double GetH() { return h; }
	int Get_Poriadok() { return p; }
	~Method_Runge_Kutty() {};
};