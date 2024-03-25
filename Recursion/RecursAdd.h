#ifndef RECURSADD_H
#define RECURSADD_H
#include <iostream>
#include <fstream>
#include <cassert>

//������� ��� ������ ����� ����� a � b � ������� ����������� 1 � ��������� 1  (��������� �������� ���������� �������� )
template<typename T>
T recAdd(T a, T b)
{
    if (a == 0)
        return b;
    // �������� �������� ���� ������ �������� �� ����� ����� 0
    return recAdd(a - 1, b + 1);
}

// �������� ������ ������� recAdd
void TestAssert()
{
    assert(recAdd(7, 3) == 10);
    assert(recAdd(9, 3) == 12);
    assert(recAdd(6, 8) == 14);
}


// ������� ��������� ������� ������� � ������� ��������
int recursionSt(int& x)
{
    std::cout << x << std::endl;
    x += 1;
    recursionSt(x);
    return 0;
}

#endif
