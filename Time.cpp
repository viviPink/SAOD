//Пинчукова Гертруда ИВТ-22
#include <chrono>
#include <iostream>
#include "modul_time.h"
#include <cassert>        

using namespace std;
using namespace std::chrono;

int main() {
	// проверка корректной работы проверки на сортировку
	chek_sorted_assert();

    unsigned arraySize;                                    //размер массива 
	int max_nam, min_nam;                                  // максимальное и минимальное значение элемента массива
	string NameF;                                          //название файла

//начальный размер массива
arraySize = 100;
//начальные значения для рассчета сред. знач. работы функций
double sred_file = 0;
double sred_sort = 0;
double sred_find = 0;
double sred_mass = 0;

//цикл работает для размерности массива до 10000000
while (arraySize < 10000000) {

	//устанавливаем начальные значения
		sred_file = 0;
		sred_sort = 0;
		sred_find = 0;
		sred_mass = 0;

    //цикл для 100 запусков
	for (int i = 0; i < 100; i++) {

		NameF = "txt.txt";
		//ввод размера массива
		max_nam = 100000;
		//минимальное число значения эл - та массива
		min_nam = 6;
		//выделение памяти под массив
		float* array = new float[arraySize];


		// начальная отметка времени для оценки времени заполнения массива
		auto t0 = steady_clock::now();
		//заполнение массива в заданном д-не
		FillArray(array, arraySize, max_nam, min_nam);
		// конечная отметка времени
		auto t1 = steady_clock::now();
		// преобразование времени (обычно наносекунды) в миллисекунды
		auto delta_mass = duration_cast<milliseconds>(t1 - t0);


		// начальная отметка времени для записи в бинарный файл
		auto t2 = steady_clock::now();
		//вывод массива в бинарный файл
		WriteToBin(array, arraySize, "floatArray.bin");
		// конечная отметка времени
		auto t3 = steady_clock::now();
		// преобразование времени (обычно наносекунды) в миллисекунды
		auto delta_file = duration_cast<milliseconds>(t3 - t2);


		// начальная отметка времени для проверки сортировки
		auto t4 = steady_clock::now();
		//проверка на сортировку
		chek_sorted(array, arraySize);
		// конечная отметка времени
		auto t5 = steady_clock::now();
		// преобразование времени (обычно наносекунды) в миллисекунды
		auto delta_sort = duration_cast<milliseconds>(t5 - t4);


		// начальная отметка времени для времени поиска жлемента
		auto t6 = steady_clock::now();
		int elementToFind = 5; // элемент, который нужно найти
		/*if (findElement(array, arraySize, elementToFind)) {
			cout << "Element  found in the array" << endl;
		}
		else {
			cout << "Element not found in the array" << endl;
		}*/
		findElement(array, arraySize, elementToFind);
		// конечная отметка времени
		auto t7 = steady_clock::now();
		// преобразование времени (обычно наносекунды) в миллисекунды
		auto delta_find = duration_cast<milliseconds>(t7 - t6);
		

		// сумма значений времени для 100 запусков 
		sred_file += delta_file.count();
		sred_sort += delta_sort.count();
		sred_find += delta_find.count();
		sred_mass += delta_mass.count();
	}

	cout << "Average time " << arraySize << " is: " << "file:" <<(sred_file / 100) << " " << "sort: " <<(sred_sort/100) << " " <<"find:" <<(sred_find/100) << " "<<"mass" <<(sred_mass/100)<<endl;
	arraySize *= 10;
}

}




















