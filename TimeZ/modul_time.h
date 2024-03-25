////Пинчукова Гертруда ИВТ-22
//#ifndef MODUL_TIME_H
//#define MODUL_TIME_H
//#include <string>
//#include <iostream>
//#include <iomanip>
//#include <cassert>  
//#include <fstream>
//
//using namespace std;
//
////array -массив 
////size -размер
////nameF-имя файла 
////max min - максимальное и минимальное значение для заполнения рандомно
//
//template<typename T>
//bool chek_sorted(const T* array, size_t size)
//{
//    if (array[1] > array[0]) {
//        // Проверка на сортировку по возрастанию (от меньшего к большему)
//        for (size_t i = 0; i < size - 1; i++) {
//            if (array[i] > array[i + 1]) {
//                return false;
//            }
//        }
//    }
//    else {
//        // Проверка на сортировку по убыванию (от большего к меньшему)
//        for (size_t i = 0; i < size - 1; i++) {
//            if (array[i] < array[i + 1]) {
//                return false;
//            }
//        }
//    }
//
//    return true;
//}
//
//
//
//// функция заполнения массива размера size рандомными числами в заданном диапозоне от мин до макс включая ?
//template <typename T>
//void FillArray(  T* array, size_t size, size_t max, size_t min)//не целое
//{
//    // Проверка, что тип T является либо вещественным, либо целочисленным
//    //static_cast<T>(rand()) - это явное преобразование результата  к типу T
//    T range= max - min;
//    for (size_t i = 0; i < size; i++)
//    {
//        array[i] = static_cast<T>(rand()) / RAND_MAX * range + min;
//    }
//}
//
//// вывод массива в консоль в консоль  
//template <typename T>
//void printArray(T* array, size_t size)
//{
//    for (size_t i = 0; i < size; i++)
//    {
//        cout << setprecision(2) << array[i] << " ";
//    }
//    cout << endl;
//}
//
//// функция поиска элемента в массиве    возвращать номер 
//template <typename T>
//bool findElement( const T* array, size_t size,  T element) {
//    for (size_t i = 0; i < size; i++) {
//        if (array[i] == element) {
//            return true; // элемент найден
//        }
//    }
//    return false; // элемент не найден
//}
//
//
////+текстовый
//// запись данных в бинарный файл NameF
//template <typename T>
//void WriteToBin(T* array, size_t size, const string& NameF)
//{
//    std::ofstream file(NameF, std::ios::binary);
//    file.write(reinterpret_cast<const char*>(&size), sizeof(size)); // (sieof) размер temp в байтах 
//    file.write(reinterpret_cast<const char*>(array), sizeof(T) * size); // Запись самого массива
//    file.close();
//}
///* Функция file.write() служит взятия из файла.Она принимает указатель на буфер,
//    в который будут записаны считываемые данные, и количество байт, которое следует считать.
//
//     В данном случае, функция reinterpret_cast<char*>() выполняет приведение типа указателя на
//     переменную temp к типу char* .Это делается для того, чтобы можно было считать данные из файла
//     как последовательность байтов.
//
//         sizeof(temp) используется для получения размера переменной
//         temp в байтах.Это нужно для определения количества байт, которые следует считать из файла.
//
//   После выполнения этой функции, в переменной temp будет содержаться считанное значение из файла.*/
//
//
//
////проверка функции проверки сортировки
//void chek_sorted_assert()
//{
//    unsigned* int_mass_t = new unsigned[3] { 8, 9, 13 };
//    assert(chek_sorted(int_mass_t, 3));
//
//    unsigned* int_mass_f = new unsigned[3] { 9, 8, 3 };
//    assert(chek_sorted(int_mass_f, 3) == 0);
//
//    double* double_mass_t = new double[3] { 1.01, 1.02, 1.03 };
//    assert(chek_sorted(double_mass_t, 3));
//
//    double* double_mass_f = new double[3] { 9.01, 9.002, 9.03 };
//    assert(chek_sorted(double_mass_f, 3)== 0);
//
//
//    std::string* string_mass_t = new std::string[3]{ "aaa", "aab", "aac" };
//    assert(chek_sorted(string_mass_t, 3));
//
//    std::string* string_mass_f = new std::string[3]{ "aad", "aab", "aac" };
//    assert(chek_sorted(string_mass_f, 3) == 0);
//   
//    
//}
//
//#endif




//Ïèí÷óêîâà Ãåðòðóäà ÈÂÒ-22
#ifndef MODUL_TIME_H
#define MODUL_TIME_H
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>  
#include <fstream>

using namespace std;

//array -ìàññèâ 
//size -ðàçìåð
//nameF-èìÿ ôàéëà 
//max min - ìàêñèìàëüíîå è ìèíèìàëüíîå çíà÷åíèå äëÿ çàïîëíåíèÿ ðàíäîìíî


