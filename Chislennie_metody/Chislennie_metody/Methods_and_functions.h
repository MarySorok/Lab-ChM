#pragma once

class myFunction {
	double m; // �����
	double a1, a3; // ���������
	double x0 = 0, u0; // ��������� ����� � ��������
public:
	myFunction() {};
	myFunction(const myFunction& G);
	myFunction(double mas, double par1, double par2);
	double Count(double xi, double ui);
	double GetNU() { return u0; };
	void Set_Start_Condition(double uStart);
	myFunction& operator=(const myFunction& G);
	~myFunction() {};
};