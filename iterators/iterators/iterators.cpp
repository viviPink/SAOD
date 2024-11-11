#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // for_each()
    vector<int> numbers = { 1, 2, 3, 4, 5 };

    // Применяем функцию-лямбду к каждому элементу вектора
    // - numbers.begin() - итератор на первый элемент
    // - numbers.end()   - итератор на конец вектора
    // - Лямбда-функция принимает int& - ссылка на элемент типа int
    //не возращает а просто выводит результат поэлиметно 
    for_each(numbers.begin(), numbers.end(), [](int& num) {
        num *= 2;
        });

    // Выводим результат
    cout << "for_each():\n";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << std::endl; //  2 4 6 8 10

    //  any_of(), all_of(), none_of()
    numbers = { 1, 2, 3, 4, 5 };

    // Проверяем есть ли в векторе хотя бы один элемент больше3
     // - numbers.begin() - итератор на первый элемент
     // - numbers.end()   - итератор на конец вектора
     // - Лямбда-функция принимает int& - ссылка на элемент типа int
    // возращается boolean
    bool hasElementGreaterThan3 = std::any_of(numbers.begin(), numbers.end(), [](int num) {
        //тип данных булеан
        return num > 3;
        });
    cout << "\nany_of() :\nelement > than 3: " << std::boolalpha << hasElementGreaterThan3 << std::endl; // true

    // Проверяем, все ли элементы вектора меньше 6
      // Проверяем есть ли в векторе хотя бы один элемент больше3
     // - numbers.begin() - итератор на первый элемент
     // - numbers.end()   - итератор на конец вектора
     // - Лямбда-функция принимает int& - ссылка на элемент типа int
    // возращается boolean
    bool allLessThan6 = std::all_of(numbers.begin(), numbers.end(), [](int num) {
        return num < 6;
        });
    std::cout << "all_of():\nAll elements < than 6: " << std::boolalpha << allLessThan6 << std::endl; // true

    // Проверяем, нет ли в векторе элементов, равных 6
      // Проверяем есть ли в векторе хотя бы один элемент больше3
     // - numbers.begin() - итератор на первый элемент
     // - numbers.end()   - итератор на конец вектора
     // - Лямбда-функция принимает int& - ссылка на элемент типа int
    // возращается boolean
    bool noneEqual6 = none_of(numbers.begin(), numbers.end(), [](int num) {
        return num == 6;
        });
    cout << "none_of():\nNone of the elements = 6: " << std::boolalpha << noneEqual6 << std::endl; // true

    // Пример использования transform()
    numbers = { 1, 2, 3, 4, 5 };
    vector<int> squares(numbers.size());

 
    // Применяем функцию-лямбду к каждому элементу вектора и сохраняем результат в другой вектор
      // Проверяем есть ли в векторе хотя бы один элемент больше3
     // - squares.begin() - итератор на первый элемент
     // - numbers.end()   - итератор на конец вектора
     // - Лямбда-функция принимает int& - ссылка на элемент типа int
    // возращается int
    transform(numbers.begin(), numbers.end(), squares.begin(), [](int num) {
        return num * num  ;
        });

    cout << "\ntransform() :";
    for (int num : squares) {
        cout << num << " ";
    }
    cout << endl; // Вывод: 1 4 9 16 25

    // Пример использования copy_if()
    numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vector<int> evenNumbers;

    // Копируем в новый вектор только четные элементы
    // - numbers.begin() - итератор на первый элемент
    // - numbers.end() - итератор на конец вектора
    // - back_inserter(evenNumbers) - вставляет элементы в конец вектора evenNumbers
    // - Лямбда-функция, которая принимает int num и возвращает true, если num четное
    copy_if(numbers.begin(), numbers.end(), back_inserter(evenNumbers), [](int num) {
        /*int d = rand();
        return d>20;*/
        return num % 2 == 0;
        });

    cout << "\ncopy_if():";
    for (int num : evenNumbers) {
        cout << num << " ";
    }
    cout << std::endl; // 2 4 6 8 10

    return 0;
}
