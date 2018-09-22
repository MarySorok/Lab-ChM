#include "Korrektirovka_shaga.h"
#include "Method_RK.h"
#include "Methods_and_functions.h"
#include "Tochnoe_reshenie.h"


int main(void) {

	int P=4, Nmax; //N - число шагов >=10000, h <= 0.0001
	double Mas, param1, param2, xStart = 0, uStart, E, h0;
	double Ei; //глобальная погрешность в точке хi: Ei = ui-vi
	int k; // выбор пользователя: отказ от контроля снизу или от контроля вообще (постоянный шаг) - выбор пользователя 0 - без ниж., 1 - обе границы есть,любая другая - без обеих границ
	//S - оценка погрешности на i-ом шаге

	//ввод параметров

	myFunction R (Mas, param1, param2); // вводим нашу функцию (параметры)
	R.Set_Start_Condition(uStart); // устанавливаем начальные условия

	mySolution U(Mas, param1, param2, uStart, h0); //точное решение

	Method_Runge_Kutty ChM(P, h0, uStart, R); // численный метод с шагом h
	Method_Runge_Kutty ChM2(P, h0 / 2, uStart, R); //численный метод с половинным шагом
	LocalPogreshControl S(P, E); //локальная погрешность

	// начало рассчета 
	for (int i = 0;i < Nmax;i++)
	{
		ChM.Podschet(); // после подсчета их можно сразу вывести из класса с помощью методов Get и распечатать в таблице
		ChM2.Podschet();
		//ChM2.Podschet(); тк шаг половинный, чтобы попасть в тот же xi, нужно их сдела 2. потому что у половинного метода и с обычным хагом иксы одинаковые, а функции, возможно, разные
		S.CountLP(P,ChM.GetVi(),ChM2.GetVi());
		if (k == 0) {
			if (S.TooBig())
			{
				ChM.Goback();
				ChM.HalfH();
				ChM.Podschet(); // здесь и внизу
				//ChM2.Goback();  раз мы возвращаемся обычным шагом на ступень назад, то надо вернуться и половинным?
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
						ChM.Podschet(); // !!! здесь вычисляется V уточненное, если помнишь из таблицы. Его тоже надо вывести
						//ChM2.Goback(); 
						//ChM2.SetH(ChM.GetH() / 2);
						//ChM2.Podschet();
					}
				}
			}
		}
		// там есть еще v итоговое, это как бы самое близкое к точному решению численное v.

		U.Tochnoe_vichislenie(); // точное решение
		Ei = U.GetUi_tochnoe() - ChM.GetVi(); // глобальная погрешность
	}

	return 0;
}