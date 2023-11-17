#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <random>
#include <windows.h>

using namespace std;

int Check()
{
	int in; rewind(stdin);
	while (scanf_s("%d", &in) != 1)
		rewind(stdin), printf_s("\nНеверные данные, введите повторно: ");
	return in;
}

void palindrom()
{
	stack<char> st; queue<char> qu; string pal; size_t cnt = 0;
	cout << "Для выхода напишите \"exit\"\n";

	do
	{
		cout << "\nВведите слово или число для проверки его на палиндром: "; cin >> pal;
		if (pal != "exit")
		{
			cnt = size(pal);

			for (auto simv : pal) st.push(simv), qu.push(simv);

			for (size_t i = 0; i < cnt; ++i)
			{
				if (st.top() == qu.front()) st.pop(), qu.pop();
				else
				{
					cout << "\nНе палиндром\n"; break;
				}
			}
			if (st.empty()) cout << "\nПалиндром\n";
			else
			{
				cout << "Не хватает символа: " << st.top() << " или " << qu.front() << "\n";
				while (!st.empty()) st.pop(), qu.pop();
			}

			pal = "";
		}
	} while (pal != "exit");
}

int Request(int mean)
{
	random_device rd; //генератор случайных чисел. 
	mt19937 gen(rd()); //генератор псевдослучайных чисел, который инициализируется случайным числом rd().
	poisson_distribution<>distr(mean); //создание объекта для генерации случайных чисел с распределением Пуассона при заданном среднем (ожидаемом) значении mean.
	return distr(gen);//генерирование случайного числа с распределением Пуассона с заданным параметром mean.
}

void Start(int& meanB, int& meanT, int& maxBoarding, int& maxTakeoff, int& time)
{
	cout << "Введи максимальное количество запросов на\nПосадку: "; maxBoarding = Check();
	cout << "Взлёт: "; maxTakeoff = Check();
	cout << "Введи время для моделирования запросов (значение, как час реального времени): "; time = Check();
	cout << "Введи предполагаемое (ожидаемое) число самолётов\nПрилетающих: "; meanB = Check();
	cout << "Взлетающих: "; meanT = Check();
}

void Airport()
{
	int meanB, meanT, mB, mT, maxBoarding, maxTakeoff, time,
		landCount = 0, takeoffCount = 0;
	queue<int> qB, qT;
	Start(meanB, meanT, maxBoarding, maxTakeoff, time);

	int boardCountRequests = 0, takeoffCountRequests = 0,
		acceptedBoardRequest = 0, acceptedTakeoffRequest = 0,
		allBoardCount = 0, allTakeoffCount = 0,
		rejectedBoardRequest = 0, rejectedTakeoffRequest = 0,
		allTimeWaiting = 0, downtime = 0;

	for (int i = 0; i < time; ++i)
	{
		mB = Request(meanB), mT = Request(meanT);

		for (int i = 0; i < mB; ++i, qB.push(1), ++boardCountRequests);
		for (int i = 0; i < mT; ++i, qT.push(1), ++takeoffCountRequests);

		if (qB.empty() && qT.empty()) ++downtime;

		if (!qB.empty())
			for (int i = landCount; i < maxBoarding && !qB.empty(); ++i, ++landCount, ++acceptedBoardRequest, ++allBoardCount, qB.pop());
		if (!qT.empty())
			for (int i = takeoffCount; i < maxTakeoff && !qT.empty(); ++i, ++takeoffCount, --landCount, ++acceptedTakeoffRequest, ++allTakeoffCount, qT.pop());

		if (!qB.empty())
		{
			cout << endl << qB.size() << " отправили на другой аэропорт\n";
			while (!qB.empty()) qB.pop(), ++rejectedBoardRequest;
		}
		if (!qT.empty())
		{
			cout << endl << qT.size() << " задержали взлёт\n";
			while (!qT.empty()) qT.pop(), ++rejectedTakeoffRequest;
			takeoffCount = 0;
			allTimeWaiting += rejectedTakeoffRequest;
		}
	}

	cout << "\n\nОбщее количество запросов: " << boardCountRequests + takeoffCountRequests;
	cout << "\n\nКоличество запросов на\nПосадку: " << boardCountRequests << "\nВзлёт: " << takeoffCountRequests;
	cout << "\n\nКоличество принятых запросов на\nПосадку: " << acceptedBoardRequest << "\nВзлёт: " << acceptedTakeoffRequest;
	cout << "\n\nКоличество\nПриземлившихся: " << allBoardCount << "\nВзлетевших: " << allTakeoffCount;
	cout << "\n\nКоличество отказов на\nПосадку: " << rejectedBoardRequest << "\nВзлёт: " << rejectedTakeoffRequest;
	cout << "\n\nОбщее время ожидания самолётов: " << allTimeWaiting;
	cout << "\n\nОбщее время простоя: " << (time / 100) * downtime << "%";
	cout << "\n\nСреднее количество запросов в час на\nПосадку: " << boardCountRequests / time << "\nВзлёт: " << takeoffCountRequests / time << endl;

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(0, "");
	int choice = -1;
	cout << "					Выполнил студент ДИНРБ-21/2 Ахмедов Шамиль";

	while (choice != 0)
	{

		cout << R"(
Выберите задание:
1. Палиндром
2. Аэропорт
0. Выход

Ввод: )";

		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			palindrom();
			break;
		case 2:
			Airport();
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	return 0;


}
