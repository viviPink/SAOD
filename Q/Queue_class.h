#include <iostream>
#include <cassert>
#include "List_class.h"

using namespace std;

#pragma once
template <class T>
class Queue : private DoublyLinkedList<T> {
public:
    // ƒобавление элемента в конец очереди (value значение)
    //ќ(1)
    void enqueue(T value) {
        this->insert(this->getSize(), value); // ¬ызываем метод вставки из базового класса
    }

    // вз€тие элемента из начала очереди (если очередь пуста возращаетс€ €значение по умолчанию )
    //ќ(1)
    T denqueue() {
        if (!this->isEmpty()) {
            T s = this->get(0);
            this->remove(0); // ”дал€ем элемент с индексом 0 (начало очереди) из базового класса
            return s;
        }
        else {
            return T();
        }
    }

    // ѕолучение элемента в начале очереди (если очередь пуста возращаетс€ €значение по умолчанию )
    //ќ(1)
    T front() const {
        if (!this->isEmpty()) {
            return this->get(0); // ¬озвращаем элемент с индексом 0 (начало очереди) из базового класса
        }
        else {
            return T();
        }
    }

    // ѕроверка на пустоту очереди(если очередь пуста возращаетс€ 0 )
    //ќ(1)
    bool isEmpty() const {
        return this->getSize() == 0; 
    }

    // ѕолучение размера очереди
    //O(1)
    size_t size() const {
        return this->getSize(); // ¬озвращаем размер очереди, вызыва€ метод getSize из базового класса
    }
};





// ‘ункци€ assert дл€ порверки работы класса Queue
void assert_average_case() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(q.front() == 1);
    q.denqueue();
    //теперь нова€ верниша тк элемент удален
    assert(q.front() == 2);
    assert(q.size() == 2);

    q.denqueue();
    q.denqueue();

    //проверка просмотра вершины из пустой очереди (выводитс€ значение по умолчанию)
    assert(q.front() == 0);
    //проверка просмотра вершины из пустой очереди (выводитс€ значение по умолчанию)
    assert(q.denqueue() == 0);
   

}

