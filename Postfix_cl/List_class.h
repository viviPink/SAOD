
#include <iostream>
#include <cassert>
//#include "TestProject.h"
//��������� ���� ���-22
using namespace std;

#pragma once
// ����� ���� ������
template <class T>
class Node {
public:
    T data;                // �������� ����
    Node<T>* prev;         // ��������� �� ���������� ����
    Node<T>* next;          // ��������� �� ��������� ����


    // ����������� ���� � ����������
    Node(T value) : data(value), prev(nullptr), next(nullptr) {}

    // ����������� ���� �� ���������
    Node() : data(T()), prev(nullptr), next(nullptr) {}

    // ���������� ����
    ~Node() {
        if ( prev != nullptr )
        {
            prev = nullptr;  // �������� ��������� �� ���������� ����
            next = nullptr;  // �������� ��������� �� ��������� ����
        }
    }
};

// ����� ����������� ������
template <class T>
class DoublyLinkedList {
private:
    Node<T>* head;  //��������� �� ������ ������
    Node<T>* tail;  //��������� �� ����� ������
    size_t size;    // ����������, ������� ������ ������ ������

public:
    // ����������� ����������� ������ �� ���������
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // ���������� ����������� ������
    ~DoublyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;  // ����������� ������ ��� ������� ����
        }
        head = nullptr;  // �������� ��������� �� ������
        tail = nullptr;  // �������� ��������� �� �����
    }

    //��������� ������ ������ O(1)
    size_t getSize() const{
        return size;
    }

    // ����� ������� �������� � ������ (������ � ��������)
    // ������ �(1)
    // ����� �(1) �� ������ ���������� 
    // �������� O(n)
    void insert(size_t index, T value) {
        // ��������� ������������ �������
        if (index < 0 || index > size) {
            cout << "Index out " << endl;
            return;
        }

        Node<T>* newNode = new Node<T>(value);  // ������� ����� ���� � ���������� ���������

        if (index == 0) {
            // ������� � ������ ������
            if (head == nullptr) {
                head = newNode;  // ���� ������ ������, ����� ���� ���������� ��� �������, ��� � �������
                tail = newNode;
            }
            else {
                newNode->next = head;  // ������������� ����� ������ ���� � ������� �������
                head->prev = newNode;  // ��������� ��������� ����������� ���� ��� ������� ������
                head = newNode;  // ����� ���� ���������� �������
            }
        }
        else if (index == size) {
            // ������� � ����� ������
            if (tail == nullptr) {
                head = newNode;  // ���� ������ ������, ����� ���� ����������  ������� � �������
                tail = newNode;
            }
            else {
                newNode->prev = tail;  // ������������� ����� ������ ���� � ������� �������
                tail->next = newNode;  // ��������� ��������� ���������� ���� ��� �������� ������
                tail = newNode;  // ����� ���� ���������� �������
            }
        }
        else {
            // ������� � �������� ������
            Node<T>* current = head;
            // ������� ���� ����� �������� �������
            for (size_t i = 0; i < index - 1; i++) {
                current = current->next;
            }
            // ��������� ����� ���� � ������ � ����� ������
            newNode->next = current->next;
            if (current->next != nullptr) {
                current->next->prev = newNode;
            }
            current->next = newNode;
            newNode->prev = current;
        }
        size++;  // ����������� ������ ������
    }

    // ����� �������� �������� �� ������ (���������� ������ index)
    // ������ �(1)
    // ����� �(1) �� ������ ���������� 
    // �������� O(n)
    void remove(size_t index) {
        // ��������� ������������ �������
        if (index < 0 || index >= size) {
            std::cout << "Index out " << std::endl;
            return;
        }

        // �������� ������� ��������
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
        // �������� ���������� ��������
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
        // �������� �������� �� �������
        else {
            Node<T>* current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
        size--;  // ��������� ������ ������
    }





    //����� ���� ������� (element) � ������� � ���������� ��� ������. ���� ������� �� ������, ���������� -1
      //�� ����� 
    long long Search(T element) {

        return findElement(Node, size-1, element);
    }
   

    //���������� ���� ������� ����� �������� ���������
    //��������� �(n)
    void concatenate(DoublyLinkedList& list) {
        // ���������, ���� ������ ������, ������� �� �������� ��������, ����� nullptr
        if (list.head == nullptr) {
            // ���� ��� ���, �� ������ ������������ �� �������
            return;
        }

        // ���������, ���� ������ �������� ������ ����� nullptr
        if (head == nullptr) {
            // ���� ��� ���, ����������� ������ � ����� �������� ������ �������� �� ������ list
            head = list.head;
            tail = list.tail;
        }
        else {
            // ���� ������� ������ �� ������, ��������� �������� �� ������ list � ����� �������� ������
            tail->next = list.head;
            list.head->prev = tail;
            tail = list.tail;
        }

        // ����������� ������ �������� ������ �� ������ ������ list
        size += list.size;

        // �������� ��������� � ������ ������ list
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
    }

    //�������� ������� � ��������� ������
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

    // ����� ������ ������ �� �����
    //  O(n)
    void printList() {
        Node<T>* current = head;  // ��������� �� ������� ������� ������
        while (current != nullptr) {
            cout << current->data << " ";  // ������� �������� �������� ����
            current = current->next;  // ��������� � ���������� ����
        }
        cout << endl;
    }

    // ����� ��������� �������� ���� �� �������
    // ������ O(1)
    // ����� O(1)
    // �������� O(n)
    T get(size_t index) {
        //assert(index >= 0  index < size);  // �������� ������������ �������
        Node<T>* current = head;
        // ������� ���� � ��������� ��������
        for (size_t i = 0; i < index; i++) {
            current = current->next;

        }
        return current->data;  // ���������� �������� ����
    }
    // ����� ������� ������
    void clearList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;  // ����������� ������ ��� ������� ����
        }
        head = nullptr;  // �������� ��������� �� ������
        tail = nullptr;  // �������� ��������� �� �����
        size = 0;  // ���������� ������ ������
    }

void assertInsert() {
    DoublyLinkedList<int> list;
    // ������� � ������ ������
    list.insert(0, 10);

    assert(list.size == 1);

    // ������� � ����� ������
    list.insert(size, 20);
    assert(list.size == 2);

    //  ������� � �������� ������
    list.insert(1, 15);
    assert(list.size == 3);


    //������� 
    //����������
    //�����
}

};
