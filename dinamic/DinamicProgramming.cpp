//Пинчукова Гера ИВТ-22
#include <iostream>
#include <fstream>
#include "DinProg.h"


/*Задача Треугольник Паскаля
Треугольник Паскаля строится следующим образом.Первая строка состоит из одного числа, равного единице.
Каждая следующая содержит на одно число больше, чем предыдущая.Первое и последнее из этих чисел равны 1, 
а все остальные вычисляются как сумма числа, стоящего в предыдущей строке над ним и числа, стоящего в предыдущей 
же строке слева от него.Входные данные.В файле INPUT.TXT записано одно число N(0 <= N <= 30).Выходные данные.В файл OUTPUT.TXT 
вывести N строк треугольника 
Паскаля.Примечание.Все числа в треугольнике Паскаля при указанных ограничениях входят в Longint.Пример файла INPUT.TXT*/

int main() {

    testt();

    // взятие значения n из файла input.txt
    std::ifstream inputFile("input.TXT");
    int n;
    inputFile >> n;
    inputFile.close();

    // динамическое выделение памяти для элементов 
    long long** pascalsTriangle = new long long* [n];
    //заполнение треугольника паскаля с заданным значением n в файле input.txt
    createPascalTriangle(n, pascalsTriangle);
    outputPascalsTriangleToFile(n, pascalsTriangle);

    //освобождение памяти 
    for (int i = 0; i < n; i++) {
        delete[] pascalsTriangle[i];
    }
    delete[] pascalsTriangle;
}
