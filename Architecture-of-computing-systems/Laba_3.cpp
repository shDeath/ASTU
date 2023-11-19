﻿#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

int main()
{
	// вычислить: xy + (x^3 + y^3)/(x^2 - 2xy + y^2)
	// для x = 5.1, y = 0 ожидается ответ 
	// для x = 2, y = 3 ожидается ответ 
	// для x = 1, y = 1 ожидается ответ 
	// для x = 10, y = 1 ожидается ответ 
	setlocale(LC_ALL, "Russian"); // Русский алфавит
	double x, y;
	cout << "Введите x: ";   cin >> x;	// ввод числа х по шаблону 00.00
	cout << "Введите y: ";   cin >> y;	// ввод числа y по шаблону 00.00

	double zn = 0, x2, y2, xy, resultA = 0, resultC = 0;
	__asm
	{
		fld x    // скопировать х в st(0) (загрузить х в st(0))
		fmul y   // умножить содержимое st(0) на y
		fstp xy  // перенести (выгрузить) из регистра st(0) в xy
		// в результате в ячейке xy находится произведение x и y, а стек пуст
		fld  x   // скопировать х в st(0) (загрузить х в st(0))
		fmul x   // умножить содержимое st(0) на x, получено x^2		
		fst x2   // скопировать x^2 в x2
		// в результате в ячейке x2 находится x^2, и в st(0) тоже
		fsub xy  // к содержимому st(0) добавили содержимое xy
		fsub xy  // и ещё раз  к содержимому st(0) добавили содержимое xy, там теперь x^2+2xy
		fld y    // скопировать y в st(0), при этом x^2 + 2xy продавилось в st(1)
		fmul y   // умножить содержимое st(0) на y, там теперь у^2
		fst y2   // сохранить содержимое st(0) в переменную y2
		fadd     // содержимое st(1) добавить к st(0), теперь в st(0) значение x^2+2xy+y^2, 
				   //а st(1) пусто
				   fstp zn  // выгрузили содержимое st(0)- знаменатель - в ячейку zn 
				   // в вершине стека получаем  x^3
				   fld x2
				   fmul x   // x^3
				   fld y2   // в вершине стека теперь y^2, а  x^3 - этажом ниже
				   fmul y   // y^3
				   fadd     // вычли из вершины содержимое st(1), в вершине теперь x^3 - y^3
				   fdiv zn  // поделили содержимое вершины на значение ячейки zn, 
				   // в st(0) теперь(x^3 + y^3)/(x^2 - 2xy + y^2)
				   fld xy   // в вершину стека загрузили xy, 
				   // вычитаемое (x^3 + y^3)/(x^2 - 2xy + y^2) теперь этажом ниже
				   fadd    //  из xy вычли дробь; если fsub, то из дроби будет вычтено ху
				   fstp resultA	// отправить результат в переменную resultA
	}
	cout << "Иванов Иван. Лабораторная работа № 5. Вариант #0." << endl;
	cout << "Результат (на языке Assembler): " << resultA << endl;

	// -- вычисление формулы на С++ -- 
	resultC = x * y + (x * x * x + y * y * y) / (x * x - 2 * x * y + y * y);
	cout << "Результат (на языке C++): " << resultC << endl;

	if (fabs(resultA - resultC) < 0.00001)	// Если |resultA - resultC| < 0.00001	 
		cout << "Разработанная программа на Ассемблере работает правильно! " << endl;
	else
		cout << "ПРОГРАММА НЕПРАВИЛЬНАЯ!!! " << endl;

	system("pause");
	return 0;
}