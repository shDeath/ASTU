#include <iostream>
#include <cmath>

using namespace std;

// Функция для вычисления значения функции y = f(x) с использованием полного ветвления
double Fulbranch(double x) {
	if (x <= -1) {
		return sin(x);
	}
	else if (x <= 2) {
		return exp(x);
	}
	else if (x < 7) {
		return exp(-x) / (x + 2);
	}
	else {
		return sqrt(x);
	}
}
void FullBranch(double x, double y)
{
	const double  two = 2, seven = 7, sone = -1, one_two = 1.0 / 2.0, minusx=-x; // объявляем и инициализируем константные переменные

	__asm
	{
		fld sone // скопировали -1 в st(0)
		fld x // скопировали x в st(0), а -1 провалилось в st(1)
		fcomi st, st(1) // сравниваем x с -1

		jbe X_Less_s7 // если x < -1, то переходим на метку X_Less_s7
		jg X_Greater_s7 // если x >= -1, то переходим на метку X_Greater_s7

		X_Less_s7 :
		fsin // st(0) = sin(x)
			jmp finish // переход к финишу

			X_Greater_s7 : // x > -1
		fld two // st(0) = 2, st(1) = x
			fxch // st(0) = x, st(1) = 4 (st(0) <-> st(1))
			fcomi st, st(1)	// сравниваем x c 2
			jbe X_Less_4 // если x <= 2, то переходим на метку X_Less_4
			jg X_Greater_4 // если x >= 2, то переходим на метку X_Greater_4

			X_Less_4 : // x <= 2
		fld x
			fldl2e			// st(0) = log2(e), st(1) = x 
			fmul			// st(0) = log2(e) * x
			fld st			// st(0) = st(1) = log2(e) * x
			frndint
			fsub st(1), st	// st(1) -= st(0)		|	больше 1 или меньше -1, то эти 3 строчки можно
			fxch			// st(0) <-> st(1)		|	не писать
			f2xm1			// st(0) = 2^st(0) - 1	
			fld1			// st(0) = 1, st(1) = 2^st(1) - 1, st(2) = log2(e) * x
			fadd			// st(0) = 2^st(0), st(1) = log2(e) * x
			fscale			// st(0) = 2^st(0) * 2^(log2(e) * x)
			jmp finish		// переход к финишу

			X_Greater_4 :// x > 2
		fld seven // st(0) = 7, st(1) = x
			fxch // st(0) <-> st(1)
			fcomi st, st(1)	// сравниваем x c 7
			jae X_Greater_6	// если x >= 7, то переходим на метку X_Greater_6
			// если x < 7, то продолжаем
			fld minusx
			fldl2e			// st(0) = log2(e), st(1) = x 
			fmul			// st(0) = log2(e) * x
			fld st			// st(0) = st(1) = log2(e) * x
			fsub st(1), st	// st(1) -= st(0)		|	больше 1 или меньше -1, то эти 3 строчки можно
			fxch			// st(0) <-> st(1)		|	не писать
			f2xm1			// st(0) = 2^st(0) - 1	
			fld1			// st(0) = 1, st(1) = 2^st(1) - 1, st(2) = log2(e) * x
			fadd			// st(0) = 2^st(0), st(1) = log2(e) * x
			fscale			// st(0) = 2^st(0) * 2^(log2(e) * x)
			fld x			//st(0)= x
			fadd two		// st(0) = x + 2
			fdivp st(1), st // (2^st(0) * 2^(log2(e) * x))/(x+2)
			jmp finish		// переход к финишу

			X_Greater_6 : // x > 7
		fld one_two // st(0) = 1.0/2.0
			fld x // st(0) = x, st(1) = 1.0/2.0 
			fyl2x // st(0) = log2(x) * 1.0/2.0
			fld st // st(0) = log2(x) * 1.0/2.0, st(1) = log2(x) * 1.0/2.0
			frndint // Округление log2(x)*1.0/2.0 к ближайшему целому, результат в st(0), целое число в st(1)
			fxch // st(0) <-> st(1)
			fsub st, st(1) // st(0) = st(0) - st(1)
			f2xm1 // x(0) = 2^x - 1, где x - дробная часть log2(x)
			fld1 // x(0) = 1, x(1) = 2^x - 1
			fadd // x(0) = 1 + 2^x - 1
			fscale // умножение
			fld x // st(0) = x, st(1) = 2^x
			fadd  // x + 2^x
			fld x
			fsub
			jmp finish // переход к финишу


			finish : fstp y // поместили результат в y
	}

	cout << "Результаты вычислений на Assembler: " << y << endl;

	// -- здесь вычисление формулы на С++ -- 

	cout << "Результаты вычислений на C++: " << Fulbranch(x) << endl << endl;
}

// Функция для вычисления значения функции y = f(x) с использованием краткой формы ветвления
double Unfullbranch(double x) {
	return (x <= -1) ? sin(x) :
		(x <= 2) ? exp(x) :
		(x < 7) ? exp(-x) / (x + 2) :
		sqrt(x);
}

