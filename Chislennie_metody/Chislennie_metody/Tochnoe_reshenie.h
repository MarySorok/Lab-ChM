#pragma once
#include <math.h>

class mySolution {
	double xi, ui;
	int i;
	double Const;
	double m;
	double a1, a3;
	double h;
	double x0=0, u0;
public:
	mySolution() {};
	mySolution(double, double, double, double, double);
	int Tochnoe_vichislenie(double);
};