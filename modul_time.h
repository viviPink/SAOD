//��������� �������� ���-22
#ifndef MODUL_TIME_H
#define MODUL_TIME_H
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>  
#include <fstream>

using namespace std;

//array -������ 
//size -������
//nameF-��� ����� 
//max min - ������������ � ����������� �������� ��� ���������� ��������


//�������� ������������ �� ������������ ������ ���������� �� ����������� � ��������.
template<typename T>
bool chek_sorted(const T* array, unsigned size, const char mode = 'b')
//�������� 'b' (�� ���������) ��������, ��� ������ ������ ���� ������������ � ������������ �������
{
	if (size == 0 || size == 1)
		return true;
	if (mode == 'l')
    //������������ �� ������ � ������� �������� (�� �������� � ��������)
		for (unsigned i = 0; i < size - 1; i++) {
			if (array[i] < array[i + 1]) return false;
		}
	else
		for (unsigned i = 0; i < size - 1; i++) {
			if (array[i] > array[i + 1]) return false;
		}

	return true;
}


// ������� ���������� ������� ���������� ������� � �������� ���������
template <typename T>
void FillArray( T* array, unsigned size, int max, int min)
{
    // ��������, ��� ��� T �������� ���� ������������, ���� �������������
    //static_cast<T>(rand()) - ��� ����� �������������� ����������  � ���� T
    static_assert(is_floating_point<T>::value || is_integral<T>::value,
        "Template type must be floating-point or integral.");

    T range= max - min;
    for (size_t i = 0; i < size; i++)
    {
        array[i] = static_cast<T>(rand()) / RAND_MAX * range + min;
    }
}

// ����� ������� � ������� � �������  
template <typename T>
void printArray(T* array, unsigned size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << setprecision(2) << array[i] << " ";
    }
    cout << endl;
}

// ������� ������ �������� � �������
template <typename T>
bool findElement(const T* array, unsigned size, const int element) {
    for (unsigned i = 0; i < size; i++) {
        if (array[i] == element) {
            return true; // ������� ������
        }
    }
    return false; // ������� �� ������
}



// ������ ������ � �������� ����
template <typename T>
void WriteToBin(T* array, unsigned size, const std::string& NameF)
{
    std::ofstream file(NameF, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&size), sizeof(size)); // (sieof) ������ temp � ������ 
    file.write(reinterpret_cast<const char*>(array), sizeof(T) * size); // ������ ������ �������
    file.close();
}
/* ������� file.write() ������ ������ �� �����.��� ��������� ��������� �� �����,
    � ������� ����� �������� ����������� ������, � ���������� ����, ������� ������� �������.

     � ������ ������, ������� reinterpret_cast<char*>() ��������� ���������� ���� ��������� ��
     ���������� temp � ���� char* .��� �������� ��� ����, ����� ����� ���� ������� ������ �� �����
     ��� ������������������ ������.

         sizeof(temp) ������������ ��� ��������� ������� ����������
         temp � ������.��� ����� ��� ����������� ���������� ����, ������� ������� ������� �� �����.

   ����� ���������� ���� �������, � ���������� temp ����� ����������� ��������� �������� �� �����.*/



//�������� ������� �������� ����������
void chek_sorted_assert()
{
    unsigned* int_mass_t = new unsigned[3] { 8, 9, 13 };
    assert(chek_sorted(int_mass_t, 3));

    unsigned* int_mass_f = new unsigned[3] { 9, 8, 3 };
    assert(chek_sorted(int_mass_f, 3) == false);

    double* double_mass_t = new double[3] { 1.01, 1.02, 1.03 };
    assert(chek_sorted(double_mass_t, 3));

    double* double_mass_f = new double[3] { 9.01, 9.002, 9.03 };
    assert(chek_sorted(double_mass_f, 3)== false);


    std::string* string_mass_t = new std::string[3]{ "aaa", "aab", "aac" };
    assert(chek_sorted(string_mass_t, 3));

    std::string* string_mass_f = new std::string[3]{ "aad", "aab", "aac" };
    assert(chek_sorted(string_mass_f, 3) == false);
   
    
}

#endif
