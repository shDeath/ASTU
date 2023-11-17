#include <Windows.h>
#include <iostream>
#include<string>
#include <cmath>

using namespace std;

class vector3D {
private:
    double x, y, z;

public:
    //Геттеры
    double Getx() const {
        return x;
    }
    double Gety() const {
        return y;
    }
    double Getz() const {
        return z;
    }
    //Сеттеры
    void Setx(const double newx) {
        x = newx;
    }
    void Sety(const double newy) {
        y = newy;
    }
    void Setz(const double newz) {
        z = newz;
    }

    // Конструкторы без аргументов и инициализации
    vector3D() : x(0), y(0), z(0) {}
    vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    // Методы класса
    vector3D& operator+=(const vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vector3D& operator-=(const vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    double operator*(const vector3D& other) const {
        return (x * other.x + y * other.y + z * other.z);
    }

    vector3D operator^(const vector3D& other) const {
        return vector3D(y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    vector3D operator*(double scalar) const {
        return vector3D(x * scalar, y * scalar, z * scalar);
    }

    bool operator==(const vector3D& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    double length() const {
        return sqrt(x * x + y * y + z * z);
    }
};

// Дружественные функции операций без присваивания
vector3D operator+(vector3D lhs, const vector3D& rhs) {
    lhs += rhs;
    return lhs;
}

vector3D operator-(vector3D lhs, const vector3D& rhs) {
    lhs -= rhs;
    return lhs;
}

// Дружественная функция операции вывода в поток
ostream& operator<<(ostream& os, const vector3D& vec) {
    os << "(" << vec.Getx() << ", " << vec.Gety() << ", " << vec.Getz() << ")";
    return os;
}
istream& operator>>(istream& in, vector3D& vec) {
    string s;
    in >> s;
    vec.Setx(stod(s));
    in >> s;
    vec.Sety(stod(s));
    in >> s;
    vec.Setz(stod(s));
    return in;
}



double GetAngle(vector3D vec1, vector3D vec2)
{
    double dot_product = vec1 * vec2;
    vec1.length();
    vec2.length();
    double cosAngle = dot_product / (vec1.length() * vec2.length());//Получени косинуса угла
    double angle = acos(cosAngle);// Вычисление угла в радианах
    return angle;
}


// Главная функция для демонстрации работы с объектами класса vector3D
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    double angle;
    vector3D vec1;
    vec1.Setx(5);
    vec1.Sety(6);
    vec1.Setz(7);
    vector3D vec2;
    vec2.Setx(8);
    vec2.Sety(9);
    vec2.Setz(10);
    vector3D sum = vec1 + vec2;
    vector3D diff = vec2 - vec1;
    vector3D cross_product = vec1 ^ vec2;
    double dot_product = vec1 * vec2;
    cout << "Вектор1: " << vec1 << endl;
    cout << "Вектор2: " << vec2 << endl;
    cout << "Сумма: " << sum << endl;
    cout << "Разница: " << diff << endl;
    cout << "Векторное произведение: " << cross_product << endl;
    cout << "Скалярное произведение: " << dot_product << endl;
    cout << "Длина 1-го Вектора: " << vec1.length() << endl;
    cout << "Длина 2-го Вектора: " << vec2.length() << endl;
    if (vec1.length() != 0 && vec2.length() != 0) {
        angle = GetAngle(vec1, vec2);
        cout << "Вычисление угла между векторами: " << angle << endl;
    }
    else {
        cout << "Невозможно вычислить угол, так как один из векторов имеет нулевую длину." << endl;
    }

    if (vec1 == vec2) {
        cout << "Векторы равны" << endl;
    }
    else {
        cout << "Векторы не равны" << endl;
    }

    return 0;
}
