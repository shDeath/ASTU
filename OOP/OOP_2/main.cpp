/*
Ахмедов Шамиль ДИНРБ-21/2
Вариант № 11
Создать класс vector3D, задаваемый тройкой координат. Обязательно должны быть реализованы: операции сложения и вычитания векторов,
векторное произведение векторов, скалярное произведение векторов, умножения на скаляр, сравнение векторов на совпадение,
вычисление длины вектора, сравнение длины векторов, вычисление угла между векторами.
*/
#include "Vector3D.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    setlocale(LC_ALL,"ru");
    try {
        // Создание объектов Vector3D
        Vector3D v1(1.0, 2.0, 3.0);
        Vector3D v2(4.0, 5.0, 6.0);
        Vector3D v3(3.0, 4.0, 5.0);
        // Операции с векторами
        Vector3D sum = v1 + v2;
        Vector3D diff = v3 - v2;
        double scalar = 2.0;
        Vector3D scaled = v1 * scalar;

        // Вывод результатов
        cout << "v1: " << v1 << endl;
        cout << "v2: " << v2 << endl;
        cout << "v3: " << v3 << endl;
        cout << "Сумма: " << sum << endl;
        cout << "Разность: " << diff << endl;
        cout << "Умножение на скаляр: " << scaled << endl;

        // Другие операции и вывод результатов
        cout << "Скалярное произведение: " << v1.dotProduct(v2) << endl;
        cout << "Векторное произведение: " << v1.crossProduct(v2) << endl;
        cout << "Угол между векторами: " << v1.angle(v2) << " радиан" << endl;
        cout << "Длина v1: " << v1.length() << endl;
        cout << "Длина v2: " << v2.length() << endl;

        if (v1 == v2) {
            cout << "Векторы равны" << endl;
        }
        else {
            cout << "Векторы не равны" << endl;
        }

        assert(sum == Vector3D(5.0, 7.0, 9.0));
        assert(diff == Vector3D(-1.0, -1.0, -1.0));
        assert(scaled == Vector3D(2.0, 4.0, 6.0));
        // Проверка метода dotProduct
        assert(v1.dotProduct(v2) == 32.0);
        // Проверка метода crossProduct
        assert(v1.crossProduct(v2) == (-3.0, 6.0, -3.0));
        // Проверка метода angle
        assert(v1.angle(v2) == 0.225726);
        // Проверка метода length
        assert(v1.length() == 3.74166);
        // Проверка метода length
        assert(v2.length() == 8.77496);
        //Векторы не равны
        // Демонстрация операций сравнения
        cout << "v1 == v2: " << (v1 == v2) << endl;
        cout << "v1 != v2: " << (v1 != v2) << endl;
        cout << "v1 < v2: " << (v1 < v2) << endl;
    }
    catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
    }

    return 0;
}