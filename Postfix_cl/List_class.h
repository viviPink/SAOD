
#include <iostream>
#include <cassert>
//#include "TestProject.h"
//Пинчукова Гера ивт-22
using namespace std;

#pragma once
// Класс узла списка
template <class T>
class Node {
public:
    T data;                // Значение узла
    Node<T>* prev;         // Указатель на предыдущий узел
    Node<T>* next;          // Указатель на следующий узел


    // Конструктор узла с парамерами
    Node(T value) : data(value), prev(nullptr), next(nullptr) {}

    // Конструктор узла по умолчанию
    Node() : data(T()), prev(nullptr), next(nullptr) {}

    // Деструктор узла
    ~Node() {
        if ( prev != nullptr )
        {
            prev = nullptr;  // Обнуляем указатель на предыдущий узел
            next = nullptr;  // Обнуляем указатель на следующий узел
        }
    }
};

// Класс двусвязного списка
template <class T>
class DoublyLinkedList {
private:
    Node<T>* head;  //указатель на голову списка
    Node<T>* tail;  //указатель на хвост списка
    size_t size;    // переменная, которая хранит размер списка

public:
    // Конструктор двусвязного списка по умолчанию
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор двусвязного списка
    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;  // Освобождаем память для каждого узла
        }
        head = nullptr;  // Обнуляем указатель на голову
        tail = nullptr;  // Обнуляем указатель на хвост
    }

    //получение размер списка O(1)
    size_t getSize() const{
        return size;
    }

    // Метод вставки элемента в список (индекс и значение)
    // начало О(1)
    // конец О(1) тк только обновление 
    // середина O(n)
    void insert(size_t index, T value) {
        // Проверяем корректность индекса
        if (index < 0 || index > size) {
            cout << "Index out " << endl;
            return;
        }

        Node<T>* newNode = new Node<T>(value);  // Создаем новый узел с переданным значением

        if (index == 0) {
            // Вставка в начало списка
            if (head == nullptr) {
                head = newNode;  // Если список пустой, новый узел становится как головой, так и хвостом
                tail = newNode;
            }
            else {
                newNode->next = head;  // Устанавливаем связь нового узла с текущей головой
                head->prev = newNode;  // Обновляем указатель предыдущего узла для текущей головы
                head = newNode;  // Новый узел становится головой
            }
        }
        else if (index == size) {
            // Вставка в конец списка
            if (tail == nullptr) {
                head = newNode;  // Если список пустой, новый узел становится  головой и хвостом
                tail = newNode;
            }
            else {
                newNode->prev = tail;  // Устанавливаем связь нового узла с текущим хвостом
                tail->next = newNode;  // Обновляем указатель следующего узла для текущего хвоста
                tail = newNode;  // Новый узел становится хвостом
            }
        }
        else {
            // Вставка в середину списка
            Node<T>* current = head;
            // Находим узел перед позицией вставки
            for (size_t i = 0; i < index - 1; i++) {
                current = current->next;
            }
            // Связываем новый узел с узлами с обеих сторон
            newNode->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = newNode;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        size++;  // Увеличиваем размер списка
    }

    // Метод удаления элемента из списка (передается индекс index)
    // начало О(1)
    // конец О(1) тк только обновление 
    // середина O(n)
    void remove(size_t index) {
        // Проверяем корректность индекса
        if (index < 0 || index >= size) {
            std::cout << "Index out " << std::endl;
            return;
        }

        // Удаление первого элемента
        if (index == 0) {
            if (head == nullptr) {
                std::cout << "List is empty" << std::endl;
                return;
            }
            Node<T>* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            delete temp;
        }
        // Удаление последнего элемента
        else if (index == size - 1) {
            if (tail == nullptr) {
                std::cout << "List is empty" << std::endl;
                return;
            }
            Node<T>* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
        }
        // Удаление элемента по индексу
        else {
            Node<T>* current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;  // Уменьшаем размер списка
    }





    //Метод ищет элемент (element) в массиве и возвращает его индекс. Если элемент не найден, возвращает -1
      //не тоооо 
    long long Search(T element) {

        return findElement(Node, size-1, element);
    }
   

    //соеденение двух списков путем переноса указателя
    //сложность О(n)
    void concatenate(DoublyLinkedList& list) {
        // Проверяем, если голова списка, который мы пытаемся добавить, равна nullptr
        if (list.head == nullptr) {
            // Если это так, то просто возвращаемся из функции
            return;
        }

        // Проверяем, если голова текущего списка равна nullptr
        if (head == nullptr) {
            // Если это так, присваиваем голову и хвост текущего списка значения из списка list
            head = list.head;
            tail = list.tail;
        }
        else {
            // Если текущий список не пустой, добавляем элементы из списка list в конец текущего списка
            tail->next = list.head;
            list.head->prev = tail;
            tail = list.tail;
        }

        // Увеличиваем размер текущего списка на размер списка list
        size += list.size;

        // Обнуляем указатели и размер списка list
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
    }

    //оператор доступа к элементам списка
    T& operator[](size_t index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out");
        }

        Node<T>* current = head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    // Метод вывода списка на экран
    //  O(n)
    void printList() {
        Node<T>* current = head;  // Указатель на текущий элемент списка
        while (current != nullptr) {
            cout << current->data << " ";  // Выводим значение текущего узла
            current = current->next;  // Переходим к следующему узлу
        }
        cout << endl;
    }

    // Метод получения значения узла по индексу
    // начало O(1)
    // конец O(1)
    // середина O(n)
    T get(size_t index) {
        //assert(index >= 0  index < size);  // Проверка корректности индекса
        Node<T>* current = head;
        // Находим узел с требуемым индексом
        for (size_t i = 0; i < index; i++) {
            current = current->next;

        }
        return current->data;  // Возвращаем значение узла
    }
    // Метод очистки списка
    void clearList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;  // Освобождаем память для каждого узла
        }
        head = nullptr;  // Обнуляем указатель на голову
        tail = nullptr;  // Обнуляем указатель на хвост
        size = 0;  // Сбрасываем размер списка
    }

void assertInsert() {
    DoublyLinkedList<int> list;
    // вставка в начало списка
    list.insert(0, 10);

    assert(list.size == 1);

    // вставка в конец списка
    list.insert(size, 20);
    assert(list.size == 2);

    //  вставка в середину списка
    list.insert(1, 15);
    assert(list.size == 3);


    //очистка 
    //сортировка
    //поиск
}

};
