#pragma once
#include "Methods_and_functions.h"

class Method_Runge_Kutty
{
	int p; //������� ������
	myFunction* F;
	double h;
	int i;//����� �������� ����
	double xi, vi; //������� ����� ������
public:
	Method_Runge_Kutty() {};
	Method_Runge_Kutty(int, double, double, myFunction);
	int Podschet();
	double GetXi() { return xi; }
	double GetVi() { return vi; }
	void SetH(double step) { h = step; }
	int Get_Poriadok() { return p; }
};