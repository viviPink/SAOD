#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

/// <summary>
/// шаблонный класс для кучи min-heap
/// корень-максим элемент 
/// куча это 
/// завершенное днерево это
/// </summary>
template<typename T>
class MinHeap {
private:
    /// <summary>
    /// Массив для хранения элементов кучи
    /// </summary>
    vector<T> heap;

    /// <summary>
    /// Вспомогательная функция для "подъема" элемента
    /// проверяет что вставляемый элемент меньше родителя
    /// и меняет местами с родителем если true
    /// BigO
    /// лучший:O(1)
    /// средний:O(n)
    /// худший:O( n)
    /// </summary>
    /// <param name="index">позиция элемента</param>
    void heapifyUp(size_t index) {
        //heapifyUpp(index);

        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            //Если элемент уже больше родителя, то выходим
            if (heap[index] >= heap[parentIndex]) return;
            // Меняем местами
            swap(heap[index], heap[parentIndex]);
            // Переходим к родителю
            index = parentIndex;
        }
    }


    /// <summary>
    ///  Вспомогательная функция для "опускания" элемента в минимальной куче
    /// BigO
    /// лучший:O(1)
    /// средний:O(n)
    /// худший:O(n)
    /// </summary>
    /// <param name="index">позиция элемента</param>
    void heapifyDown(size_t index) {
        //heapifyDownn(index);

        int leftChild, rightChild, smallest; // Индексы для левого и правого детей, а также для наименьшего
        // Проверяем, есть ли элемент под индексом, пока он менее размера кучи
        while (index < heap.size()) {
            leftChild = 2 * index + 1;  // Нахождение индекса левого ребенка
            rightChild = 2 * index + 2; // Нахождение индекса правого ребенка
            smallest = index; // Инициализируем smallest текущим индексом
            // Находим наименьший элемент среди родителя и его деток(маленькие такие миленькие)
            if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
                smallest = leftChild; // Обновляем smallest, если левый baby меньше
            }
            if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
                smallest = rightChild; // Обновляем smallest, если правый baby меньше
            }
            // Если родитель меньше или равен наименьшему из baby, выходим из функции
            if (smallest == index) return;
            // Меняем местами текущий элемент с наименьшим из детей
            swap(heap[index], heap[smallest]);
            // Переходим к наименьшему элементу для дальнейшей проверки
            index = smallest;
        }
    }

    //класс итератора для кучи 
    class Iterator {
    private:
        // Ссылка на кучу и текущий индекс
        MinHeap<T>& minHeap;
        size_t index;

    public:
        // Конструктор итератора
        Iterator(MinHeap<T>& heap, size_t idx) : minHeap(heap), index(idx) {}

        // Оператор разыменования для получения элемента
        T& operator*() {
            return heap[index];
        }

        // Оператор перегрузки для итератора ++
        Iterator& operator++() {
            ++index; // Увеличиваем индекс
            return *this; // Возвращаем текущее значение итератора
        }

        //оператор сравнения равенство
        bool operator==(const Iterator& other) const {
            return &heap == &other.minHeap && index == other.index;
        }
        
        // Оператор сравнения неравенство
        bool operator!=(const Iterator& other) const {
            return index != other.index; // Сравниваем индексы
        }

        //проверка на наличичие следующего элемента 
        bool HasNext() const{
            return index != heap.size();
    }
         //возращает значение текущ иттератора
         T& data() const {
             return heap[index];
        }


         //исключение бросается в случае если нет след элемента
         Iterator& next() {
             if (!HasNext()) {
                 throw out_of_range("Iter null");
             }
             ++index;
             return *this;
         }

         //сброс иттератора 
         void reset() {
             index = 0;
         }
         
    };


