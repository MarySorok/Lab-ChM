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
	int Podschet(double, int N=10000);
};