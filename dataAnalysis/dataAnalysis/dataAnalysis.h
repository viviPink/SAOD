#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H
#include <iostream>
#include <fstream>
#include <cassert>  
using namespace std;

// ������� ������ ����� inputfile � ���� �������� ����
template <typename T>
size_t CountUppercase(T& inputfile) {
 //������ ������ �� �����
    ifstream file(inputfile);
    //�������� �� ������������� �����
    if (!file.is_open()) {
      cout << "Error opening file " << endl;
    } 
    //������ ��������� �������� ��������
    size_t count_upper = 0;
    char ch;
    //�������� �� ������� ��������� ���� � ����� 
    // while(file.get(ch)) - ��� ����������� ����� while,
    //������� ��������� ����������� ������ ������ �� ����� file � ��������� �������� � ����� �� ����� �����.
    //file.get(ch) ������ ��������� ������ �� �����, ��������� ��� � ���������� ch � ���������� true, ���� �������� ������ ������ �������.
    while (file.get(ch)) {
        //isupper(ch) - ���������, �������� �� ������ ch ��������� ������..
        if (isupper(ch)) {
            count_upper++;
        }
    }
    return count_upper;
    file.close();
}



// ������� ������ �������� � ���� outputFile
template <typename T>
void OutFile(T& outputFile, size_t countUp) {

    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return;
    }
    outFile << "Number of uppercase letters : " << countUp << endl;
}


//������������ ������� CountUppercase
void AssertU()
{
    assert(CountUppercase("inputTest1.txt") == 0);
    assert(CountUppercase("inputTest2.txt") == 4);
    assert(CountUppercase("inputTest3.txt") == 10);
}
#endif