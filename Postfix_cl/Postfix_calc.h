#pragma once


#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cassert>
#include "Stack_class.h"
using namespace std;


// ����� ������������ ������������ �� ������ ����� 
class StackCalculator : public Stack<double> {

public:
    // ������� ��� ���������� �������� ��� ����� ������� O(1)
    //����� �� ����� 2 ��������� ����� � ����������� ��������->����� ����� ������������ � ����
    double Operations(double a, double b, char operators) {
        switch (operators) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b==0){
                throw invalid_argument("�������� ��������");
            }
            return a / b;
        default:
            throw invalid_argument("�������� ��������");
        }
    }

    // ������� ��� ���������� ��������� -> �������� � ���� ��������� O(1)
    double Solution(const string& expression) {
        stringstream ss(expression);
        string token;
        while (ss >> token) {
            if (isdigit(token[0])) {
                // ���� �����, ��������� ��� � ����
                push(stod(token));
            }
            else {
                // ���� ��������, ��������� �������� ��� ����� �������� ���������� �����
                double b = pop();
                double a = pop();
                double result = Operations(a, b, token[0]);
                push(result);
            }
        }

        // ���������� ������� � ����� - ��������� ����������
        return peek();
    }




    // ������� ��� �������������� ���������� ��������� � ����������� ������
    string infix_postfix(const string& expression) {
        string postfix;
        stack<char> operators;
        //��������� ��������� �� ������ � ���� ���� ����� �� ��������� � ����� 
        //���� ����������� ������, �� ��������� ��������� �� ����� � ��������� �� � �������� ������ �� ��� ���, ���� �� �������� ����������� ������
         //���� ������ - ��������, �� ���������� ��� ��������� � ����������� � �����
        //.���� ��������� �������� ��������� ������ ��� ����� ���������� �������� ��������� � �����, �� ��������� ��������� 
        //�� ����� � ��������� �� � �������� ������ �� ��� ���, ���� ��� ������� �����������
        //����� ��������� ������� �������� � ����
        for (char token : expression) {
            if (isdigit(token)) {
                // ���� ����� - �����, ��������� ��� � �������� ������
                postfix += token;
                postfix += ' '; // ����������� ����� �������
            }
            else if (token == '(') {
                // ����������� ������, ��������� �� � ���� ����������
                operators.push(token);
            }
            else if (token == ')') {
                // ����������� ������, ��������� ��������� �� ����� �� ����������� ������
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    postfix += ' '; 
                    operators.pop();
                }
                operators.pop(); // ������� ����������� ������ �� �����
            }
            else {
                // ��������
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    postfix += operators.top();
                    postfix += ' '; 
                    operators.pop();
                }
                operators.push(token); // ��������� ������� �������� � ����
            }
        }
        // ��������� ���������� ��������� �� �����
        while (!operators.empty()) {
            postfix += operators.top();
            postfix += ' '; // ����������� ����� �����������
            operators.pop();
        }
        // ������� ��������� ������ ������
        postfix.pop_back();

        return postfix;
    }

    // ������� ��� ����������� ���������� ��������� ������� -1 � ������ ���� �������� ��������
    int precedence(char op) {
        if (op == '(' || op == ')') return 0;
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return -1; 
    }
};


void assert_worst_case() {
    StackCalculator calculator;
    string expression = "3 + 4 * 2 / ( 1 - 5 )";
    string postfix = calculator.infix_postfix(expression);
    assert(postfix == "3 4 2 * 1 5 - 2 / +");
    cout << calculator.Solution(postfix);
    assert(calculator.Solution(postfix)==1);
}

void assert_best_case() {
    StackCalculator calculator;
    string expression = "2 + 3 * 4";
    string postfix = calculator.infix_postfix(expression);
    assert(postfix == "2 3 4 * +");
    assert(calculator.Solution(postfix) == 14);
}

void assert_average_case() {
    StackCalculator calculator;
    string expression = "5 * ( 6 + 2 ) - 12 / 4";
    string postfix = calculator.infix_postfix(expression);
    assert(postfix == "5 6 2 + * 12 4 / -");
}


