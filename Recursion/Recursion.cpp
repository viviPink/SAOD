
//Gertruda Pinchukova 
// Задание:Написать функцию сложения двух чисел, используя только прибавление единицы.

#include <iostream>
#include <cassert>
#include "RecursAdd.h"
using namespace std;




int main(int argc, char* argv[])
{
    // для ввода с командной строки
    if (argc == 3)
    { //функцию atoi для преобразования аргументов командной строки в целочисленные значения
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);

        int result = recAdd(a, b);
        cout << "Сумма: " << result << endl;
    }
    
    else
    {
        TestAssert();

        int a, b,x;
        cout << "A: ";
        cin >> a;
        cout << "B: ";
        cin >> b;
        int result = recAdd(a, b);
        cout << "Summ: " << result << endl;

        // глубина стека вызовов , проверенный данной функцией равен равен 21351 в режиме release(размер стека болше)(погрешность 10) 
        x = 0;
        recursionSt(x);
    }



    

}