public:
    //конструктор класса без параметров 
    MinHeap() {};

    /// <summary>
    /// конструктор класса кучи с параметрами
    /// </summary>
    /// <param name="data">ссылка на константный вектор
    ///  heap векрот в виде мин кучи </param>
    MinHeap(const vector<int>& data) : heap (data){
        buildMinHeap();
    };
    
    /// <summary>
    /// Строим минимальную кучу
    /// </summary>
    void buildMinHeap() {
        // Начинаем с последнего не листового узла и "просеиваем" вниз
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // Метод, возвращающий итератор на начало
    Iterator begin() {
        return Iterator(*this, 0); // Возвращаем итератор на первый элемент
    }

    // Метод, возвращающий итератор на конец
    Iterator end() {
        return Iterator(*this, heap.size()); // Возвращаем итератор за последний элемент
    }

    /// <summary>
    /// Метод для добавления элемента
    /// BigO
    /// лучший:O(1)
    /// средний:O(log n)
    /// худший:O(log n)
    /// </summary>
    /// <param name="value"> значегние элемента</param>
    void insert(T value) {
        heap.push_back(value); // Добавляем элемент в конец массива
        heapifyUp(heap.size() - 1); // Поднимаем элемент вверх
    }

    /// <summary>
    /// Метод для удаления минимального элемента
    /// лучший:O(1)
    /// средний:O(1)
    /// худший:O(1)
    /// </summary>
    /// <returns>возращаем мин элемент</returns>
    T extractMin() {
        //extractMini();
        if (heap.empty()) throw std::runtime_error("Heap is empty.");
        T minValue = heap[0]; // Сохраняем минимальный элемент
        heap[0] = heap.back(); // Заменяем его последним элементом
        heap.pop_back(); // Удаляем последний элемент
        heapifyDown(0); // Опускаем новый корень
        return minValue; // Возвращаем минимальный элемент
    }


    /// <summary>
    /// Метод для доступа к минимальному элементу
    /// BigO
    /// лучший:O(1)
    /// средний:O(1)
    /// худший:O(1)
    /// </summary>
    /// <returns>Возвращаем корень</returns>
    T peek() const {
        if (heap.empty()) throw std::runtime_error("Heap is empty.");
        return heap[0]; // Возвращаем корень
    }


    /// <summary>
    /// Метод для получения размера кучи
    ///  BigO
    /// лучший:O(1)
    /// средний:O(1)
    /// худший:O(1)
    /// </summary>
    /// <returns>Возвращаем размер массива</returns>
    size_t size() const {
        return heap.size(); // Возвращаем размер массива
    }

    /// <summary>
    /// Метод для проверки, пуста ли куча
    /// BigO
    /// лучший:O(1)
    /// средний:O(1)
    /// худший:O(1)
    /// </summary>
    /// <returns>true если пуста</returns>
    bool isEmpty() const {
        return heap.empty(); // Проверяем на пустоту массива
    }

    // Для тестирования: возвращаем текущее состояние кучи и ее размер
    const vector<T>& getHeap() const {
        return heap;
    }



    /// <summary>
    /// Метод для получения массива, представляющего кучу
    /// BigO
    /// лучший:O(1)
    /// средний:O(1)
    /// худший:O(1)
    /// </summary>
    /// <returns>Возвращаем массив</returns>
    const vector<T>& toArray() const {
        return heap; // Возвращаем массив
    }

    ///// <summary>
    ///// класс итератора для кучи 
    ///// не испотзуя станд библ 
    ///// </summary>
    //class Iterator {
    //private:
    //    // Итератор на текущий элемент вектора элементов
    //    typename vector<T>::iterator current;
    //public:
    //    // Конструктор итератора, принимающий итератор начала вектора
    //    Iterator(typename vector<T>::iterator start) : current(start) {}
    //    // Оператор разыменования
    //    T& operator*() {
    //        return *current; // Позволяет получить доступ к текущему элементу
    //    }
    //    // Оператор инкрементации (префиксный)
    //    Iterator& operator++() {
    //        ++current; // Переход к следующему элементу
    //        return *this; // Возвращение текущего итератора
    //    }
    //    // Оператор неравенства
    //    bool operator!=(const Iterator& other) const {
    //        return current != other.current; // Проверка на неравенство двух итераторов
    //    }
    //    // Возвращает итератор на первый элемент
    //    Iterator begin() {
    //        return Iterator(heap.begin());
    //    }
    //    // Возвращает итератор на элемент, следующий за последним
    //    Iterator end() {
    //        return Iterator(heap.end());
    //    }
    //};

};



