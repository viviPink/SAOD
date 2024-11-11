#pragma once
#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

/// <summary>
/// Шаблонный класс для узла дерева
///     18
///   /   \ 
///  5     20
/// / \   /  \
///4   7  21  22
/// </summary>
template<typename T>
class TreeNode {
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode() : data(T()), left(nullptr), right(nullptr) {}

    TreeNode(const T& data, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr)
        : data(data), left(l), right(r) {}
};

/// <summary>
/// Шаблонный класс бинарного дерева поиска
/// </summary>
template<typename T>
class BinaryTree {
public:
    TreeNode<T>* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        deleteTree(root);
    }

    // Вставка узла в дерево
    void insert(const T& data) {
        root = insertNode(root, data);
    }

    // Удаление узла из дерева
    void remove(const T& data) {
        root = removeNode(root, data);
    }

    // Обход in-order
    void inOrderTraversal() {
        inOrderTraversal(root);
    }

private:
    // Вспомогательный метод для вставки узла
    TreeNode<T>* insertNode(TreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return new TreeNode<T>(data);
        }
        if (data < node->data) {
            node->left = insertNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertNode(node->right, data);
        } // Дубликаты не допускаются
        return node;
    }

    // Вспомогательный метод для удаления узла
    TreeNode<T>* removeNode(TreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr; // Дерево пустое
        }

        if (data < node->data) {
            node->left = removeNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = removeNode(node->right, data);
        }
        else {
            // Узел найден, теперь мы можем удалить его
            if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Узел с двумя дочерними, найдем минимальное значение в правом поддереве
            TreeNode<T>* minNode = findMin(node->right);
            node->data = minNode->data; // Копируем данные
            node->right = removeNode(node->right, minNode->data); // Удаляем минимальный узел
        }
        return node;
    }

    // Вспомогательный метод для нахождения минимального узла
    TreeNode<T>* findMin(TreeNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Удаление дерева
    void deleteTree(TreeNode<T>* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    // Обход in-order
    void inOrderTraversal(TreeNode<T>* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
};
