#ifndef TESTPROJECT_H
#define TESTPROJECT_H
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>  
#include <fstream>

using namespace std;


//array -массив 
//size -размер
//nameF-имя файла 
//max min - максимальное и минимальное значение для заполнения рандомно

// функция заполнения массива <array> размера <size> рандомными числами в заданном диапозоне от <min > до <max> возможных значений включая их
template <typename T>
void FillArray(T* array, size_t size, size_t max, size_t min)
{
    T range = max - min;
    for (size_t i = 0; i < size; i++)
    {
        array[i] = static_cast<T>(rand()) / RAND_MAX * range + min;
    }
}


//пследовательный поиск элемента <element> в массиве <array> размера <size> (Возвращаем -1, если элемент не найден)
template <typename T>
long long findElement(const T* array, size_t size, const T& element) {
    size_t endE = size - 1;
    if (array[endE] == element)
    {return endE;
    }
    else if (array[0] == element){
        return 0;
    }
    else {
        for (size_t i = 0; i < size; i++) {
            if (array[i] == element) {
                return i; // Возвращаем индекс найденного элемента
            }
        }
        return -1;

    }
}


//вывод данных в бинарный файл NameF ( массив <array> размера <size>)
template <typename T>
void WriteToBin(T* array, size_t size, const std::string& NameF)
{
    std::ofstream file(NameF, std::ios::binary);
    file.write(reinterpret_cast<const char*>(&size), sizeof(size)); 
    file.write(reinterpret_cast<const char*>(array), sizeof(T) * size); 
    file.close();
}
/* Функция file.write() служит взятия из файла.Она принимает указатель на буфер,
    в который будут записаны считываемые данные, и количество байт, которое следует считать.

     В данном случае, функция reinterpret_cast<char*>() выполняет приведение типа указателя на
     переменную temp к типу char* .Это делается для того, чтобы можно было считать данные из файла
     как последовательность байтов.

         sizeof(temp) используется для получения размера переменной
         temp в байтах.Это нужно для определения количества байт, которые следует считать из файла.

   После выполнения этой функции, в переменной temp будет содержаться считанное значение из файла.*/

//проверка на сортировку массива <array> размера size
template<typename T>
bool chek_sorted(const T* array, size_t size)
{
    if (size == 0 || size == 1)
        return true;
    // Проверяем порядок сортировки: true - по возрастанию, false - по убыванию
    bool chek = array[1] > array[0]; 
    for (size_t i = 0; i < size - 1; i++) {
        if ((array[i] < array[i + 1]) != chek) {
            return false; 
        }
    }

    return true;
}


// вывод данных в текстовый файл NameF ( массив <array> размер <size>)
template<typename T>
void WriteToFile(const T* array, size_t size, const std::string& NameF)
{
    std::ofstream file(NameF);

    if (file.is_open())
    {
        for (size_t i = 0; i < size; i++)
        {
            file << array[i] << " ";
        }

        file.close();
    }
    else
    {
      cout << "Failed to open file for writing" << std::endl;
    }
}

//функция сортировки по возрастанию массива Array  размера size_t пузырьком
/// лучший: O(n)
/// худший: O(n2)
/// средний: O(n2) 
template <typename T>
void BubbleSort( T *array, size_t size) {
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = 0; j < size - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    // Обмен значений при выполнении условия
                    array[j] = array[j] + array[j + 1];
                    array[j + 1] = array[j] - array[j + 1];
                    array[j] = array[j] - array[j + 1];
                }
            }
        }
    }

//  функция для бинарного  поиска элемента <element> в массиве <array> размера <size> отсортированного по возрастанию (-1 Элемент не найден -2 неотсортирован массив)
template <typename T>
long long BinarySearch(const T* array, size_t size, const T& element) {

    size_t begin = 0;
    size_t endE = size - 1;
    if (chek_sorted(array,size) == false)
        return -2;
    else {
        if (array[endE] == element)
        {return endE ;
        }
        if (array[0] == element)
        {return 0;
        }
        else {
            while (begin <= endE) {
                size_t tap;

                tap = begin + (endE - begin) / 2;

                if (array[tap] == element) {
                    return tap;
                }
                if (array[tap] < element) {
                    begin = tap + 1;
                }
                else {
                    endE = tap - 1;
                }
            }

            return -1;
        }
    }
}

