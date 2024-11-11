#pragma once
#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

/// <summary>
/// ��������� ����� ��� ���� ������
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
/// ��������� ����� ��������� ������ ������
/// </summary>
template<typename T>
class BinaryTree {
public:
    TreeNode<T>* root;

    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        deleteTree(root);
    }

    // ������� ���� � ������
    void insert(const T& data) {
        root = insertNode(root, data);
    }

    // �������� ���� �� ������
    void remove(const T& data) {
        root = removeNode(root, data);
    }

    // ����� in-order
    void inOrderTraversal() {
        inOrderTraversal(root);
    }

private:
    // ��������������� ����� ��� ������� ����
    TreeNode<T>* insertNode(TreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return new TreeNode<T>(data);
        }
        if (data < node->data) {
            node->left = insertNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertNode(node->right, data);
        } // ��������� �� �����������
        return node;
    }

    // ��������������� ����� ��� �������� ����
    TreeNode<T>* removeNode(TreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr; // ������ ������
        }

        if (data < node->data) {
            node->left = removeNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = removeNode(node->right, data);
        }
        else {
            // ���� ������, ������ �� ����� ������� ���
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

            // ���� � ����� ���������, ������ ����������� �������� � ������ ���������
            TreeNode<T>* minNode = findMin(node->right);
            node->data = minNode->data; // �������� ������
            node->right = removeNode(node->right, minNode->data); // ������� ����������� ����
        }
        return node;
    }

    // ��������������� ����� ��� ���������� ������������ ����
    TreeNode<T>* findMin(TreeNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // �������� ������
    void deleteTree(TreeNode<T>* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    // ����� in-order
    void inOrderTraversal(TreeNode<T>* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
};
