//Пинчукова Гертруда ИВТ-22
#include <chrono>
#include <iostream>
#include "TestProject.h"
#include <cassert>        

using namespace std;
using namespace std::chrono;



int main() {
	// проверка корректной работы проверки на сортировку
	//chek_sorted_assert();
	//chek_binSerch_assert();



	size_t arraySize;                                        //размер массива 
	size_t max_nam, min_nam;                                 // максимальное и минимальное значение элемента массива
	string NameF;                                            //название файла
	int g=5;
	size_t bi;
	size_t find;
	//начальный размер массива
	arraySize = 10000;
	//начальные значения для рассчета сред. знач. работы функций
	double sred_file = 0;
	double sred_sort = 0;
	double sred_find = 0;
	double sred_mass = 0;
	double sred_find_Bin = 0;
	double sred_find_inter = 0;
	double sred_buble_sort = 0;
	double sred_merge_sort = 0;


	//цикл работает для размерности массива до 10000000
	while (arraySize < 40000000) {

		//устанавливаем начальные значения
		sred_file = 0;
		sred_sort = 0;
		sred_find = 0;
		sred_mass = 0;
		sred_find_Bin = 0;
	    sred_buble_sort = 0;
		sred_merge_sort = 0;
		

			NameF = "txt.txt";
			//ввод размера массива
			max_nam = 100000;
			//минимальное число значения эл - та массива
			min_nam = 6;
			//выделение памяти под массив
			float* array = new float[arraySize];


			//// начальная отметка времени для оценки времени заполнения массива
			//auto t0 = steady_clock::now();
			////цикл для 100 запусков
			//for (int i = 0; i < g; i++) {
			//	//заполнение массива в заданном д-не
			//	FillArray(array, arraySize, max_nam, min_nam);
			//}
			//// конечная отметка времени
			//auto t1 = steady_clock::now();
			//// преобразование времени (обычно наносекунды) в миллисекунды
			//auto delta_mass = duration_cast<seconds>(t1 - t0);
			//sred_mass = delta_mass.count();


			//// начальная отметка времени для записи в бинарный файл
			//auto t2 = steady_clock::now();
			////цикл для 100 запусков
			//for (int i = 0; i < g; i++) {
			//	//вывод массива в файл
			//	WriteToFile(array, arraySize, "Array.txt");
			//}
			//// конечная отметка времени
			//auto t3 = steady_clock::now();
			//// преобразование времени (обычно наносекунды) в секунды
			//auto delta_file = duration_cast<seconds>(t3 - t2);
			//sred_file = delta_file.count();

			//// начальная отметка времени для проверки сортировки
			//auto t4 = steady_clock::now();
			////цикл для 100 запусков
			//for (int i = 0; i < g; i++) {
			//	//проверка на сортировку
			//	chek_sorted(array, arraySize);
			//}
			//// конечная отметка времени
			//auto t5 = steady_clock::now();
			//// преобразование времени (обычно наносекунды) в секунды
			//auto delta_sort = duration_cast<seconds>(t5 - t4);
			//sred_sort += delta_sort.count();

			//// начальная отметка времени для времени поиска жлемента
			//auto t6 = steady_clock::now();
			////цикл для 100 запусков
			//for (int i = 0; i < g; i++) {
			//	float elementToFind = 5.0; // элемент, который нужно найти
			//	/*if (findElement(array, arraySize, elementToFind)) {
			//		cout << "Element  found in the array" << endl;
			//	}
			//	else {
			//		cout << "Element not found in the array" << endl;
			//	}*/
			//	//cout << findElement(array, arraySize, elementToFind) << endl;
			//	find=findElement(array, arraySize, elementToFind);
			//}
			//// конечная отметка времени
			//auto t7 = steady_clock::now();
			//// преобразование времени (обычно наносекунды) в миллисекунды
			//auto delta_find = duration_cast<seconds>(t7 - t6);
			//sred_find += delta_find.count();




			// начальная отметка времени для сортировки пузырьком
			auto t6 = steady_clock::now();
			//цикл для 100 запусков
			for (int i = 0; i < g; i++) {
				FillArray(array, arraySize, max_nam, min_nam);
				//сортировка пузырьком 
				BubbleSort(array, arraySize);
				sred_buble_sort;
				// конечная отметка времени
				auto t7 = steady_clock::now();
				// преобразование времени (обычно наносекунды) в секунды
				auto delta_find = duration_cast<seconds>(t7 - t6);
				sred_buble_sort += delta_find.count();

			}

			// начальная отметка времени для сортировки пузырьком
			auto t8 = steady_clock::now();
			//цикл для 100 запусков
			for (int i = 0; i < g; i++) {
				FillArray(array, arraySize, max_nam, min_nam);
				mergeSort(array, 0, arraySize - 1);
				// конечная отметка времени
				auto t9= steady_clock::now();
				// преобразование времени  в секунды
				auto delta_find = duration_cast<seconds>(t9 - t8);
				sred_merge_sort += delta_find.count();
			}




			////вывод массива в файл
			//WriteToFile(array, arraySize, "Array.txt");

			//// начальная отметка времени для времени поиска жлемента
			//auto t8 = steady_clock::now();
			////цикл для 100 запусков
			//for (int i = 0; i < g; i++) {
			//	float element = 5.0; // элемент, который нужно найти
			//	//cout << BinarySearch(array, arraySize, element) << endl;

			//	bi = BinarySearch(array, arraySize, element);
			//}
			//// конечная отметка времени
			//auto t9 = steady_clock::now();
			//// преобразование времени (обычно наносекунды) в миллисекунды
			//auto delta_find_bi = duration_cast<seconds>(t9 - t8);
			//sred_find_Bin += delta_find_bi.count();



			//// начальная отметка времени для времени поиска жлемента
			//auto t10 = steady_clock::now();
			////цикл для 100 запусков
			//for (int i = 0; i < g; i++) {
			//	float element = 5.0; // элемент, который нужно найти
			//	//cout << BinarySearch(array, arraySize, element) << endl;

			//	bi = InterpolationSearch(array, arraySize, element);
			//}
			//// конечная отметка времени
			//auto t11 = steady_clock::now();
			//// преобразование времени (обычно наносекунды) в миллисекунды
			//auto delta_find_inter = duration_cast<seconds>(t11 - t10);
			//sred_find_inter += delta_find_inter.count();


		//cout << "Average time " << arraySize << " is: " << "file:" << (sred_file / 100) << " " << "sort: " << (sred_sort / 100) << " " << "find:" << (sred_find / 100) <<" "<<"find bin : "<<(sred_find_Bin/100) << " " << "mass : " << (sred_mass / 100)<<" "<<"inter : "<< (sred_find_inter/100) << endl;
			cout << "Average time " << arraySize << " is... " << "buble: " << (sred_buble_sort / 5)<<" "<< "merge: " << (sred_merge_sort / 5);
        
			delete[] array;
		if (arraySize < 1000000) {
			arraySize *= 10;
		}
		else arraySize += 1000000;
	
	
	}

}



