//интерп поиск элемента <element> в массиве <array> размера <size> интер-оная функуия (-1 если элемент не найден -2 неотсортирован массив) 
template <typename T>
long long InterpolationSearch(const T* array, size_t size, const T& element) {
    //начальная и конечная точки поиска
    size_t begin = 0, endE = size - 1;
    //пока элемент не найден
    if (array[endE] == element)
    {return endE;
    }
    else if (array[0] == element){
        return 0;
    }
    else {
   /*     if (check_sorted(array, size) == false)
            return -2;*/
        //else {
            while (begin <= endE && element >= array[begin] && element <= array[endE]) {

                size_t inter_pos;
                //найдем позицию поиска по формуле 
                inter_pos = begin + ((element - array[begin] / (array[endE] - array[begin])) * (endE - begin));

                if (array[inter_pos] == element) return inter_pos;

                (array[inter_pos] < element) ? begin = inter_pos + 1 : endE = inter_pos - 1;
            }

            return -1;
        }
    }

//лямбда-функция для определения шага для сортировки n- размер адрес -----
auto shellStep = [](size_t n) {
    return n / 2;
};

// функция для сортировки вставками массива array размера size с шагом temp в порядке возрастания 
template <typename T>
void interSort(T* array, size_t size,size_t temp) {
    for (size_t i = temp; i < size; i++) {
        size_t temp1 = array[i];
        size_t j;
        for (j = i; j >= temp && array[j - temp] > temp1; j -= temp1) {
            array[j] = array[j - temp];
        }
        array[j] = temp1;
    }
}

// функця сортировки массива array в порядке возрастания размера size методом Шелла
/// лучший: O(n2)
/// худший: O(n log n)
/// средний: O(n^3/2) 
template <typename T>
void shellSort( T* array, size_t size) 
{
    for (size_t temp = shellStep(size); temp > 0; temp = shellStep(temp))
    {
        interSort(array, size, temp);
    }
}
 
/// Функция merge объединяет два отсортированных подмассива array[l..m] и array[m+1..r] в один отсортированный массив
/// l - индекс начала подмассива, который нужно объединить.
/// m - индекс середины подмассива, разделяющий его на две части.
/// r - индекс конца подмассива
/// 
/// сделать не 2 а 1 буферный массив для записи!!!!!!!!!!  
template <typename T>
void merge( T* array,size_t l, size_t m, size_t r) {
  

    size_t n1 = m - l + 1; // Вычисляем размер первого подмассива
    size_t n2 = r - m; // Вычисляем размер второго подмассива

    T* L = new T[n1]; // Динамически выделяем память для временного массива L
    T* R = new T[n2]; // Динамически выделяем память для временного массива R

    // Копируем данные из основного массива во временные массивы
    memcpy(&array[k], &L[i], n1  * sizeof(T));                     //количество байт для копир size of t - размер типа  * n
    memcpy(&array[k], &R[j], n2 * sizeof(T));
    // Инициализируем индексы для обхода временных массивов и основного массива
    size_t i = 0, j = 0, k = l;

    // Слияние двух временных массивов в основной массив в порядке возрастания
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Добавляем оставшиеся элементы из первого временного массива  memcpy
    if (n1 - i > 0) {
        memcpy(&array[k], &L[i], (n1 - i) * sizeof(T));
        k += (n1 - i);
    }

    // Добавляем оставшиеся элементы из второго временного массива
    if (n2 - j > 0) {
        memcpy(&array[k], &R[j], (n2 - j) * sizeof(T));
    }
    delete[] L; // Очищаем временный массив L
    delete[] R; // Очищаем временный массив R
}


