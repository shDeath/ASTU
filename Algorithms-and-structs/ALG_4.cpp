#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>


using namespace std;

// Структура, представляющая файл
struct File {
    string name;
    time_t creationDate;
    int accessCount;
    File* previous;
    File* next;
};

// Функция для создания нового файла
File* createFile(string name, int accessCount) {
    File* newFile = new File();
    newFile->name = name;
    newFile->creationDate = time(0); // текущая дата
    newFile->accessCount = accessCount;
    newFile->previous = nullptr;
    newFile->next = nullptr;
    return newFile;
}

// Функция для добавления файла в конец списка
void addFile(File*& first, File*& last, File* file) {
    if (first == nullptr) { // список пустой
        first = file;
        last = file;
    }
    else {
        last->next = file;
        file->previous = last;
        last = file;
    }
}

// Функция для вывода каталога файлов
void printFiles(File* first) {
    char buffer[26];
    if (first == nullptr) {
        cout << "Каталог файлов пуст." << endl;
        return;
    }

    cout << "Каталог файлов:" << endl;
    File* current = first;
    while (current != nullptr) {
        cout << "Имя файла: " << current->name << endl;
        ctime_s(buffer, sizeof(buffer), &(current->creationDate));
        cout << "Дата создания: " << buffer;
        cout << "Количество обращений: " << current->accessCount << endl;
        cout << endl;
        current = current->next;
    }
}

// Функция для удаления файлов с датой создания меньше заданной
void deleteFilesByDate(File*& first, File*& last, time_t deleteDate) {
    char buffer[26];

    if (first == nullptr) {
        cout << "Каталог файлов пуст." << endl;
        return;
    }

    File* current = first;
    while (current != nullptr) {
        File* temp = current;
        current = current->next;
        if (temp->creationDate < deleteDate) {
            // Преобразование даты удаления в строку
            tm deleteTm;
            localtime_s(&deleteTm, &deleteDate);
            strftime(buffer, sizeof(buffer), "%c", &deleteTm);
            string deleteDateString(buffer);

            // Вывод информации о файле перед удалением
            cout << "Удаление файла: " << current->name << endl;
            cout << "Дата создания: " << buffer << endl;
            cout << "Дата удаления: " << deleteDateString << endl;

            // Удаление файла
            if (temp->previous != nullptr) {
                temp->previous->next = temp->next;
            }
            else {
                first = temp->next;
            }
            if (temp->next != nullptr) {
                temp->next->previous = temp->previous;
            }
            else {
                last = temp->previous;
            }
            delete temp;
        }
    }
}

// Функция для выборки файлов с наибольшим количеством обращений
void printTopFiles(File* first, int count) {
    if (first == nullptr) {
        cout << "Каталог файлов пуст." << endl;
        return;
    }

    // Создаем временный массив указателей на файлы
    File** files = new File * [count];
    for (int i = 0; i < count; i++) {
        files[i] = nullptr;
    }

    // Проходим по всем файлам и поддерживаем ранжированный массив files
    File* current = first;
    while (current != nullptr) {
        for (int i = 0; i < count; i++) {
            if (files[i] == nullptr || current->accessCount > files[i]->accessCount) {
                // Сдвигаем файлы с меньшим количеством обращений вправо
                for (int j = count - 1; j > i; j--) {
                    files[j] = files[j - 1];
                }
                files[i] = current;
                break;
            }
        }
        current = current->next;
    }

    cout << "Файлы с наибольшим количеством обращений:" << endl;
    for (int i = 0; i < count; i++) {
        if (files[i] == nullptr) {
            break;
        }
        cout << "Имя файла: " << files[i]->name << endl;
        cout << "Количество обращений: " << files[i]->accessCount << endl;
        cout << endl;
    }

    delete[] files; // освобождаем память
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    File* first = nullptr;
    File* last = nullptr;

    int choice;
    do {
        cout << "Меню:" << endl;
        cout << "1. Добавить файл" << endl;
        cout << "2. Вывести каталог файлов" << endl;
        cout << "3. Удалить файлы по дате создания" << endl;
        cout << "4. Вывести файлы с наибольшим количеством обращений" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберитепункт меню: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введите имя файла: ";
            string name;
            cin >> name;
            cout << "Введите количество обращений: ";
            int accessCount;
            cin >> accessCount;
            File* file = createFile(name, accessCount);
            addFile(first, last, file);
            cout << "Файл успешно добавлен." << endl;
            break;
        }
        case 2: {
            printFiles(first);
            break;
        }
        case 3: {
            cout << "Введите дату (unix timestamp): ";
            time_t date;
            cin >> date;
            deleteFilesByDate(first, last, date);
            cout << "Файлы успешно удалены." << endl;
            break;
        }
        case 4: {
            cout << "Введите количество файлов для выборки: ";
            int count;
            cin >> count;
            printTopFiles(first, count);
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "Ошибка: неверный пункт меню." << endl;
            break;
        }
        }
        cout << endl;
    } while (choice != 0);

    // Освобождаем память, выделенную под файлы
    while (first != nullptr) {
        File* temp = first;
        first = first->next;
        delete temp;
    }

    return 0;
}