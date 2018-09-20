#pragma once
#include "Methods_and_functions.h"

class Method_Runge_Kutty
{
	int p; //порядок метода
	myFunction* F;
	double h;
	int i;//номер текущего шага
	double xi, vi; //текущая точка метода
public:
	Method_Runge_Kutty() {};
	Method_Runge_Kutty(int, double, double, myFunction);
	int Podschet(double, int N=10000);
};