/// <summary>
///  Вспомогательная функция для "опускания" элемента в минимальной куче
/// BigO
/// лучший:O(1)
/// средний:O(log n)
/// худший:O(log n)
/// </summary>
/// <param name="index">позиция элемента</param>
// template<typename T>
//void heapifyDownn(int index) {
//    int leftChild, rightChild, smallest; // Индексы для левого и правого детей, а также для наименьшего
//    // Проверяем, есть ли элемент под индексом, пока он менее размера кучи
//    while (index < heap.size()) {
//        leftChild = 2 * index + 1;  // Нахождение индекса левого ребенка
//        rightChild = 2 * index + 2; // Нахождение индекса правого ребенка
//        smallest = index; // Инициализируем smallest текущим индексом
//        // Находим наименьший элемент среди родителя и его деток(маленькие такие миленькие)
//        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
//            smallest = leftChild; // Обновляем smallest, если левый baby меньше
//        }
//        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
//            smallest = rightChild; // Обновляем smallest, если правый baby меньше
//        }
//        // Если родитель меньше или равен наименьшему из baby, выходим из функции
//        if (smallest == index) return;
//        // Меняем местами текущий элемент с наименьшим из детей
//        swap(heap[index], heap[smallest]);
//        // Переходим к наименьшему элементу для дальнейшей проверки
//        index = smallest;
//    }
//}

/// <summary>
    /// Вспомогательная функция для "подъема" элемента
    /// проверяет что вставляемый элемент меньше родителя
    /// и меняет местами с родителем если true
    /// BigO
    /// лучший:O(1)
    /// средний:O(log n)
    /// худший:O(log n)
    /// </summary>
    /// <param name="index">позиция элемента</param>
//template<typename T>
//void heapifyUpp(int index) {
//    while (index > 0) {
//        int parentIndex = (index - 1) / 2;
//        //Если элемент уже больше родителя, то выходим
//        if (heap[index] >= heap[parentIndex]) return;
//        // Меняем местами
//        swap(heap[index], heap[parentIndex]);
//        // Переходим к родителю
//        index = parentIndex;
//    }
//}


    /// <summary>
    /// Метод для удаления минимального элемента
    /// лучший:O(1)
    /// средний:O(1)
    /// худший:O(1)
    /// </summary>
    /// <returns>возращаем мин элемент</returns>
//template<typename T>
//T extractMini() {
//    if (heap.empty()) throw std::runtime_error("Heap is empty.");
//    T minValue = heap[0]; // Сохраняем минимальный элемент
//    heap[0] = heap.back(); // Заменяем его последним элементом
//    heap.pop_back(); // Удаляем последний элемент
//    heapifyDown(0); // Опускаем новый корень
//    return minValue; // Возвращаем минимальный элемент
//}


/// <summary>
/// BigO
/// лучший:O(1)
/// средний:O(n log n)
/// худший:O(n log n)
/// алгоритм сортировки с использованием минимальной кучи (MinHeap) от наимен к наибольшему
/// 
///  Сначала создается пустая минимальная куча heap.
/// Каждый элемент из переданного массива array добавляется в кучу 
/// с помощью метода insert
/// Создается пустой вектор sortedArray
///Затем в цикле, пока куча не пуста, извлекаются минимальные элементы 
/// из кучи(минимальный элемент всегда находится на корневом уровне)
///Каждый извлеченный элемент добавляется в sortedArray
/// </summary>
/// <param name="array">массив</param>
/// <returns>отсортированный массив</returns>
template<typename T>
vector<T> heapSort(vector<T> array) {
    MinHeap<T> heap;
    for (const auto& item : array) {
        heap.insert(item); // Вставляем каждый элемент в кучу
    }
    vector<T> sortedArray;
    while (!heap.isEmpty()) {
        sortedArray.push_back(heap.extractMin()); // Извлекаем минимальные элементы
    }
    return sortedArray; // Возвращаем отсортированный массив
}

