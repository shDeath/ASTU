// laba_2_alg_and_str.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

template<class Type> struct Node
{
	Type info; Node<Type>* link;
	Node(const Type& d = Type(), Node<Type>* p = nullptr) :info{ d }, link{ p } {}

};

template<class T> class LinkedStack
{
private:
	Node<T>* top; // указатель на последний добавленный элемент стэка
public:
	LinkedStack() : top(NULL) {}; // Конструктор по умолчанию

	bool isEmpty() const // Отвечает на вопрос пуст ли стэк?
	{
		if (top == NULL)
			return true;
		else return false;
	}

	void initialize() // Опустошает стэк.(top = NULL)
	{
		while (top != NULL)
		{
			Node<T>* temp = top->link;
			delete top;
			top = temp;
		}
		top = NULL;
	}

	void push(const T& newItem) // Добавляет newItem xв стэк
	{
		Node<T>* temp = new Node<T>;
		temp->info = newItem;
		if (top != NULL)
			temp->link = top;
		top = temp;
	}

	T topInfo() const // Возвращает данные top элемента стэка
	{
		if (top != NULL)
			return top->info;
		else return NULL;
	}

	void pop() // Удаляет top элемент стэка
	{
		if (top->link != NULL)
		{
			Node<T>* temp = top->link;
			delete top;
			top = temp;
		}
		else if (top != NULL)
		{
			delete top;
			top = NULL;
		}
	}

	~LinkedStack() // Деструктор
	{
		while (top = NULL)
		{
			Node<T>* temp = top->link;
			delete top;
			top = temp;
		}
	}
};

//------------------------------------------------------------------------------------ 1. Массив

template<typename T> void start(T* mas, const T& size, LinkedStack<T>& stack)
{
	cout << "\nВведи размер массива: ";

	scanf_s("%d", &size);

	cout << "Введи элементы массива:\n";

	for (uint32_t i = 0; i < size; ++i)
	{
		printf_s("%d-й элемент: ", i + 1);
		scanf_s("%d", &mas[i]);
		stack.push(mas[i]);
		if (mas[i] == 1488)
		{
			start(mas, size, stack);
			break;
		}
	}
}

template<typename T> void invertMas(T* mas, const T& size, LinkedStack<T>& stack)
{
	LinkedStack<T> temp;
	for (uint32_t i = 0; i < size; i++)
	{
		mas[i] = stack.topInfo(); temp.push(stack.topInfo());
		stack.pop();
	}
	stack = temp;
}

template<typename T> void displayMas(const T* mas, const T& size)
{
	printf_s("\nЭлементы массива:\n");
	for (uint32_t i = 0; i < size; ++i)
	{
		printf_s("%d-й элемент: %d\n", i, mas[i]);
	}
	cout << endl;
}

int menuMas()
{
	LinkedStack<uint32_t> stack;
	uint32_t length = 0, choice = -1;
	uint32_t* mas = new uint32_t[length];
	start(mas, length, stack);
	displayMas(mas, length);

	while (choice != 0 && choice != -2)
	{
		cout << R"(
Выбери действия:
1. Инвертировать массив
2. Создать новый массив

0. Выход в меню

Ввод: )";
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			invertMas(mas, length, stack);
			displayMas(mas, length);
			break;
		case 2:
			choice = 0;
			break;
		case 0:
			choice = -2;
			break;
		default:
			break;
		}
	}
	if (!stack.isEmpty())
		stack.initialize();
	if (choice != -2)
		menuMas();
	return 0;
}

//------------------------------------------------------------------------------------ 2. HTML

#include <sstream>
#include <string>
#define is_latin(c) ((c) >= 'A' && (c) <= 'Z' || (c) >= 'a' && (c) <= 'z')
#define is_digit(c) ((c) >= '0' && (c) <= '9')

