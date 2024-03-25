
#ifndef DINPROG_H
#define DINPROG_H
#include <iostream>
#include <fstream>
#include <cassert>

// �������� ������������ ������� <pascalTriangle> �� ��������� ���������� ����� <n>� ����� <input.txt>
template <typename T>
void createPascalTriangle(int n, T** pascalTriangle) {
    // ��������� ������ ��� ���������
    for (int i = 0; i < n; i++) {
        pascalTriangle[i] = new T[i + 1];
    }
    // ���������� �� �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            //���������� 1 ���� ������ ��� ��������� �������
            if (j == 0 || j == i) {
                pascalTriangle[i][j] = 1;
            }
            //���������� ������ �������� � ������ ��������
            else {
                pascalTriangle[i][j] = pascalTriangle[i - 1][j - 1] + pascalTriangle[i - 1][j];
            }
        }
    }
}

// ����� ������������ ������� � ���� 
template <typename T>
void outputPascalsTriangleToFile(int n, T** pascalTriangle) {
    std::ofstream outputFile;
    outputFile.open("output.TXT");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            outputFile << pascalTriangle[i][j] << " ";
        }
        outputFile << std::endl;
    }
    outputFile.close();
}

//�������� ������ ������� (�������� 5 ����� �����������)
void testt()
{
    const int n = 5;
    long long** pascalTriangle = new long long* [n];
    createPascalTriangle(n, pascalTriangle);
    assert(pascalTriangle[0][0] == 1);

    assert(pascalTriangle[1][0] == 1);
    assert(pascalTriangle[1][1] == 1);

    assert(pascalTriangle[2][0] == 1);
    assert(pascalTriangle[2][1] == 2);
    assert(pascalTriangle[2][2] == 1);

    assert(pascalTriangle[3][0] == 1);
    assert(pascalTriangle[3][1] == 3);
    assert(pascalTriangle[3][2] == 3);
    assert(pascalTriangle[3][3] == 1);

    assert(pascalTriangle[4][0] == 1);
    assert(pascalTriangle[4][1] == 4);
    assert(pascalTriangle[4][2] == 6);
    assert(pascalTriangle[4][3] == 4);
    assert(pascalTriangle[4][4] == 1);

    for (int i = 0; i < n; i++) {
        delete[] pascalTriangle[i];
    }
    delete[] pascalTriangle;
}

#endif