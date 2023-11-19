#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


void calculateTask1(float x, float y, float resa, float resc)
{
	__asm
	{
		fld x		// скопироваkb x в st(0)
		fmul y		// x * y = xy

		fld x		// скопировали x в st(0), xy провалилось в st(1)
		fmul x		// x * x = x^2
		fmul x		// x^2 * x = x^3

		fld y		// скопировали y в st(0),x^3 провалилось в st(1) , xy провалилось в st(2)
		fmul y		// y * y = y^2
		fmul y		// y^2 * y = y^3
		fsub		// x^3 / y^3

		fld x		// скопировали x в st(0), x^3 - y^3 провалилось в st(1), xy провалилось в st(2)
		fmul x		// x * x = x^2

		fld st(2)	// скопировали xy
		fld1		
		fld1		
		fadd		// 1 + 1
		fmul		// 2 * xy

		fld y		// скопировать y в st(0)
		fmul y		// y * y
		fadd		// y^2 + 2xy
		fadd		// y^2 + 2xy + x^2
		fdiv		// (x^3 - y^3) / (x^2 + 2xy + y^2)
		fsub		// xy - (x^3 - y^3) / (x^2 + 2xy + y^2)

		fstp resa	// resa = st(0)
	}

	printf_s("Результаты вычислений на Assembler: %f\n", resa);

	// -- здесь вычисления на С++ -- 
	resc = x * y - ((x * x * x - y * y * y) / (x * x + 2 * x * y + y * y));

	printf_s("Результаты вычислений на C++: %f\n\n", resc);
}

void Task1(const int& choice)
{
	// Задание №1
	// xy - ((x^3 - y^3) / (x^2 + 2xy + y^2))

	// -- тестовые значения --
	// для x = -2, y = 7 ожидается ответ 0,040000
	// для x = 4, y = 3 ожидается ответ 11,244898

	float x, y, resa = 0, resc = 0;	// объявляем переменные

	std::cout << "Введите x и y: "; std::cin >> x; std::cin >> y;	//ввод значений x и y

	if (choice == 1)
		calculateTask1(x, y, resa, resc);
	else
		__asm {
		push resc
		push resa
		push y
		push x
		call calculateTask1
		add esp, 16
	}
}


void calculateTask2(float x, float resa, float resc)
{
	const float four = 4, five = 5;

	__asm
	{
		fld x		// скопировали x в st(0)
		fmul x		// x * x = x^2
		fmul x		// x^2 * x = x^3

		fld1		
		fld x		// скопировали x в st(0)
			
		fyl2x		// log2(x)
		fldl2e		// st(0) = log2(e), st(1) = log2(x)
		fdiv		// log2(x) / log2(e)
		fmul		// x^3 * lnx

		fld1		
		fld x		// скопировали x в st(0)
		fsqrt		// занесли под корень x
		fmul four	// корень x * 4
		fadd five	// 4x^(1/2) + 5

		fyl2x		// log2(x)
		fldl2e		// log2(e)
		fdiv		// ln( 4x^(1/2) + 5)

		fadd		// (x^3 * lnx) + (ln( 4x^(1/2) + 5))

		fstp resa		// resa = st(0)
	}

	printf_s("Результаты вычислений на Assembler: %f\n", resa);

	// -- здесь вычисления на С++ -- 
	resc = x * x * x * log(x) + log(4 * sqrt(x) + 5);

	printf_s("Результаты вычислений на C++: %f\n\n", resc);
}

void Task2(const int& choice)
{
	// Задание №2
	// x^3 * ln(x) + ln(4 sqrt(x) + 5)

	// -- тестовые значения --
	// для x = 10 ожидается ответ 2305,455811
	// для x = 4 ожидается ответ 91,287788

	float x, resa = 0, resc = 0;	// объявляем переменные
	std::cout << "Введите x: "; std::cin >> x;	//ввод значений x

	if (choice == 1)
		calculateTask2(x, resa, resc);
	else
		__asm {
		push resc
		push resa
		push x
		call calculateTask2
		add esp, 12
	}
}


void Highs(float a, float b, float c)
{
	float p, square, high1, high2, high3;
	__asm
	{
		fld a		// скопировали a в st(0)
		fadd b		// a + b
		fadd c		// a + b
		fld1
		fld1
		fadd		// 2
		fdiv		// (a + b) / 2
		fst p		// перенесkи (выгрузили) из регистра st(0) в xy

		fsub a		// p - a
		fld p		
		fsub b		// p - b
		fld p
		fsub c		// p - c
		fld p		
		fmul
		fmul
		fmul		// p * ( p - a ) * ( p - b ) * ( p - c )
		fsqrt		// занесли выражение под корень
		fst square	// выгрузили из регистра st(0) в square

		fld1		
		fld1		
		fadd		// 2
		fmul		// 2 * square
		fld st		// копируем стэк
		fld st		// также копируем

		fdiv a		// (2 * square) / a
		fstp high1	// выгрузили из регистра st(0) в high1
		fdiv b		// (2 * square) / b
		fstp high2	// выгрузили из регистра st(0) в high2
		fdiv c		// (2 * square) / c
		fstp high3	// выгрузили из регистра st(0) в high3

	}

	printf_s("Результаты вычислений на Assembler: \nВысоты: %f %f %f\n\n", high1, high2, high3);

	// -- здесь вычисления на С++ -- 
	p = (a + b + c) / 2;
	square = sqrt(p * (p - a) * (p - b) * (p - c));
	high1 = square * 2 / a;
	high2 = square * 2 / b;
	high3 = square * 2 / c;


	printf_s("Результаты вычислений на C++: \nВысоты: %f %f %f\n\n", high1, high2, high3);
}

void Task3(const int& choice)
{
	// Задание №3
	// Вычислить высоты треугольника со сторонами a, b, c.

	// -- тестовые значения --
	// для a = 3, b = 4, c = 5 ожидается ответ Высоты: 4 3 2,4
	// для a = 6, b = 3, c = 8 ожидается ответ Высоты: Высоты: 2,548147 5,096295 1,911111

	float a, b, c;	// объявляем переменные

	std::cout << "Введите стороны треугольника a, b и c: "; std::cin >> a; std::cin >> b; std::cin >> c;	// ввод значений a, b и c

	if (choice == 1)
		Highs(a, b, c);
	else
		__asm {
		push c
		push b
		push a
		call Highs
		add esp, 12
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");	// установка русского алфавита

	int choice = 0, task = 0;

	std::cout << "Ахмедов Шамиль. Лабораторная работа № 17-18. Вариант №4."
		<< R"(
Введите способ передачи данных:
1. Обычно (через С++)
2. В ассемблере

Ввод: )";
 std::cin >> choice;

	std::cout << "Введите номер задания (1-3): "; std::cin >> task;

	switch (task)
	{
	case 1:
		Task1(choice);
		break;
	case 2:
		Task2(choice);
		break;
	case 3:
		Task3(choice);
		break;
	default:
		break;
	}

	return 0;
}