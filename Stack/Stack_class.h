#pragma once

#include <iostream>
#include <cassert>
#include "List_class.h"
// ����� ����� 
// ����� ���� ����������� �� ������ ����������� ������ DoublyLinkedList 
template <typename T>
class Stack : public DoublyLinkedList<T> {
public:
    // ����� ���������� �������� � ����
    void push(const T& element) {
        this->insert(this->getSize(), element);
    }

    // ����� �������� �������� �� �����
    void pop() {
        if (this->getSize() > 0) {
            this->remove(this->getSize() - 1);
        }
    }

   
    void assertStack() {
        Stack<int> stack;

        // ������ ������: ���� ������
        stack.push(10);
        assert(stack.getSize() == 1);
        assert(stack[0] == 10);

        stack.pop();
        assert(stack.getSize() == 0);

        // ������ ������: ���� ��������
        stack.push(20);
        stack.push(30);
        stack.push(40);
        stack.pop();
        assert(stack.getSize() == 2);
        assert(stack[0] == 20);
        assert(stack[1] == 30);

        // ������� ������: ���������� � �������� ���������� ���������
        stack.push(50);
        stack.pop();
        stack.push(60);
        stack.push(70);
        assert(stack.getSize() == 4);
        assert(stack[0] == 20);
        assert(stack[1] == 30);
        assert(stack[3] == 70);
    }


   
};
