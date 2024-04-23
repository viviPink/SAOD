#include <iostream>
#include <cassert>
#include "List_class.h"

using namespace std;

#pragma once
template <class T>
class Queue : private DoublyLinkedList<T> {
public:
    // ���������� �������� � ����� ������� (value ��������)
    //�(1)
    void enqueue(T value) {
        this->insert(this->getSize(), value); // �������� ����� ������� �� �������� ������
    }

    // ������ �������� �� ������ ������� (���� ������� ����� ����������� ��������� �� ��������� )
    //�(1)
    T denqueue() {
        if (!this->isEmpty()) {
            T s = this->get(0);
            this->remove(0); // ������� ������� � �������� 0 (������ �������) �� �������� ������
            return s;
        }
        else {
            return T();
        }
    }

    // ��������� �������� � ������ ������� (���� ������� ����� ����������� ��������� �� ��������� )
    //�(1)
    T front() const {
        if (!this->isEmpty()) {
            return this->get(0); // ���������� ������� � �������� 0 (������ �������) �� �������� ������
        }
        else {
            return T();
        }
    }

    // �������� �� ������� �������(���� ������� ����� ����������� 0 )
    //�(1)
    bool isEmpty() const {
        return this->getSize() == 0; 
    }

    // ��������� ������� �������
    //O(1)
    size_t size() const {
        return this->getSize(); // ���������� ������ �������, ������� ����� getSize �� �������� ������
    }
};





// ������� assert ��� �������� ������ ������ Queue
void assert_average_case() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(q.front() == 1);
    q.denqueue();
    //������ ����� ������� �� ������� ������
    assert(q.front() == 2);
    assert(q.size() == 2);

    q.denqueue();
    q.denqueue();

    //�������� ��������� ������� �� ������ ������� (��������� �������� �� ���������)
    assert(q.front() == 0);
    //�������� ��������� ������� �� ������ ������� (��������� �������� �� ���������)
    assert(q.denqueue() == 0);
   

}

