#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H
#include <iostream>
#include <fstream>
#include <cassert>  
using namespace std;

// функция чтения файла inputfile и счет заглвных букв
template <typename T>
size_t CountUppercase(T& inputfile) {
 //чтение данных из файла
    ifstream file(inputfile);
    //проверка на существование файла
    if (!file.is_open()) {
      cout << "Error opening file " << endl;
    } 
    //ставим начальное значение счетчика
    size_t count_upper = 0;
    char ch;
    //проверка на наличие порписных букв в файле 
    // while(file.get(ch)) - это конструкция цикла while,
    //которая позволяет посимвольно читать данные из файла file и выполнять действия в цикле до конца файла.
    //file.get(ch) читает следующий символ из файла, сохраняет его в переменную ch и возвращает true, если операция чтения прошла успешно.
    while (file.get(ch)) {
        //isupper(ch) - проверяет, является ли символ ch заглавной буквой..
        if (isupper(ch)) {
            count_upper++;
        }
    }
    return count_upper;
    file.close();
}



// Функция вывода значения в файл outputFile
template <typename T>
void OutFile(T& outputFile, size_t countUp) {

    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return;
    }
    outFile << "Number of uppercase letters : " << countUp << endl;
}


//тестирование функции CountUppercase
void AssertU()
{
    assert(CountUppercase("inputTest1.txt") == 0);
    assert(CountUppercase("inputTest2.txt") == 4);
    assert(CountUppercase("inputTest3.txt") == 10);
}
#endif