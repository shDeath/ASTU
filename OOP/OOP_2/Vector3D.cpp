#include "Vector3D.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
// Конструктор по умолчанию
Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}

// Конструктор с параметрами
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

// Методы-операции с присваиванием
Vector3D& Vector3D::operator+=(const Vector3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3D& Vector3D::operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

// Методы класса
double Vector3D::length() const noexcept {
    return sqrt(x * x + y * y + z * z);
}

double Vector3D::dotProduct(const Vector3D& other) const noexcept {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::crossProduct(const Vector3D& other) const noexcept {
    return Vector3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

double Vector3D::angle(const Vector3D& other) const noexcept {
    double dot = dotProduct(other);
    double lenProduct = length() * other.length();
    return acos(dot / lenProduct);
}

// Дружественные функции операции без присваивания
Vector3D operator+(const Vector3D& v1, const Vector3D& v2) {
    Vector3D result = v1;
    result += v2;
    return result;
}

Vector3D operator-(const Vector3D& v1, const Vector3D& v2) {
    Vector3D result = v1;
    result -= v2;
    return result;
}

Vector3D operator*(const Vector3D& v, double scalar) {
    Vector3D result = v;
    result *= scalar;
    return result;
}

Vector3D operator*(double scalar, const Vector3D& v) {
    return v * scalar;
}

bool operator==(const Vector3D& v1, const Vector3D& v2) {
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

bool operator!=(const Vector3D& v1, const Vector3D& v2) {
    return !(v1 == v2);
}

bool operator<(const Vector3D& v1, const Vector3D& v2) {
    return v1.length() < v2.length();
}

// Дружественные функции ввода/вывода
ostream& operator<<(ostream& os, const Vector3D& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

istream& operator>>(istream& is, Vector3D& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}

// Метод преобразования в строку
string Vector3D::toString() const {
    return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
}