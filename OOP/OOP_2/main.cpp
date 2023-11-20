/*
������� ������ �����-21/2
������� � 11
������� ����� vector3D, ���������� ������� ���������. ����������� ������ ���� �����������: �������� �������� � ��������� ��������,
��������� ������������ ��������, ��������� ������������ ��������, ��������� �� ������, ��������� �������� �� ����������,
���������� ����� �������, ��������� ����� ��������, ���������� ���� ����� ���������.
*/
#include "Vector3D.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    setlocale(LC_ALL,"ru");
    try {
        // �������� �������� Vector3D
        Vector3D v1(1.0, 2.0, 3.0);
        Vector3D v2(4.0, 5.0, 6.0);
        Vector3D v3(3.0, 4.0, 5.0);
        // �������� � ���������
        Vector3D sum = v1 + v2;
        Vector3D diff = v3 - v2;
        double scalar = 2.0;
        Vector3D scaled = v1 * scalar;

        // ����� �����������
        cout << "v1: " << v1 << endl;
        cout << "v2: " << v2 << endl;
        cout << "v3: " << v3 << endl;
        cout << "�����: " << sum << endl;
        cout << "��������: " << diff << endl;
        cout << "��������� �� ������: " << scaled << endl;

        // ������ �������� � ����� �����������
        cout << "��������� ������������: " << v1.dotProduct(v2) << endl;
        cout << "��������� ������������: " << v1.crossProduct(v2) << endl;
        cout << "���� ����� ���������: " << v1.angle(v2) << " ������" << endl;
        cout << "����� v1: " << v1.length() << endl;
        cout << "����� v2: " << v2.length() << endl;

        if (v1 == v2) {
            cout << "������� �����" << endl;
        }
        else {
            cout << "������� �� �����" << endl;
        }

        assert(sum == Vector3D(5.0, 7.0, 9.0));
        assert(diff == Vector3D(-1.0, -1.0, -1.0));
        assert(scaled == Vector3D(2.0, 4.0, 6.0));
        // �������� ������ dotProduct
        assert(v1.dotProduct(v2) == 32.0);
        // �������� ������ crossProduct
        assert(v1.crossProduct(v2) == (-3.0, 6.0, -3.0));
        // �������� ������ angle
        assert(v1.angle(v2) == 0.225726);
        // �������� ������ length
        assert(v1.length() == 3.74166);
        // �������� ������ length
        assert(v2.length() == 8.77496);
        //������� �� �����
        // ������������ �������� ���������
        cout << "v1 == v2: " << (v1 == v2) << endl;
        cout << "v1 != v2: " << (v1 != v2) << endl;
        cout << "v1 < v2: " << (v1 < v2) << endl;
    }
    catch (const exception& e) {
        cerr << "����������: " << e.what() << endl;
    }

    return 0;
}