//ïðîâåðêà îòñîðòèðîâàí ëè äèíàìè÷åñêèé ìàññèâ ñîðòèðîâêè ïî âîçðîñòàíèþ è óáûâàíèþ.
template<typename T>
bool chek_sorted(const T* array, unsigned size, const char mode = 'b')
//Çíà÷åíèå 'b' (ïî óìîë÷àíèþ) îçíà÷àåò, ÷òî ìàññèâ äîëæåí áûòü îòñîðòèðîâàí â âîçðàñòàþùåì ïîðÿäêå
{
    if (size == 0 || size == 1)
        return true;
    if (mode == 'l')
        //îòñîðòèðîâàí ëè ìàññèâ â ïîðÿäêå óáûâàíèÿ (îò áîëüøåãî ê ìåíüøåìó)
        for (unsigned i = 0; i < size - 1; i++) {
            if (array[i] < array[i + 1]) return false;
        }
    else
        for (unsigned i = 0; i < size - 1; i++) {
            if (array[i] > array[i + 1]) return false;
        }

    return true;
}


// ôóíêöèÿ çàïîëíåíèÿ ìàññèâà ðàíäîìíûìè ÷èñëàìè â çàäàííîì äèàïîçîíå
template <typename T>
void FillArray(T* array, unsigned size, int max, int min)
{
    // Ïðîâåðêà, ÷òî òèï T ÿâëÿåòñÿ ëèáî âåùåñòâåííûì, ëèáî öåëî÷èñëåííûì
    //static_cast<T>(rand()) - ýòî ÿâíîå ïðåîáðàçîâàíèå ðåçóëüòàòà  ê òèïó T
    static_assert(is_floating_point<T>::value || is_integral<T>::value,
        "Template type must be floating-point or integral.");

    T range = max - min;
    for (size_t i = 0; i < size; i++)
    {
        array[i] = static_cast<T>(rand()) / RAND_MAX * range + min;
    }
}

// âûâîä ìàññèâà â êîíñîëü â êîíñîëü  
template <typename T>
void printArray(T* array, unsigned size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << setprecision(2) << array[i] << " ";
    }
    cout << endl;
}

// ôóíêöèÿ ïîèñêà ýëåìåíòà â ìàññèâå
template <typename T>
bool findElement(const T* array, unsigned size, const int element) {
    for (unsigned i = 0; i < size; i++) {
        if (array[i] == element) {
            return true; // ýëåìåíò íàéäåí
        }
    }
    return false; // ýëåìåíò íå íàéäåí
}



// çàïèñü äàííûõ â áèíàðíûé ôàéë
template <typename T>
void WriteToBin(T* array, unsigned size, const std::string& NameF)
{
    std::ofstream file(NameF, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&size), sizeof(size)); // (sieof) ðàçìåð temp â áàéòàõ 
    file.write(reinterpret_cast<const char*>(array), sizeof(T) * size); // Çàïèñü ñàìîãî ìàññèâà
    file.close();
}
/* Ôóíêöèÿ file.write() ñëóæèò âçÿòèÿ èç ôàéëà.Îíà ïðèíèìàåò óêàçàòåëü íà áóôåð,
    â êîòîðûé áóäóò çàïèñàíû ñ÷èòûâàåìûå äàííûå, è êîëè÷åñòâî áàéò, êîòîðîå ñëåäóåò ñ÷èòàòü.

     Â äàííîì ñëó÷àå, ôóíêöèÿ reinterpret_cast<char*>() âûïîëíÿåò ïðèâåäåíèå òèïà óêàçàòåëÿ íà
     ïåðåìåííóþ temp ê òèïó char* .Ýòî äåëàåòñÿ äëÿ òîãî, ÷òîáû ìîæíî áûëî ñ÷èòàòü äàííûå èç ôàéëà
     êàê ïîñëåäîâàòåëüíîñòü áàéòîâ.

         sizeof(temp) èñïîëüçóåòñÿ äëÿ ïîëó÷åíèÿ ðàçìåðà ïåðåìåííîé
         temp â áàéòàõ.Ýòî íóæíî äëÿ îïðåäåëåíèÿ êîëè÷åñòâà áàéò, êîòîðûå ñëåäóåò ñ÷èòàòü èç ôàéëà.

   Ïîñëå âûïîëíåíèÿ ýòîé ôóíêöèè, â ïåðåìåííîé temp áóäåò ñîäåðæàòüñÿ ñ÷èòàííîå çíà÷åíèå èç ôàéëà.*/



   //ïðîâåðêà ôóíêöèè ïðîâåðêè ñîðòèðîâêè
void chek_sorted_assert()
{
    unsigned* int_mass_t = new unsigned[3] { 8, 9, 13 };
    assert(chek_sorted(int_mass_t, 3));

    unsigned* int_mass_f = new unsigned[3] { 9, 8, 3 };
    assert(chek_sorted(int_mass_f, 3) == false);

    double* double_mass_t = new double[3] { 1.01, 1.02, 1.03 };
    assert(chek_sorted(double_mass_t, 3));

    double* double_mass_f = new double[3] { 9.01, 9.002, 9.03 };
    assert(chek_sorted(double_mass_f, 3) == false);


    std::string* string_mass_t = new std::string[3]{ "aaa", "aab", "aac" };
    assert(chek_sorted(string_mass_t, 3));

    std::string* string_mass_f = new std::string[3]{ "aad", "aab", "aac" };
    assert(chek_sorted(string_mass_f, 3) == false);


}

#endif