/// Функция mergeSort рекурсивно сортирует подмассив arr[l..r] используя функцию merge по возрастанию
/// l - индекс начала подмассива, который нужно объединить.
/// m - индекс середины подмассива, разделяющий его на две части.
/// r - индекс конца подмассива
/// лучший: O(n log n)
/// худший: O(n log n)
/// средний: O(n log n) 
template <typename T>
void mergeSort( T* array, size_t l,size_t r) {
    
    if (l >= r) {
        return; // Если подмассив состоит из одного элемента или менее, он считается отсортированным
    }

    size_t m = l + (r - l) / 2; // Находим середину подмассива

    // Рекурсивно вызываем mergeSort для левой и правой половин подмассива
    mergeSort(array, l, m);
    mergeSort(array, m + 1, r);

    // Объединяем две отсортированные части подмассива
    merge(array, l, m, r);
}


//
// Функция для разделения массива <array> и выполнения быстрой сортировки по возрастанию <low> индекс начала сортировки в массиве  <high> индекс конца сортировки в массиве
template<typename T>
int partition(T* array, size_t low, size_t high) {
    T pivot = array[high]; // Опорный элемент
    size_t i = (low - 1); // Индекс меньшего элемента

    for (size_t j = low; j <= high - 1; j++) {
        // Если текущий элемент меньше или равен опорному
        if (array[j] <= pivot) {
            i++; // Увеличиваем индекс меньшего элемента
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

// Функция для выполнения быстрой сортировки массива <array> по возрастнанию <low> 
// индекс начала сортировки в массиве  <high> индекс конца сортировки в массиве  опорный элемент-n
//Сложность быстрой сортировки(QuickSort) :
  // -В лучшем случае : O(n log n)
  // - В среднем случае : O(n log n)
  // - В худшем случае : O(n ^ 2)
template<typename T>
void quickSort(T* array, size_t low, size_t high) {
    if (low < high) {
        // Индекс разделения, arr[p] теперь на своем месте
        size_t p = partition(array, low, high);

        // Рекурсивно сортируем элементы до разделения и после разделения
        quickSort(array, low, p - 1);
        quickSort(array, p + 1, high);
    }
}

//Пирамидальная сортировка массива <array> по возрастанию n представляет собой размер массива array,
//а i является индексом элемента в массиве, который рассматривается как вершина пирамиды
//Пирамида (или куча) представляет собой структуру данных, у которой каждый узел (элемент массива)
//больше или равен своим дочерним элементам
template <typename T>
void heapify(T* array, size_t n, size_t i)
{
    size_t largest = i; // Инициализация переменной largest как i
    size_t l = 2 * i + 1; // Вычисление индекса левого потомка узла i в пирамиде
    size_t r = 2 * i + 2; // Вычисление индекса правого потомка узла i в пирамиде

    if (l < n && array[l] > array[largest]) // Проверка, что левый потомок существует и больше текущего largest
        largest = l; // Если условие выполняется, обновляем largest

    if (r < n && array[r] > array[largest]) // Проверка, что правый потомок существует и больше текущего largest
        largest = r; // Если условие выполняется, обновляем largest

    if (largest != i) // Проверка, что нарушено свойство пирамиды
    {
        swap(array[i], array[largest]); // Обмен значениями между узлом i и узлом largest
        heapify(array, n, largest); // Рекурсивный вызов heapify для поддерева с корнем в largest
    }
}
//Пирамидальная сортировка массива <array> по возрастанию n представляет собой размер массива array
//Сложность пирамидальной сортировки(HeapSort) :
  //  -В лучшем случае : O(n log n)
  //  - В среднем случае : O(n log n)
  //  - В худшем случае : O(n log n)
//После построения начальной пирамиды делается итерация по массиву, начиная с конца.
//-На каждом шаге максимальный элемент(который находится в корне пирамиды) обменивается с последним элементом.
//- Затем вызывается heapify для восстановления свойства пирамиды после извлечения максимума из корня.
//- Процесс повторяется, пока не будет отсортирован весь массив
template <typename T>
void heapSort(T* array, size_t n)
{
    for (int i = n / 2 - 1; i >= 0; i--) // Построение начальной пирамиды
        heapify(array, n, i); // Вызов функции heapify для каждого узла в пирамиде

    for (int i = n - 1; i >= 0; i--) // Итерация по элементам массива для извлечения максимумов
    {
        swap(array[0], array[i]); // Обмен значениями между корнем пирамиды и последним элементом
        heapify(array, i, 0); // Восстановление свойства пирамиды после извлечения максимума
    }
}



//проверка функции поиска элемента с помощью последовательного поиска
void check_sorted()
{

    double* double_mass_f1 = new double[4] {1.3, 3.9, 6.4, 6.61};
    assert(findElement(double_mass_f1, 4, 3.9) == 1);

    double* double_mass_f2 = new double[3] { 1.06, 1.05, 1.04 };
    assert(findElement(double_mass_f2, 3, 1.04) == 2);

    double* double_mass_f3 = new double[3] { 1.6, 1.5, 1.4 };
    assert(findElement(double_mass_f3, 3, 1.3) == -1);

    int* int_mass_f1 = new int[5] { 1, 2, 3, 4, 5 };
    assert(findElement(int_mass_f1, 5, 3) == 2);

    int* int_mass_f2 = new int[5] { 7, 6, 4, 3, 1 };
    assert(findElement(int_mass_f2, 5, 4) == -1);

    int* int_mass_f3 = new int[5] { 10, 20, 30, 40, 50 };
    assert(findElement(int_mass_f3, 5, 25) == -1);

    int* int_mass_f4 = new int[6] { 2, 4, 6, 8, 10, 12 };
    assert(findElement(int_mass_f4, 6, 6) == 2);

    int* int_mass_f5 = new int[6] { 2, 4, 6, 8, 10, 12 };
    assert(findElement(int_mass_f5, 6, 12) == 5);

}

//проверка функции проверки сортировки  
void check_sorted_assert()
{
    unsigned* int_mass_f = new unsigned[3] { 9, 8, 3 };
    assert(chek_sorted(int_mass_f, 3) == false);

    double* double_mass_f = new double[3] { 9.01, 9.002, 9.03 };
    assert(chek_sorted(double_mass_f, 3) == false);

    std::string* string_mass_f = new std::string[3]{ "aad", "aab", "aac" };
    assert(chek_sorted(string_mass_f, 3) == false);

    unsigned* int_mass_t = new unsigned[3] { 8, 9, 13 };
    assert(chek_sorted(int_mass_t, 3));

    double* double_mass_t = new double[3] { 1.01, 1.02, 1.03 };
    assert(chek_sorted(double_mass_t, 3));


    std::string* string_mass_t = new std::string[3]{ "aaa", "aab", "aac" };
    assert(chek_sorted(string_mass_t, 3));
}
//проверка функции проверки бинарной сортировки
void  check_binSerch_assert()
{
        int* int_mass_f1 = new int[5] { 1, 2, 3, 4, 5 };
        assert(BinarySearch(int_mass_f1, 5, 3) == 2);

        int* int_mass_f2 = new int[5] { 7, 6, 4, 3, 1 };
        assert(BinarySearch(int_mass_f2, 5, 4) == -1);

        int* int_mass_f21 = new int[5] { 7, 1, 4, 3, 1 };
        assert(BinarySearch(int_mass_f2, 5, 4) == -2);

        int* int_mass_f3 = new int[5] { 10, 20, 30, 40, 50 };
        assert(BinarySearch(int_mass_f3, 5, 25) == -1);

        int* int_mass_f4 = new int[6] { 2, 4, 6, 8, 10, 12 };
        assert(BinarySearch(int_mass_f4, 6, 6) == 2);

        double* double_mass_f1 = new double[4] {1.3, 3.9, 6.4, 6.61};
        assert(BinarySearch(double_mass_f1, 4, 3.9) == 1);

        double* double_mass_f2 = new double[3] { 1.06, 1.05, 1.04 };
        assert(BinarySearch(double_mass_f2, 3, 1.04) == 2);

        double* double_mass_f3 = new double[3] { 1.6, 1.5, 1.4 };
        assert(BinarySearch(double_mass_f3, 3, 1.3) == -1);

        int* int_mass_f6 = new int[5] { 1, 2, 3, 4, 5 };
        assert(BinarySearch(int_mass_f6, 5, 5) == 4);
    }

//функция проверки интер-онной сорттировки
void check_Inter_assert()
{
    int* int_mass_f1 = new int[5] { 1, 2, 3, 4, 5 };
    assert(InterpolationSearch(int_mass_f1, 5, 3) == 2);

    int* int_mass_f2 = new int[5] { 7, 6, 4, 3, 1 };
    assert(InterpolationSearch(int_mass_f2, 5, 4) == -1);

    int* int_mass_f3 = new int[5] { 1, 6, 4, 3, 1 };
    assert(InterpolationSearch(int_mass_f2, 5, 4) == -2);

    int* int_mass_f4 = new int[6] { 2, 4, 6, 8, 10, 12 };
    assert(InterpolationSearch(int_mass_f4, 6, 6) == 2);

    double* double_mass_f1 = new double[4] {1.3, 3.9, 6.4, 6.61};
    assert(InterpolationSearch(double_mass_f1, 4, 3.9) == 1);

    double* double_mass_f2 = new double[3] { 1.06, 1.05, 1.04 };
    assert(InterpolationSearch(double_mass_f2, 3, 1.04) == 2);

    double* double_mass_f3 = new double[3] { 1.6, 1.5, 1.4 };
    assert(InterpolationSearch(double_mass_f3, 3, 1.3) == -1);

    int* int_mass_f9 = new int[5] { 7, 6, 4, 3, 1 };
    assert(InterpolationSearch(int_mass_f9, 5, 1) == 4);
}

// проверка слиянием 
void TestMerge() {
    int* array1 = new int[6] { 7, 2, 6, 1, 0, 12 };
    int* array2 = new int[6] { 0, 1, 2, 6, 7, 12 };
    mergeSort(array1, 0, 5);
    assert(array1 == array2);

    double* array3 = new double[6] { 1.2, 0.2, 1.002, 1.01, 3.2, 2.08 };
    double* array4 = new double[6] { 0.2, 1.01, 1.002, 1.2, 2.08, 3.2 };
    mergeSort(array1, 0, 5);
    assert(array3 == array4);

    double* array5 = new double[6] { 9, 8, 7, 6, 5, 4 };
    double* array6 = new double[6] { 4, 5, 6, 7, 8, 9 };
    mergeSort(array1, 0, 5);
    assert(array5 == array6);

    int* array7 = new int[6] { 0, 1, 2, 6, 7, 12 };
    int* array8 = new int[6] { 0, 1, 2, 6, 7, 12 };
    shellSort(array1, 6);
    assert(array7 == array8);

    double* array9 = new double[6] { 9, 8, 8, 6, 4, 4 };
    double* array10 = new double[6] { 4, 4, 6, 8, 8, 9 };
    shellSort(array5, 6);
    assert(array9 == array10);

    delete[] array1, array2, array3, array4, array5, array6, array7, array8, array9, array10;
}

// проверка сортировки Пузырьком 
void TestBuble() {
    int* array1 = new int[6] { 7, 2, 6, 1, 0, 12 };
    int* array2 = new int[6] { 0, 1, 2, 6, 7, 12 };
    BubbleSort(array1, 6);
    assert(array1 == array2);

    double* array3 = new double[6] { 1.2, 0.2, 1.002, 1.01, 3.2, 2.08 };
    double* array4 = new double[6] { 0.2, 1.01, 1.002, 1.2, 2.08, 3.2 };
    BubbleSort(array3, 6);
    assert(array3 == array4);

    double* array5 = new double[6] { 9, 8, 7, 6, 5, 4 };
    double* array6 = new double[6] { 4, 5, 6, 7, 8, 9 };
    BubbleSort(array5, 6);
    assert(array5 == array6);

    int* array7 = new int[6] { 0, 1, 2, 6, 7, 12 };
    int* array8 = new int[6] { 0, 1, 2, 6, 7, 12 };
    shellSort(array1, 6);
    assert(array7 == array8);

    double* array9 = new double[6] { 9, 8, 8, 6, 4, 4 };
    double* array10 = new double[6] { 4, 4, 6, 8, 8, 9 };
    shellSort(array5, 6);
    assert(array9 == array10);

    delete[] array1, array2, array3, array4, array5, array6, array7, array8, array9, array10;
}

// проверка сортировки Шелла
void TestShell() {
    int* array1 = new int[6] { 7, 2, 6, 1, 0, 12 };
    int* array2 = new int[6] { 0, 1, 2, 6, 7, 12 };
    shellSort(array1, 6);
    assert(array1 == array2);

    double* array3 = new double[6] { 1.2, 0.2, 1.002, 1.01, 3.2, 2.08 };
    double* array4 = new double[6] { 0.2, 1.01, 1.002, 1.2, 2.08, 3.2 };
    shellSort(array3, 6);
    assert(array3 == array4);

    int* array7 = new int[6] { 0, 1, 2, 6, 7, 12 };
    int* array8 = new int[6] { 0, 1, 2, 6, 7, 12 };
    shellSort(array1, 6);
    assert(array7 == array8);

    double* array5 = new double[6] { 9, 8, 7, 6, 5, 4 };
    double* array6 = new double[6] { 4, 5, 6, 7, 8, 9 };
    shellSort(array5, 6);
    assert(array5 == array6);

    double* array9 = new double[6] { 9, 8, 8, 6, 4, 4 };
    double* array10 = new double[6] { 4, 4, 6, 8, 8, 9 };
    shellSort(array5, 6);
    assert(array9 == array10);

    delete[] array1, array2, array3, array4, array5, array6, array7, array8, array9, array10;
}

// проверка быстрой сортировки
void TestquickSort() {
    int* array1 = new int[6] { 7, 2, 6, 1, 0, 12 };
    int* array2 = new int[6] { 0, 1, 2, 6, 7, 12 };
    quickSort(array1, 0,5);
    assert(array1 == array2);

    double* array3 = new double[6] { 1.2, 0.2, 1.002, 1.01, 3.2, 2.08 };
    double* array4 = new double[6] { 0.2, 1.01, 1.002, 1.2, 2.08, 3.2 };
    quickSort(array1, 0, 5);
    assert(array3 == array4);

    int* array7 = new int[6] { 0, 1, 2, 6, 7, 12 };
    int* array8 = new int[6] { 0, 1, 2, 6, 7, 12 };
    quickSort(array1, 0, 5);
    assert(array7 == array8);

    double* array5 = new double[6] { 9, 8, 7, 6, 5, 4 };
    double* array6 = new double[6] { 4, 5, 6, 7, 8, 9 };
    quickSort(array1, 0, 5);
    assert(array5 == array6);

    double* array9 = new double[6] { 9, 8, 8, 6, 4, 4 };
    double* array10 = new double[6] { 4, 4, 6, 8, 8, 9 };
    quickSort(array1, 0, 5);
    assert(array9 == array10);

    delete[] array1, array2, array3, array4, array5, array6, array7, array8, array9, array10;
}

// проверка пиромидалной сортировки
void TestheapSort() {
    int* array1 = new int[6] { 7, 2, 6, 1, 0, 12 };
    int* array2 = new int[6] { 0, 1, 2, 6, 7, 12 };
    heapSort(array1, 6);
    assert(array1 == array2);

    double* array3 = new double[6] { 1.2, 0.2, 1.002, 1.01, 3.2, 2.08 };
    double* array4 = new double[6] { 0.2, 1.01, 1.002, 1.2, 2.08, 3.2 };
    heapSort(array3, 6);
    assert(array3 == array4);

    int* array7 = new int[6] { 0, 1, 2, 6, 7, 12 };
    int* array8 = new int[6] { 0, 1, 2, 6, 7, 12 };
    heapSort(array1, 6);
    assert(array7 == array8);

    double* array5 = new double[6] { 9, 8, 7, 6, 5, 4 };
    double* array6 = new double[6] { 4, 5, 6, 7, 8, 9 };
    heapSort(array5, 6);
    assert(array5 == array6);

    double* array9 = new double[6] { 9, 8, 8, 6, 4, 4 };
    double* array10 = new double[6] { 4, 4, 6, 8, 8, 9 };
    heapSort(array5, 6);
    assert(array9 == array10);

    delete[] array1, array2, array3, array4, array5, array6, array7, array8, array9, array10;
}


#endif 
