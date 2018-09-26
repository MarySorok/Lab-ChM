#include "Korrektirovka_shaga.h"
#include "Method_RK.h"
#include "Methods_and_functions.h"
#include "Tochnoe_reshenie.h"


int main(void) {
	//������� ������ ����� ���� � ��������, ��������� �������� - 170 ��/� = 47.2222 �/� � ������� ��. 
	// ����� ������ ���� - 149 ����� = 0.149 ��
	// �1 = 0.15, �3 = 0.00075 
	// ���� ��������� ����� ���������, ��� ��������� �������� �����
	int P=4, Nmax = 10000; //N - ����� ����� >=10000, h <= 0.0001
	double Mas = 20;
	double param1 = 1, param2 = 1, xStart = 0, uStart = 1;
	double E = 1.0e-6;
	double h0 = 0.001, h1;
	double Ei; //���������� ����������� � ����� �i: Ei = ui-vi
	int k=1; // ����� ������������: ����� �� �������� ����� ��� �� �������� ������ (���������� ���) - ����� ������������ 0 - ��� ���., 1 - ��� ������� ����,����� ������ - ��� ����� ������
	//S - ������ ����������� �� i-�� ����
	h1 = h0 / 2;
	//���� ����������

	myFunction R (Mas, param1, param2); // ������ ���� ������� (���������)
	myFunction R1(Mas, param1, param2);
	R.Set_Start_Condition(uStart); // ������������� ��������� �������
	R1.Set_Start_Condition(uStart);

	mySolution U(Mas, param1, param2, uStart, h0); //������ �������

	Method_Runge_Kutty ChM(P, h0, uStart, R); // ��������� ����� � ����� h
	Method_Runge_Kutty ChM2(P, h1, uStart, R1); //��������� ����� � ���������� ����� 
	LocalPogreshControl S(P, E); //��������� �����������

	// ������ �������� 
	for (int i = 0;i < Nmax;i++)
	{ 
		while (ChM.GetVi() != 0) {
			ChM.Podschet(); // ����� �������� �� ����� ����� ������� �� ������ � ������� ������� Get � ����������� � �������
			ChM2.Podschet();
			ChM2.Podschet(); // �� ��� ����������, ����� ������� � ��� �� xi, ����� �� ������� 2. ������ ��� � ����������� ������ � � ������� ����� ���� ����������, � �������, ��������, ������
			S.CountLP(P, ChM.GetVi(), ChM2.GetVi());
			if (k == 0) {
				if (S.TooBig())
				{
					while (S.TooBig()) {
						ChM.Goback();
						ChM.HalfH();
						ChM.Podschet(); // ����� � �����
						ChM2.Goback(); // ��� �� ������������ ������� ����� �� ������� �����, �� ���� ��������� � ����������?
						ChM2.SetH(ChM.GetH() / 2);
						ChM2.Podschet();
					}
				}
			}
			else {
				if (k == 1) {
					if (S.TooSmall())
					{
						ChM.DoubleH();
						ChM2.SetH(ChM.GetH() / 2);
					}
					else {
						if (S.TooBig())
						{
							while (S.TooBig()) {
								ChM.Goback();
								ChM.HalfH();
								ChM.Podschet(); // !!! ����� ����������� V ����������, ���� ������� �� �������. ��� ���� ���� �������
								ChM2.Goback();
								ChM2.SetH(ChM.GetH() / 2);
								ChM2.Podschet();
							}
						}
					}
				}
			}
			// ��� ���� ��� v ��������, ��� ��� �� ����� ������� � ������� ������� ��������� v.

			U.Tochnoe_vichislenie(); // ������ �������
			Ei = U.GetUi_tochnoe() - ChM.GetVi(); // ���������� �����������
		}
	}

	return 0;
}