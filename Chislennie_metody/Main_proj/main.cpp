#include "Korrektirovka_shaga.h"
#include "Method_RK.h"
#include "Methods_and_functions.h"
#include "Tochnoe_reshenie.h"


int main(void) {
	//возьмем задачу полет мяча в бейсболе, начальная скорость - 170 км/ч = 47.2222 м/с в системе Си. 
	// масса такого мяча - 149 грамм = 0.149 кг
	// а1 = 0.15, а3 = 0.00075 
	// пока предлагаю такие параметры, все считается довольно точно
	int P=4, Nmax = 10000; //N - число шагов >=10000, h <= 0.0001
	double Mas = 20;
	double param1 = 1, param2 = 1, xStart = 0, uStart = 1;
	double E = 1.0e-6;
	double h0 = 0.001, h1;
	double Ei; //глобальная погрешность в точке хi: Ei = ui-vi
	int k=1; // выбор пользователя: отказ от контроля снизу или от контроля вообще (постоянный шаг) - выбор пользователя 0 - без ниж., 1 - обе границы есть,любая другая - без обеих границ
	//S - оценка погрешности на i-ом шаге
	h1 = h0 / 2;
	//ввод параметров

	myFunction R (Mas, param1, param2); // вводим нашу функцию (параметры)
	myFunction R1(Mas, param1, param2);
	R.Set_Start_Condition(uStart); // устанавливаем начальные условия
	R1.Set_Start_Condition(uStart);

	mySolution U(Mas, param1, param2, uStart, h0); //точное решение

	Method_Runge_Kutty ChM(P, h0, uStart, R); // численный метод с шагом h
	Method_Runge_Kutty ChM2(P, h1, uStart, R1); //численный метод с половинным шагом 
	LocalPogreshControl S(P, E); //локальная погрешность

	// начало рассчета 
	for (int i = 0;i < Nmax;i++)
	{ 
		while (ChM.GetVi() != 0) {
			ChM.Podschet(); // после подсчета их можно сразу вывести из класса с помощью методов Get и распечатать в таблице
			ChM2.Podschet();
			ChM2.Podschet(); // тк шаг половинный, чтобы попасть в тот же xi, нужно их сделать 2. потому что у половинного метода и с обычным хагом иксы одинаковые, а функции, возможно, разные
			S.CountLP(P, ChM.GetVi(), ChM2.GetVi());
			if (k == 0) {
				if (S.TooBig())
				{
					while (S.TooBig()) {
						ChM.Goback();
						ChM.HalfH();
						ChM.Podschet(); // здесь и внизу
						ChM2.Goback(); // раз мы возвращаемся обычным шагом на ступень назад, то надо вернуться и половинным?
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
								ChM.Podschet(); // !!! здесь вычисляется V уточненное, если помнишь из таблицы. Его тоже надо вывести
								ChM2.Goback();
								ChM2.SetH(ChM.GetH() / 2);
								ChM2.Podschet();
							}
						}
					}
				}
			}
			// там есть еще v итоговое, это как бы самое близкое к точному решению численное v.

			U.Tochnoe_vichislenie(); // точное решение
			Ei = U.GetUi_tochnoe() - ChM.GetVi(); // глобальная погрешность
		}
	}

	return 0;
}