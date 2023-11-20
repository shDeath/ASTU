#ifndef VECTOR3D_H
#define VECTOR3D_H

#pragma once
#include <iostream>
#include <cmath>

class Vector3D {
private:
    double x, y, z;

public:
    // Конструкторы
    Vector3D();
    Vector3D(double x, double y, double z);

    // Методы-операции с присваиванием
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D& operator*=(double scalar);

    // Методы класса
    double length() const noexcept;
    double dotProduct(const Vector3D& other) const noexcept;
    Vector3D crossProduct(const Vector3D& other) const noexcept;
    double angle(const Vector3D& other) const noexcept;

    // Дружественные функции операции без присваивания
    friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator*(const Vector3D& v, double scalar);
    friend Vector3D operator*(double scalar, const Vector3D& v);
    friend bool operator==(const Vector3D& v1, const Vector3D& v2);
    friend bool operator!=(const Vector3D& v1, const Vector3D& v2);
    friend bool operator<(const Vector3D& v1, const Vector3D& v2);

    // Дружественные функции ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    friend std::istream& operator>>(std::istream& is, Vector3D& v);

    // Метод преобразования в строку
    std::string toString() const;

};

#endif // VECTOR3D_H