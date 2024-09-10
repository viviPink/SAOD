#pragma once
//��������� ���� ���-22
#include <iostream>

using namespace std;
//��������� ����� ��� ���� ������
template<typename T>
class TreeNode {
public:
    //������, ������� �������� � ����
    T data;
    //��������� �� ����� ����
    TreeNode<T>* left;
    //��������� �� ������ ����
    TreeNode<T>* right;

    //����������� �� ���������
    TreeNode() : data(T()), left(nullptr), right(nullptr) {}

    //������������ � ����������� (����������� �� ����� � ������ ����)
    TreeNode(const T& data, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr) : data(data), left(l), right(r) {}
};

template<typename T>
//��������� ����� ������  

///�������� ������ ������ ��������������������
class BinaryTree {
public:
    //������ ������
    TreeNode<T>* root;

    //����������� ������ ��� ����������
    BinaryTree() : root(nullptr) {}

    //���������� ������
    ~BinaryTree() {
        deleteTree(root);
    }

    //������� ������� ����� � ������
    //data- ������ ��� �������
    void insert(const T& data) {

        //������������ ��������� ������ ��� ������ ���� 
        TreeNode<T>* newNode = new TreeNode<T>(data);
        //��������� �������� �� ������ null
        if (!root) {
            // ���� �� �� ����� ���� ��� ������
            root = newNode;
            return;
        }
        //��������� ��������� current, ������� ���������� ��������� �� ������ ������
        TreeNode<T>* current = root;

        //���������� ����������� ����, � ������� ���������� ����� ����������� ����� ��� ������� ������ ����
        while (true) {
            //������������ �������� data ������ ���� � ��������� �������� ���� current->data
            //���� data ������, �� �����������, ���� �� ����� ������� � �������� ����
            //���� ����, �� current ������������ �����
            //���� ���, �� ����� ���� newNode ����������� ����� �������� �������� ����, � ������� insert �����������
            //���� data ������ ��� �����, �� �����������, ���� �� ������ ������� � �������� ����
            //���� ����, �� current ������������ ������
            //���� ���, �� ����� ���� newNode ����������� ������ �������� �������� ����, � ������� insert �����������
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
    //�������� ������ ���-�� ������� �� ��� �������� ����� lrn
   //node - ����
    void deleteTree(TreeNode<T>* node) {
        //��������� ����� ���� �� ��� ������
        if (node != nullptr) {
            //������� ����� ����
            deleteTree(node->left);
            //������� ������ ����
            deleteTree(node->right);
            //������� ��� ����
            delete node;
        }
    }

    //����� ������ �� �����
    //node-������ ������
    void printTree(TreeNode<T>* node, int level = 0) {
        // ���������, �������� �� ������� ���� null
        if (node != nullptr) {
            // ���������� �������� ������� ��� ������� ���������
            printTree(node->right, level + 1);
            // ������� ������ � ����������� �� �������� ������
            for (int i = 0; i < level; i++) {
                cout << "   ";
            }
            // ������� �������� �������� ����
            cout << node->data << endl;
            // ���������� �������� ������� ��� ������ ���������
            printTree(node->left, level + 1);
        }
    }

    //��������� ������ ����  ==== ������
    const T& getNodeData(TreeNode<T>* node) {
        return node->data;
    }

};
    


//����������� ������� ������ � ������ ������ NLR
     template<typename T>
    void NLR(TreeNode<T>* node) {
        if(node) {
            //to do ��������� ������� 
            cout << node->data;
            NLR(node->left);
            NLR(node->right);
        }
    }

    //����������� ������� ������ � ������ ������ LNR
    template<typename T>
    void LNR(TreeNode<T>* node) {
        if (node) {
            LNR(node->left);
            //to do ��������� ������� 
            cout << node->data;
            LNR(node->right);
        }
    }

    //����������� ������� ������ � ������ ������ LRN
    template<typename T>
    void LRN(TreeNode<T>* node) {
        if (node) {
            LRN(node->left);
            LRN(node->right);

            //to do ��������� ������� 
            cout << node->data;
           
        }
    }

