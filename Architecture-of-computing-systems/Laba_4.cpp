#include <iostream>
#include <cmath> // подключаем библиотеку математических функций

using namespace std;

void zadanie1()
{
	setlocale(LC_ALL, "russian");	// установка русского алфавита
	// задание № 1:
	// y = a + bx,		если х > 0;
	// y = x^2,			если х < 0:
	// y = 1,			если х = 0. 

	// -- тестовые значения --
	// a = 5, b = 2
	// для x = 0, ожидается ответ 1
	// для x = 5, ожидается ответ 15
	// для x = -5, ожидается ответ 25


	int x, a = 5, b = 2, y; // объявляем переменные и инициализируем a и b

	cout << "введите x: ";   cin >> x;	//ввод значения x

	__asm
	{
		mov eax, x			// поместили x в регистр eax
		cmp eax, 0			// сравнили: x == 0

		je equ				// если x = 0 переходим на метку equ

		jg abov				// если x > 0 переходим на метку abo

		imul x				// если x < 0 eax *= x
		jmp finish			// переход на метку finish

		equ :
		mov eax, 1		// x = 0; ebx = a
			jmp finish			// переход на метку finish

			abov :
		imul b		// x > 0; eax *= b
			add eax, a			// eax += a (eax = a + bx)

			finish : mov y, eax // поместили результат в y
	}

	cout << "\nАхмедов Шамиль. лабораторная работа № 07-08. вариант №4.\n\n"
		<< "результаты вычислений на assembler: " << y << endl;

	// -- здесь вычисление формулы на с++ -- 
	x == 0 ? y = 1
		: (x > 0 ? (y = a + b * x)
			: (y = x * x));
	cout << "результаты вычислений на c++: " << y << endl << endl;
	system("pause");
}

void zadanie2()
{
	setlocale(LC_ALL, "russian");	// установка русского алфавита
	//	 задание № 2:
	//	 ввести целое число. если оно является положительным, то прибавить к нему 1; 
	//	 в противном случае не изменять его. вывести полученное число
	//
	//	 -- тестовые значения --
	//	 x = 1, ожидается 2
	//	 x = -3, ожидается -3
	//
	int x, resa, resc; // объявляем переменные

	cout << "введите x: ";   cin >> x;	//ввод значения x

	__asm
	{
		mov eax, x				// поместили x в регистр eax
		cmp eax, 0				// сравнили: x == 0

		jns positive			// если x > 0 переходим на метку positive
		jmp finish				// если x < 0 переход на метку finish

		positive : inc eax		// ++x

		finish : mov resa, eax	// поместили результат в resa
	}

	cout << "\nАхмедов Шамиль. лабораторная работа № 07-08. вариант №4.\n\n"
		<< "результаты вычислений на assembler: " << resa << endl;

	// здесь вычисление формулы на с++ -- 
	x > 0 ? resc = ++x : resc = x;
	cout << "результаты вычислений на c++: " << resc << endl << endl;
	system("pause");
}

void zadanie3()
{
	setlocale(LC_ALL, "Russian");	// установка русского алфавита
	//	// ЗАДАНИЕ № 3:
	//	// Ввести три целых числа. Найти наименьшее из них.
	//
	//	// -- тестовые значения --
	//	// x = 1, y = 2, z = 3 ожидается 1
	//	// x = 2, y = 2, z = 3 ожидается 2
	//	// x = -1, y = -2, z = -3 ожидается -3
	//
	int x, y, z, resa, resc; // объявляем переменные

	cout << "Введите x: ";   cin >> x;	//ввод значения x
	cout << "Введите y: ";   cin >> y;	//ввод значения y
	cout << "Введите z: ";   cin >> z;	//ввод значения z

	__asm
	{
		mov eax, x				// поместили x в регистр eax

		cmp eax, y				// сравнили: x == y
		jle XlessY				// если x <= y, то переход на метку XlessY

		mov eax, y				// если y < x, то копируем в регистр eax значение y

		cmp eax, z				// сравнили y == z
		jg Z_isSmall			// если z < y, то переход на метку Z_isSmall
		jmp finish				// если y <= z, то переход на метку finish

		XlessY : cmp eax, z		// сравнили x == z
		jg Z_isSmall			// если z < x, то переход на метку Z_isSmall
		jmp finish				// если x <= z, то переход на метку finish

		Z_isSmall : mov eax, z  // поместили значение z в регистр eax

		finish : mov resa, eax	// поместили результат в resa
	}

	cout << "\nАхмедов Шамиль. лабораторная работа № 07-08. вариант №4.\n\n"
		<< "результаты вычислений на assembler: " << resa << endl;

	// -- здесь вычисление формулы на С++ -- 
	x <= y ? (x <= z ? resc = x : resc = z)
		: (y <= z ? resc = y : resc = z);
	cout << "Результаты вычислений на C++: " << resc << endl << endl;
	system("pause");
}

