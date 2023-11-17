#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Структура для хранения числовых и строковых полей
struct MyStruct {
    int number1;
    int number2;
    string text1;
    string text2;
};

// Класс для узла списка
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T data) : data(data), next(nullptr) {}
};

// Класс для односвязного линейного списка
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int len = 0;
public:
    LinkedList() : head(NULL),  len(0) {}

    void print()
    {
        Node<T>* current = head;
        for (int i = 0; i < len; i++)
        {
            cout << endl << i  << "-й: " << current->data;
            current = current->next;
        }
        cout << endl;
    }

    // Добавление элемента в список
    void addElement(T data) {
        if (head == NULL) {
            head = new Node<T>(data);
        }
        else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++len;
    }

    // Получение длины спискаs
    int getLength() {

        return len-1;
    }

    // Поиск элемента в списке
    int searchElement(T value) {
        int index = 0;
        Node<T>* current = head;
        while (current != NULL) {
            if (current->data == value) {
                return index;
            }
            index++;
            current = current->next;
        }
        return -1;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    LinkedList<string> linkedList;
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Ввеcти элементы списка (для окончания введите 'exit'):" << endl;
        cout << "2. Вывести длину списка" << endl;
        cout << "3. Поиск элемента" << endl;
        cout << "4. Выйти из программы" << endl;

        int choice, count;
        cin >> choice;
        if (choice == 1) {
            cout << "Введите элементы списка (для окончания введите 'exit'):" << endl;
            string input;
            getline(cin, input);
            while (input != "exit" ) {
                linkedList.addElement(input);
                getline(cin, input);
             
            }
        }
        else if (choice == 2) {
            cout << "Длина списка: " << linkedList.getLength() << endl;

        }
        else if (choice == 3) {
            string input;
            linkedList.addElement(input);
            getline(cin, input);
            cout << "Введите значение для поиска:" << endl;
            getline(cin, input);

            int index = linkedList.searchElement(input);
            if (index != -1) {
                cout << "Элемент найден на позиции " << index << endl;
            }
            else {
                cout << "Элемент не найден" << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else if (choice == 5) {
            linkedList.print();

        }
        else {
            cout << "Неверный выбор. Пожалуйста, выберите корректный пункт меню." << endl;
        }
    }
    return 0;
}