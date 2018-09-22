#pragma once
#include "Method_RK.h"
#include "Tochnoe_reshenie.h"
#include <math.h>

class LocalPogreshControl
{
	double E; // <= 0.5 * pow(10, -6)
	double Emin, S;
public:
	LocalPogreshControl(int,double);
	double CountLP(int,double,double);
	~LocalPogreshControl() {};
	bool TooBig() { if (S > E) return true; return false; }
	bool TooSmall() { if (S < Emin) return true; return false; }
};