void zadanie4()
{
	setlocale(LC_ALL, "Russian");	// установка русского алфавита
	// ЗАДАНИЕ № 4:
	// Ввести три целых числа. Найти количество положительных чисел в исходном наборе.

	// -- тестовые значения --
	// x = 1, y = 2, z = 3 ожидается 3
	// x = 2, y = -2, z = 3 ожидается 1
	// x = -1, y = -2, z = -3 ожидается 3

	int x, y, z, resa = 0, resc = 0; // объявляем переменные

	cout << "Введите x: ";   cin >> x;	//ввод значения x
	cout << "Введите y: ";   cin >> y;	//ввод значения y
	cout << "Введите z: ";   cin >> z;	//ввод значения z

	__asm
	{
		mov eax, x					// поместили x в регистр eax
		cmp eax, 0					// сравнили: x == 0
		jns posX					// если x < 0, то переход на метку negX
		jmp analyseY				// если x > 0, то переход на метку analyseY
		posX : inc resa				// ++resa

		analyseY :
		mov eax, y				// поместили y в регистр eax
			cmp eax, 0				// сравнили: y == 0
			jns posY				// если y < 0, то переход на метку negY
			jmp analyseZ			// если x > 0, то переход на метку analyseZ
			posY : inc resa			// ++resa

			analyseZ :
		mov eax, z				// поместили z в регистр eax
			cmp eax, 0				// сравнили: z == 0
			jns posZ				// если z < 0, то переход на метку negZ
			jmp finish				// если x > 0, то переход на метку analyseZ
			posZ : inc resa			// ++resa

			finish :
	}

	cout << "\nАхмедов Шамиль. лабораторная работа № 07-08. вариант №4.\n\n"
		<< "результаты вычислений на assembler: " << resa << endl;

	// -- здесь вычисление формулы на С++ -- 
	x > 0 ? ++resc : resc; y > 0 ? ++resc : resc; z > 0 ? ++resc : resc;
	cout << "Результаты вычислений на C++: " << resc << endl << endl;
	system("pause");
}

void zadanie5()
{
	setlocale(LC_ALL, "Russian");	// установка русского алфавита
	//	// ЗАДАНИЕ № 5:
	//	// На числовой оси расположены три точки: A, B, C. Определить, какая из двух последних точек (B или C) 
	//	// расположена ближе к A, вывести эту точку и ее расстояние от точки A.
	//
	//	// -- тестовые значения --
	//	// A = 0, B = -3, C = 4 ожидается B -3
	//	// A = -3, B = -6, C = 0 ожидается B -6 или C 0
	//
	//
	int A, B, C, resa = 0, resc = 0;	// объявляем переменные
	char b = 'B', c = 'C', ansa, ansc;	// объявляем переменные

	cout << "Введите A: ";   cin >> A;	//ввод значения A
	cout << "Введите B: ";   cin >> B;	//ввод значения B
	cout << "Введите C: ";   cin >> C;	//ввод значения C

	__asm
	{
		mov eax, A					// поместили A в регистр eax
		mov ebx, A					// поместили A в регистр ebx

		sbb eax, B					// нашли расстояние от A до В
		sbb ebx, C					// нашли расстояние от А до С

		moduleAB : neg eax			// поменяли знак eax, чтобы его найти модуль
		js moduleAB					// если eax отрицательный, то меняем ещё раз

		moduleAC : neg ebx			// поменяли знак ebx, чтобы его найти модуль
		js moduleAC					// если ebx отрицательный, то меняем ещё раз

		cmp eax, ebx				// сравниваем расстояния до В и до С
		jg C_closer					// если C ближе, то переход на метку C_closer
		mov eax, B					// если B ближе, то сбрасываем значение регистра на значение B
		mov ansa, 'B'				// поместили в ansa букву B
		jmp finish					// переход на метку finish

		C_closer : mov eax, C		// заменили значение eax на C
		mov ansa, 'C'				// поместили в ansa букву С

		finish : mov resa, eax		// записали ответ в resa
	}

	cout << "\nАхмедов Шамиль. Лабораторная работа № 07-08. Вариант №4.\n\n";
	printf_s("Результаты вычислений на Assembler: %c %d\n", ansa, resa);

	// -- здесь вычисление формулы на С++ -- 
	abs(A - B) < abs(A - C) ? (ansc = 'B', resc = B) // используем функцию вычисления модуля для упрощения
		: (ansc = 'C', resc = C);
	printf_s("Результаты вычислений на C++: %c %d\n\n", ansc, resc);
	system("pause");
}

int main() {
	setlocale(LC_ALL, "RUS");
	int choice = -1;
	while (choice != 0)
	{

		cout << R"(
Выбери задание:
1. Задание № 1:
2. задание № 2:
3. задание № 3:
4. задание № 4:
5. задание № 5:
0. Выход
Ввод: )";

		scanf_s("%d", &choice);


		switch (choice)
		{
		case 1:
			zadanie1();
			break;
		case 2:
			zadanie2();
			break;
		case 3:
			zadanie3();
			break;
		case 4:
			zadanie4();
			break;
		case 5:
			zadanie5();
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	return 0;
}