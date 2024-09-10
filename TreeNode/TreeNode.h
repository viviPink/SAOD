#pragma once
//Пинчукова Гера ИВТ-22
#include <iostream>

using namespace std;
//Шаблонный класс для узла дерева
template<typename T>
class TreeNode {
public:
    //данные, которые хранятся в узле
    T data;
    //указатель на левый узел
    TreeNode<T>* left;
    //указатель на правый узел
    TreeNode<T>* right;

    //конструктор по умолчанию
    TreeNode() : data(T()), left(nullptr), right(nullptr) {}

    //констртуктор с параметрами (указателями на левый и правый узлы)
    TreeNode(const T& data, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr) : data(data), left(l), right(r) {}
};

template<typename T>
//Шаблонный класс дерева  

///бинарное дерево поиска аааааааааааааааааааа
class BinaryTree {
public:
    //корень дерева
    TreeNode<T>* root;

    //конструктор дерева без параметров
    BinaryTree() : root(nullptr) {}

    //деструктор дерева
    ~BinaryTree() {
        deleteTree(root);
    }

    //функция вставки числа в дерево
    //data- данные для вставки
    void insert(const T& data) {

        //динамическое выделение памяти для нового узла 
        TreeNode<T>* newNode = new TreeNode<T>(data);
        //проверяем является ли корень null
        if (!root) {
            // если да то новый узел это корень
            root = newNode;
            return;
        }
        //Создается указатель current, который изначально ссылается на корень дерева
        TreeNode<T>* current = root;

        //Начинается бесконечный цикл, в котором происходит поиск правильного места для вставки нового узла
        while (true) {
            //Сравнивается значение data нового узла с значением текущего узла current->data
            //Если data меньше, то проверяется, есть ли левый потомок у текущего узла
            //Если есть, то current перемещается влево
            //Если нет, то новый узел newNode назначается левым потомком текущего узла, и функция insert завершается
            //Если data больше или равно, то проверяется, есть ли правый потомок у текущего узла
            //Если есть, то current перемещается вправо
            //Если нет, то новый узел newNode назначается правым потомком текущего узла, и функция insert завершается
            if (data < current->data) {
                if (current->left) {
                    current = current->left;
                }
                else {
                    current->left = newNode;
                    return;
                }
            }
            else {
                if (current->right) {
                    current = current->right;
                }
                else {
                    current->right = newNode;
                    return;
                }
            }
        }
    }


    //
    //удаление дерева что-то похожее на лнр обратный обход lrn
   //node - узел
    void deleteTree(TreeNode<T>* node) {
        //проверяем чтобы узел не был пустым
        if (node != nullptr) {
            //удаляем левый узел
            deleteTree(node->left);
            //удаляем правый узел
            deleteTree(node->right);
            //удаляем сам узел
            delete node;
        }
    }

    //вывод дерева на экран
    //node-данные дерева
    void printTree(TreeNode<T>* node, int level = 0) {
        // Проверяем, является ли текущий узел null
        if (node != nullptr) {
            // Рекурсивно вызываем функцию для правого поддерева
            printTree(node->right, level + 1);
            // Выводим отступ в зависимости от текущего уровня
            for (int i = 0; i < level; i++) {
                cout << "   ";
            }
            // Выводим значение текущего узла
            cout << node->data << endl;
            // Рекурсивно вызываем функцию для левого поддерева
            printTree(node->left, level + 1);
        }
    }

    //получение данных узла  ==== корень
    const T& getNodeData(TreeNode<T>* node) {
        return node->data;
    }

};
    


//рекурсивная функция обхода и печати дерева NLR
     template<typename T>
    void NLR(TreeNode<T>* node) {
        if(node) {
            //to do массивчик сделать 
            cout << node->data;
            NLR(node->left);
            NLR(node->right);
        }
    }

    //рекурсивная функция обхода и печати дерева LNR
    template<typename T>
    void LNR(TreeNode<T>* node) {
        if (node) {
            LNR(node->left);
            //to do массивчик сделать 
            cout << node->data;
            LNR(node->right);
        }
    }

    //рекурсивная функция обхода и печати дерева LRN
    template<typename T>
    void LRN(TreeNode<T>* node) {
        if (node) {
            LRN(node->left);
            LRN(node->right);

            //to do массивчик сделать 
            cout << node->data;
           
        }
    }