//
///// <summary>
///// класс очередь с приоритетом, реализованную с использованием минимальной кучи (MinHeap)
//  высший приоритет имеет минимальный элемент
///// </summary>
///// <typeparam name="T"></typeparam>
//template<typename T>
//class PriorityQueue {
//private:
//    MinHeap<T> minHeap; // Используем MinHeap для хранения элементов
//
//public:
//
//    /// <summary>
//    /// Вставляем элемент в кучу
//    /// </summary>
//    /// <param name="value">значение элемента</param>
//    void push(T value) {
//        minHeap.insert(value);
//    }
//
//    /// <summary>
//    /// Извлекаем минимальный элемент
//    /// </summary>
//    /// <returns>минимальный элемент</returns>
//    T pop() {
//        return minHeap.extractMin();
//    }
//
//    /// <summary>
//    /// Возвращаем минимальный элемент
//    /// </summary>
//    /// <returns>vbybvfkmysq 'ktvtyn</returns>
//    T top() const {
//        return minHeap.peek();
//    }
//
//    /// <summary>
//    /// Проверка на пустоту
//    /// </summary>
//    /// <returns> тру если пусто</returns>
//    bool isEmpty() const {
//        return minHeap.isEmpty();
//    }
//};
//
//


//template<typename T>
//void testMinHeap() {
//    MinHeap<int> heap;
//
//    // Проверка извлечения минимального элемента из пустой кучи
//    assert(heap.isEmpty() == true);
//
//    // Проверка пика минимального элемента из пустой кучи
//    assert(heap.isEmpty() == true);
//
//    heap.insert(5);
//    heap.insert(3);
//    heap.insert(8);
//    heap.insert(1);
//    heap.insert(2);
//
//    // Проверка, что минимальный элемент вернулся корректно
//    assert(heap.peek() == 1);
//
//    // Извлечение минимального элемента и проверка кучи
//    assert(heap.extractMin() == 1);
//    assert(heap.peek() == 2);
//
//    assert(heap.extractMin() == 2);
//    assert(heap.peek() == 3);
//
//    // Извлечем оставшиеся элементы
//    assert(heap.extractMin() == 3);
//    assert(heap.extractMin() == 5);
//    assert(heap.extractMin() == 8);
//    assert(heap.isEmpty() == true);
//
//
//    // Проверка извлечения и получения пика из пустой кучи после извлечения всех элементов
//    try {
//        heap.peek();
//        assert(false); // если не выбросило исключение, тест провален
//    }
//    catch (const runtime_error& e) {
//        // Ожидаем исключение при попытке получить минимальный элемент из пустой кучи
//    }
//
//    try {
//        heap.extractMin();
//        assert(false); // если не выбросило исключение, тест провален
//    }
//    catch (const runtime_error& e) {
//        // Ожидаем исключение при попытке извлечь элемент из пустой кучи
//    }
//
//}
//
//
//template<typename T>
//void testHeapifyMethods() {
//    MinHeap<int> heap;
//
//    heap.insert(8);
//    heap.insert(5);
//    heap.insert(3);
//    heap.insert(1);
//    heap.insert(2);
//
//    vector<int> expectedHeap = { 1, 2, 3, 8, 5 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // Извлекаем минимум (1)
//    heap.extractMin();
//    expectedHeap = { 2, 3, 5, 8 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // Вставим новый элемент (0)
//    heap.insert(0);
//    expectedHeap = { 0, 2, 3, 8, 5 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // Извлекаем минимум (0)
//    heap.extractMin();
//    expectedHeap = { 2, 3, 5, 8 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // Проверка на извлечение всех элементов
//    heap.extractMin(); // 2
//    heap.extractMin(); // 3
//    heap.extractMin(); // 5
//    heap.extractMin(); // 8
//
//    // Теперь кучи должна быть пустой
//    assert(heap.isEmpty() == true);
//
//    // Проверка пика минимального элемента из пустой кучи
//    try {
//        heap.peek();
//        assert(false); // Тест должен завалиться, если исключение не выброшено
//    }
//    catch (const std::runtime_error& e) {
//        // Ожидаем исключение при попытке получить минимальный элемент из пустой кучи
//    }
//
//    // Проверка извлечения минимального элемента из пустой кучи
//    try {
//        heap.extractMin();
//        assert(false); // Тест должен завалиться, если исключение не выброшено
//    }
//    catch (const std::runtime_error& e) {
//        // Ожидаем исключение при попытке извлечь элемент из пустой кучи
//    }
//}
//
//}
//
//
//
//
//
//
//
//
//
//
//template<typename T>
//void heapsortT() {
//
//    //  пустой массив
//    vector<int> emptyarray = {};
//    assert(heapsort(emptyarray) == vector<int>{});
//
//    // массив с одним элементом
//    vector<int> singleelementarray = { 5 };
//    assert(heapsort(singleelementarray) == vector<int>{5});
//
//    // массив уже отсортирован
//    vector<int> sortedarray = { 1, 2, 3, 4, 5 };
//    assert(heapsort(sortedarray) == vector<int>{1, 2, 3, 4, 5});
//
//    // массив отсортирован в обратном порядке
//    vector<int> reversesortedarray = { 5, 4, 3, 2, 1 };
//    assert(heapsort(reversesortedarray) == vector<int>{1, 2, 3, 4, 5});
//
//    // массив с дублирующимися значениями
//    vector<int> arraywithduplicates = { 3, 1, 2, 1, 3 };
//    assert(heapsort(arraywithduplicates) == vector<int>{1, 1, 2, 3, 3});
//
//    // смешанные элементы
//    vector<int> mixedarray = { 9, -1, 3, 2, 0 };
//    assert(heapsort(mixedarray) == vector<int>{-1, 0, 2, 3, 9});
//}
////
////void testpriory() {
////    priorityqueue<int> pq;
////
////    assert(pq.isempty() == true);
////
////    pq.push(10);
////    pq.push(5);
////    pq.push(15);
////    pq.push(2);
////
////    // проверка верхнего элемента
////    assert(pq.top() == 2); // минимальный элемент должен быть 2
////    assert(pq.isempty() == false); // очередь не должна быть пуста
////
////    assert(pq.pop() == 2);
////    assert(pq.top() == 5);
////
////    assert(pq.pop() == 5);
////    assert(pq.pop() == 10);
////    assert(pq.pop() == 15);
////    assert(pq.isempty() == true);
////
////}