void UnfullBranch(double x, double y)
{
	const double  two = 2, seven = 7, sone = -1, one_two = 1.0 / 2.0,minusx=-x; // объявляем и инициализируем константные переменные
	double zn;
	__asm
	{
		fld sone // скопировали -1 в st(0)
		fld x // скопировали x в st(0), а -1 провалилось в st(1)
		fcomi st, st(1)	// сравниваем x с -1

		jbe X_Less_s7 // если x <= -1, то переходим на метку X_Less_s7

		fld two // st(0) = 2, st(1) = x
		fxch // st(0) = x, st(1) = 2 (st(0) <-> st(1))
		fcomi st, st(1) // сравниваем x c 2
		jbe X_Less_4 // если x <= 2, то переходим на метку X_Less_4

		fld seven // st(0) = 7, st(1) = x
		fxch // st(0) <-> st(1)
		fcomi st, st(1) // сравниваем x c 7
		jae X_Greater_6 // если x >= 7, то переходим на метку X_Greater_6
		// если x < 7, то продолжаем

		fld minusx
		fldl2e			// st(0) = log2(e), st(1) = x 
		fmul			// st(0) = log2(e) * x
		fld st			// st(0) = st(1) = log2(e) * x
		fsub st(1), st	// st(1) -= st(0)		|	больше 1 или меньше -1, то эти 3 строчки можно
		fxch			// st(0) <-> st(1)		|	не писать
		f2xm1			// st(0) = 2^st(0) - 1	
		fld1			// st(0) = 1, st(1) = 2^st(1) - 1, st(2) = log2(e) * x
		fadd			// st(0) = 2^st(0), st(1) = log2(e) * x
		fscale			// st(0) = 2^st(0) * 2^(log2(e) * x)
		fld x			//st(0)= x
		fadd two		// st(0) = x + 2
		fdivp st(1), st // (2^st(0) * 2^(log2(e) * x))/(x+2)
		jmp finish		// переход к финишу

		X_Greater_6 : // x > 7
		fld one_two // st(0) = 1.0/2.0
			fld x // st(0) = x, st(1) = 1.0/2.0 
			fyl2x // st(0) = log2(x) * 1.0/2.0
			fld st // st(0) = log2(x) * 1.0/2.0, st(1) = log2(x) * 1.0/2.0
			frndint // Округление log2(x)*1.0/2.0 к ближайшему целому, результат в st(0), целое число в st(1)
			fxch // st(0) <-> st(1)
			fsub st, st(1) // st(0) = st(0) - st(1)
			f2xm1 // x(0) = 2^x - 1, где x - дробная часть log2(x)
			fld1 // x(0) = 1, x(1) = 2^x - 1
			fadd // x(0) = 1 + 2^x - 1
			fscale // умножение
			fld x // st(0) = x, st(1) = 2^x
			fadd  // x + 2^x
			fld x
			fsub
			jmp finish // переход к финишу

			X_Less_4 : // x <= 2 
		fld x
			fldl2e			// st(0) = log2(e), st(1) = x 
			fmul			// st(0) = log2(e) * x
			fld st			// st(0) = st(1) = log2(e) * x
			frndint
			fsub st(1), st	// st(1) -= st(0)		|	больше 1 или меньше -1, то эти 3 строчки можно
			fxch			// st(0) <-> st(1)		|	не писать
			f2xm1			// st(0) = 2^st(0) - 1	
			fld1			// st(0) = 1, st(1) = 2^st(1) - 1, st(2) = log2(e) * x
			fadd			// st(0) = 2^st(0), st(1) = log2(e) * x
			fscale			// st(0) = 2^st(0) * 2^(log2(e) * x)
			jmp finish		// переход к финишу

			X_Less_s7 : // x < -1
		fsin // st(0) = sin(x)
			finish : fstp y // поместили результат в y
	}

	cout << "Результаты вычислений на Assembler: " << y << endl;

	// -- здесь вычисление формулы на С++ -- 
	cout << "Результаты вычислений на C++: " << Unfullbranch(x) << endl << endl;
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << R"(
Фамилия разработчика: Ахмедов Шамиль
Номер практического занятия: Лабораторная работа №11-12
	 Номер варианта: №4
     |sinx при x<=-1
f(x)=|e^x  при —1<х<=2
     |(e^-x)/(x+2) при 2<х<7
     |x^(1/2) при x=>7
========================================================
	)" << endl;
	// -- тестовые значения --
// для х = -10, ожидается ответ 0.544021
// для х = 0, ожидается ответ 1
// для х = 1, ожидается ответ 2.71828
// для х = 1.5, ожидается ответ 2.71828
// для х = 2, ожидается ответ 2.71828
// для х = 4, ожидается ответ 0.00305261
// для х = 16, ожидается ответ 4
// для х = 15, ожидается ответ 3.87298

	double x = 0, y = 0; // объявляем переменные и инициализируем в ноль
	int choice = -1;
	while (choice != 0)
	{

		if (cin.good()) {
			cout << "Введите x: ";
			cin >> x;	//ввод значения x
		}
		cout << R"(
Выберите пункт:
1: Результат с использованием полного ветвления
2: Результат с использованием краткой формы ветвления
0. Выход
)";
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			FullBranch(x, y);
			break;
		case 2:
			UnfullBranch(x, y);
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	return 0;
}

