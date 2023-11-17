#include <iostream>
#include <cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	cout << R"(
Фамилия разработчика: Ахмедов Шамиль
Номер практического занятия: Лабораторная работа №9-10
		Номер варианта: №4
     |0; _если_х<3
f(x)=|
     |(1/(x+6); _В_ противном _ случае
========================================================
	)" << endl;

	double x, resultC, resultA;
	const double three = 3.0;
	const double term1 = 1;
	const double term2 = 6;
	const double term3 = 0;

	// -- тестовые значения --
	// для x = 0, ожидается ответ 0
	// для x = 2, ожидается ответ 0
	// для x = 25, ожидается ответ 0.0322581

	cout << "Введите x: ";
	cin >> x;

	__asm
	{
		fld three		 // Загружаем порог в стек (st(0))
		fld x            // Загружаем x в стек (st(0)), порог переходит в st(1)
		fcomi st, st(1)  // Сравниваем x с порогом и убираем значения из стека

		ja X_isntLessOrEqual // Если x >= three, переходим на метку X_isntLessOrEqual
		// Если x < three, продолжаем
		fld term3		 // Загружаем 0 в стек (st(0) = 0)

		jmp finish		 // Переходим на метку finish

		X_isntLessOrEqual :
			fld term1     // Вычисляем синус 1 (st(0) = 1)
			fld x         // Загружаем x в стек (st(0) = x, st(1) = 1)
			fadd term2	  // st(0) = x + 6
			fdiv          // Выполняем деление 1 / (x + 6)

			finish :
		fstp resultA            // Результат помещаем в resultA
	}

	// -- Результаты вычислений на Assembler --
	cout << "Результаты вычислений на Assembler: " << resultA << endl;

	if (x < 3.0) {
		resultC = 0.0;
	}
	else {
		resultC = 1.0 / (x + 6);
	}

	// Вывод результата на экран
	cout << "Результат на C++: " << resultC << endl;

	system("pause");
	return 0;
}