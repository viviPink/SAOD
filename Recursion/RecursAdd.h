#ifndef RECURSADD_H
#define RECURSADD_H
#include <iostream>
#include <fstream>
#include <cassert>

//функция для поиска суммы чисел a и b с помощью прибавления 1 и вычитания 1  (возращает значение результата сложения )
template<typename T>
T recAdd(T a, T b)
{
    if (a == 0)
        return b;
    // вызываем рекурсию пока первый агрумент не будет равен 0
    return recAdd(a - 1, b + 1);
}

// Проверка работы функции recAdd
void TestAssert()
{
    assert(recAdd(7, 3) == 10);
    assert(recAdd(9, 3) == 12);
    assert(recAdd(6, 8) == 14);
}


// функция прговерки глубины функции с помощью рекурсии
int recursionSt(int& x)
{
    std::cout << x << std::endl;
    x += 1;
    recursionSt(x);
    return 0;
}

#endif
