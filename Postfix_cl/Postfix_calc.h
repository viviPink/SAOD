#pragma once


#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cassert>
#include "Stack_class.h"
using namespace std;


// Класс постфиксного калькулятора на основе стека 
class StackCalculator : public Stack<double> {

public:
    // Функция для выполнения операции над двумя числами O(1)
    //берет из стека 2 последних числа и выполняется оператор->затем ответ записывается в стек
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
                throw invalid_argument("Неверная операция");
            }
            return a / b;
        default:
            throw invalid_argument("Неверная операция");
        }
    }

    // Функция для вычисления выражения -> заноситт в стек результат O(1)
    double Solution(const string& expression) {
        stringstream ss(expression);
        string token;
        while (ss >> token) {
            if (isdigit(token[0])) {
                // Если число, поместить его в стек
                push(stod(token));
            }
            else {
                // Если оператор, выполнить операцию над двумя верхними элементами стека
                double b = pop();
                double a = pop();
                double result = Operations(a, b, token[0]);
                push(result);
            }
        }

        // Оставшийся элемент в стеке - результат вычисления
        return peek();
    }




    // Функция для преобразования инфиксного выражения в постфиксную запись
    string infix_postfix(const string& expression) {
        string postfix;
        stack<char> operators;
        //разбиваем выражение на токены и ищем если цифра то добавляем в троку 
        //Если закрывающая скобка, мы извлекаем операторы из стека и добавляем их в выходную строку до тех пор, пока не встретим открывающую скобку
         //Если символ - оператор, мы сравниваем его приоритет с операторами в стеке
        //.Если приоритет текущего оператора меньше или равен приоритету верхнего оператора в стеке, мы извлекаем операторы 
        //из стека и добавляем их в выходную строку до тех пор, пока это условие выполняется
        //Затем добавляем текущий оператор в стек
        for (char token : expression) {
            if (isdigit(token)) {
                // Если токен - число, добавляем его в выходную строку
                postfix += token;
                postfix += ' '; // Разделитель между числами
            }
            else if (token == '(') {
                // Открывающая скобка, добавляем ее в стек операторов
                operators.push(token);
            }
            else if (token == ')') {
                // Закрывающая скобка, извлекаем операторы из стека до открывающей скобки
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    postfix += ' '; 
                    operators.pop();
                }
                operators.pop(); // Удаляем открывающую скобку из стека
            }
            else {
                // Оператор
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    postfix += operators.top();
                    postfix += ' '; 
                    operators.pop();
                }
                operators.push(token); // Добавляем текущий оператор в стек
            }
        }
        // Извлекаем оставшиеся операторы из стека
        while (!operators.empty()) {
            postfix += operators.top();
            postfix += ' '; // Разделитель между операторами
            operators.pop();
        }
        // Удаляем последний лишний пробел
        postfix.pop_back();

        return postfix;
    }

    // Функция для определения приоритета оператора выводит -1 в случае если оператор неверный
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


