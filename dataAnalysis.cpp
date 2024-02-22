
#include <iostream>
#include <fstream>
#include <cctype>
#include "dataAnalysis.h"

int main() {
    //проверка работы функции
    AssertU();

    size_t countUp = CountUppercase("input.txt");
    cout << "Number of uppercase letters: " << countUp << endl;

    OutFile("output.txt", countUp);
}