bool htmlCode(std::ostream& _out, std::istream& _in, LinkedStack<string> stack) {
	std::string s, b;
	const char* p, * i;

	while (std::getline(_in, s) && !_in.fail()) {
		p = s.c_str();
		while (*p) {
			if (*p != '<') {
				++p;
				continue;
			}
			++p;

			if (is_latin(*p)) {
				i = p;
				while (is_latin(*i) || is_digit(*i))
					++i;

				stack.push(std::string(p, (i - p)));

			}
			else if ((*p == '/') && is_latin(*(p + 1))) {
				i = ++p;
				b = "";
				while (is_latin(*i) || is_digit(*i))
					b += *i++;

				if (*i != '>')
				{
					_out << "\nОшибка: Отстутствует символ \">\" в теге </" << b << '>' << std::endl;
					return false;
				}

				if (stack.isEmpty()) {
					_out << "\nОшибка: Нет открывающего тега <" << b << '>' << std::endl;
					return false;
				}
				else if (stack.topInfo() != b) {
					_out << "\nОшибка: Закрывающий тег должен быть </" << stack.topInfo()
						<< ">, а не тег </" << b << '>' << std::endl;
					return false;
				}
				stack.pop();
			}
		}
	}

	bool err = true;
	while (!stack.isEmpty()) {
		_out << "\nОшибка: Нет закрывающего тега - </" << stack.topInfo() << '>' << std::endl;
		stack.pop();
		err = false;
	}
	return err;
}

int menuHTML()
{
	string s;
	LinkedStack<string> html;
	cout << "\nВведи HTML код: ";
	cin.ignore();
	getline(cin, s);
	istringstream sp(s);
	if (htmlCode(std::cout, sp, html))
		cout << "\nУра, ошибок нет." << std::endl;
	return 0;
}

//------------------------------------------------------------------------------------ 3. postfix notation

#define is_operation(c) ((c) == '*' || (c) == '/' || (c) == '-' || (c) == '+')

bool postfixNotation(std::ostream& _out, std::istream& _in, LinkedStack<string>& stack) {
	std::string s, b;
	const char* p;
	int a, c;
	bool a_c(int& a, int& c, LinkedStack<string>&stack), op = false;

	while (std::getline(_in, s) && !_in.fail()) {
		p = s.c_str();
		while (*p)
		{
			op = false;
			if (is_latin(*p))
			{
				_out << "\nОшибка: Буквы недопустимы\n";
				return false;
			}
			else if (is_digit(*p))
			{
				b = *p;
				stack.push(b);
			}
			else if (is_operation(*p))
			{
				if (stack.isEmpty())
				{
					_out << "\nОшибка: Нет чисел для операции\n";
					return false;
				}

				if (*p == '*')
				{
					if (a_c(a, c, stack))
						stack.push(to_string(a * c).c_str());
					else
					{
						_out << "\nОшибка: Нет второго числа для операции\n";
						return false;
					}
					op = true;
				}
				else if (*p == '/')
				{
					if (a_c(a, c, stack))
						stack.push(to_string(a / c).c_str());
					else
					{
						_out << "\nОшибка: Нет второго числа для операции\n";
						return false;
					}
					op = true;
				}
				else if (*p == '+')
				{
					if (a_c(a, c, stack))
						stack.push(to_string(a + c).c_str());
					else
					{
						_out << "\nОшибка: Нет второго числа для операции\n";
						return false;
					}
					op = true;
				}
				else if (*p == '-')
				{
					if (a_c(a, c, stack))
						stack.push(to_string(a - c).c_str());
					else
					{
						_out << "\nОшибка: Нет второго числа для операции\n";
						return false;
					}
					op = true;
				}
			}
			++p;
		}
	}

	if (!op)
		cout << "\nОшибка: Недостаточно операций\n";
	return op;
}

bool a_c(int& a, int& c, LinkedStack<string>& stack)
{
	c = atoi(stack.topInfo().c_str());
	stack.pop();
	if (!stack.isEmpty())
	{
		a = atoi(stack.topInfo().c_str());
		stack.pop();
	}
	else return false;
	return true;
}

int menuMath()
{
	string s;
	LinkedStack<string> notation;
	cout << "\nВведи постфиксное выражение (2 3 + = 2 + 3 или 2 3 4 + * = 2 * (3+4) ): ";
	cin.ignore();
	getline(cin, s);
	istringstream sp(s);
	if (postfixNotation(std::cout, sp, notation))
		cout << "\nОтвет: " << notation.topInfo() << std::endl;
	return 0;

}

//------------------------------------------------------------------------------------ main

int main()
{
	setlocale(LC_ALL, "RUS");
	int choice = -1;

	while (choice != 0)
	{

		cout << R"(
					Выполнил студент ДИНРБ-21/1 Ахмедов Шамиль
Выберите задание
1. С массивом
2. С HTML
3. Выражения в постфиксной форме

0. Выход

Ввод: )";

		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			menuMas();
			break;
		case 2:
			menuHTML();
			break;
		case 3:
			menuMath();
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	return 0;
}
