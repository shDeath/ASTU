#ifndef VECTOR3D_H
#define VECTOR3D_H

#pragma once
#include <iostream>
#include <cmath>

class Vector3D {
private:
    double x, y, z;

public:
    // ������������
    Vector3D();
    Vector3D(double x, double y, double z);

    // ������-�������� � �������������
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    Vector3D& operator*=(double scalar);

    // ������ ������
    double length() const noexcept;
    double dotProduct(const Vector3D& other) const noexcept;
    Vector3D crossProduct(const Vector3D& other) const noexcept;
    double angle(const Vector3D& other) const noexcept;

    // ������������� ������� �������� ��� ������������
    friend Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
    friend Vector3D operator*(const Vector3D& v, double scalar);
    friend Vector3D operator*(double scalar, const Vector3D& v);
    friend bool operator==(const Vector3D& v1, const Vector3D& v2);
    friend bool operator!=(const Vector3D& v1, const Vector3D& v2);
    friend bool operator<(const Vector3D& v1, const Vector3D& v2);

    // ������������� ������� �����/������
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);
    friend std::istream& operator>>(std::istream& is, Vector3D& v);

    // ����� �������������� � ������
    std::string toString() const;

};

#endif // VECTOR3D_H