template<typename T>
void testMinHeapIterator() {
    MinHeap<int> minHeap;

// Проверка итератора на пустой куче
assert(minHeap.begin() == minHeap.end()); // Итератор должен быть равен итератору end

// Вставка элементов в кучу
minHeap.insert(5);
minHeap.insert(3);
minHeap.insert(8);
minHeap.insert(1);
minHeap.insert(2);

// Проверка итератора на заполненной куче
vector<int> expectedValues = { 1, 2, 3, 5, 8 };
size_t index = 0;
for (auto it = minHeap.begin(); it != minHeap.end(); ++it) {
    assert(*it == expectedValues[index]); // Проверка соответствия значений
    index++;
}
assert(index == expectedValues.size()); // Убедимся, что все элементы были проверены

// Проверка извлечения минимального элемента и повторная проверка итератора

assert(minHeap.extractMin() == 1); // Извлекаем 1
assert(minHeap.peek() == 2); // Теперь минимальный элемент 2 должен быть на вершине

index = 0;
for (auto it = minHeap.begin(); it != minHeap.end(); ++it) {
    assert(*it == expectedValues[index + 1]); // Извлеченный 1 исключаем
    index++;
}
assert(index == expectedValues.size() - 1); // Убедимся, что все элементы были проверены

// Извлечение всех элементов и проверка на пустую кучу
assert(minHeap.extractMin() == 2);
assert(minHeap.extractMin() == 3);
assert(minHeap.extractMin() == 5);
assert(minHeap.extractMin() == 8);

// Проверка на пустую кучу после извлечения
assert(minHeap.isEmpty() == true);

// Проверка итератора на пустой куче снова
assert(minHeap.begin() == minHeap.end()); // Итератор должен быть равен итератору end

try {
    minHeap.peek(); // Должен выбросить исключение
    assert(false); // Если исключения нет, тест должен провалиться
}
catch (const std::runtime_error&) {
    // Ожидаем исключение
}

try {
    minHeap.extractMin(); // Должен выбросить исключение
    assert(false);
}
catch (const std::runtime_error&) {
}
}
