#include "Korrektirovka_shaga.h"
#include "Method_RK.h"
#include "Methods_and_functions.h"
#include "Tochnoe_reshenie.h"


int main(void) {

	int P=4, Nmax; //N - ����� ����� >=10000, h <= 0.0001
	double Mas, param1, param2, xStart = 0, uStart, E, h0;
	double Ei; //���������� ����������� � ����� �i: Ei = ui-vi
	int k; // ����� ������������: ����� �� �������� ����� ��� �� �������� ������ (���������� ���) - ����� ������������ 0 - ��� ���., 1 - ��� ������� ����,����� ������ - ��� ����� ������
	//S - ������ ����������� �� i-�� ����

	//���� ����������

	myFunction R (Mas, param1, param2); // ������ ���� ������� (���������)
	R.Set_Start_Condition(uStart); // ������������� ��������� �������

	mySolution U(Mas, param1, param2, uStart, h0); //������ �������

	Method_Runge_Kutty ChM(P, h0, uStart, R); // ��������� ����� � ����� h
	Method_Runge_Kutty ChM2(P, h0 / 2, uStart, R); //��������� ����� � ���������� �����
	LocalPogreshControl S(P, E); //��������� �����������

	// ������ �������� 
	for (int i = 0;i < Nmax;i++)
	{
		ChM.Podschet(); // ����� �������� �� ����� ����� ������� �� ������ � ������� ������� Get � ����������� � �������
		ChM2.Podschet();
		//ChM2.Podschet(); �� ��� ����������, ����� ������� � ��� �� xi, ����� �� ����� 2. ������ ��� � ����������� ������ � � ������� ����� ���� ����������, � �������, ��������, ������
		S.CountLP(P,ChM.GetVi(),ChM2.GetVi());
		if (k == 0) {
			if (S.TooBig())
			{
				ChM.Goback();
				ChM.HalfH();
				ChM.Podschet(); // ����� � �����
				//ChM2.Goback();  ��� �� ������������ ������� ����� �� ������� �����, �� ���� ��������� � ����������?
				//ChM2.SetH(ChM.GetH() / 2);
				//ChM2.Podschet();
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
						ChM.Goback();
						ChM.HalfH();
						ChM.Podschet(); // !!! ����� ����������� V ����������, ���� ������� �� �������. ��� ���� ���� �������
						//ChM2.Goback(); 
						//ChM2.SetH(ChM.GetH() / 2);
						//ChM2.Podschet();
					}
				}
			}
		}
		// ��� ���� ��� v ��������, ��� ��� �� ����� ������� � ������� ������� ��������� v.

		U.Tochnoe_vichislenie(); // ������ �������
		Ei = U.GetUi_tochnoe() - ChM.GetVi(); // ���������� �����������
	}

	return 0;
}