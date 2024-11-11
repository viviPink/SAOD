#pragma once
#include "TreeNode.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// ����� AVLTreeNode ����������� �� TreeNode ��������� ������ ������
template<typename T>
class AVLTreeNode : public TreeNode<T> {
public:
    // ����������� ������� ����
    signed char balanceFactor;

    // ����������� �� ���������
    AVLTreeNode() : TreeNode<T>(), balanceFactor(0) {}

    // ����������� � �����������
    AVLTreeNode(const T& data) : TreeNode<T>(data), balanceFactor(0) {}

    // ����������� � ����������� 
    // (������ � ��������� �� ���������� � ��������� ����)
    AVLTreeNode(const T& data, TreeNode<T>* getLeft, TreeNode<T>* getRight)
        : TreeNode<T>(data, getLeft, getRight), balanceFactor(0) {}


    // ��������������� ��������� �� AVLTreeNode
    // ����������� ��������� �� ������ ������� ���� ������
    //static_cast �� ������������ ��� ���������� ��������� �� ������� ����� TreeNode<T> � ��������� �� ����������� ����� AVLTreeNode<T>
    AVLTreeNode<T>* getLeft() {
        return static_cast<AVLTreeNode<T>*>(this->left);
    }

    // ��������������� ��������� �� AVLTreeNode
    // ����������� ��������� �� ������� ������� ���� ������ �� ������� ����� TreeNode<T> � ��������� �� ����������� ����� AVLTreeNode<T>
    AVLTreeNode<T>* getRight() {
        return static_cast<AVLTreeNode<T>*>(this->right);
    }

    //// ��������������� ��������� �� (�� �����)
    // TreeNode � ��������� �� AVLTreeNode (const ������)
    //const AVLTreeNode<T>* getLeft() const {
    //    return static_cast<const AVLTreeNode<T>*>(this->left);
    //}

    //// ��������������� ��������� �� (�� ������) 
    // TreeNode � ��������� �� AVLTreeNode (const ������)
    //const AVLTreeNode<T>* getRight() const {
    //    return static_cast<const AVLTreeNode<T>*>(this->right);
    //}
};

// ����� AVLTree (���� ���������������� �������� ������ ������)
template<typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root; // ��������� �� ������ ������

    // ������� ��� ���������� ������������ ������� ����
    // O(log n/2) �
    // O(log n/2) c
    // O(log n/2) �
    void updateBalanceFactor(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());
        node->balanceFactor = leftHeight - rightHeight;
    }

    // ������� ��� ��������� ������ ����
    //(Best Case): O(1)
    //(Average Case): O(log n)
    //(Worst Case) : O(n)
    int getHeight(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight()));
    }

    // ������� ��� ������� ��������
    // ������ ������(Best Case) : O(1)
    // ������� ������(Average Case) : O(1)
    // ������ ������(Worst Case) : O(1)
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getLeft();
        node->left = temp->getRight();
        temp->right = node;
        updateBalanceFactor(node);
        updateBalanceFactor(temp);

        return temp;
    }

    // ������� ��� ������ ��������
    // ������ ������(Best Case) : O(1)
    // ������� ������(Average Case) : O(1)
    // ������ ������(Worst Case) : O(1)
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getRight();
        node->right = temp->getLeft();
        temp->left = node;

        updateBalanceFactor(node);
        updateBalanceFactor(temp);

        return temp;
    }

    // ������� ��� ������������ ������
    //- ����� ����� ������ (LL-rotation):
    //��������� node ����� ������������� ����������� �������, ��� ��������, ��� ����� ��������� ���� �������.���� ����� ��������� ����� �� ����� ������� �������� ������� ���������, ����������� ������ �������.

    //����� ������ ������(LR - rotation) :
    //����� �� ����� ������������ ������ ���������, �� ������ ��������� ������ ���� ����(��� "������ ������").������� ����������� ����� ������� �� ����� ���������, ����� ������ ������� �� ������������ ����.
    
    //������ ������ ������(RR - rotation) :
    //� ���� ������ ���� ����� ������������� ����������� �������(������ ��������� ����), � ������ ��������� ����� �� ����� �������� ������ ���������.����� ����������� ����� �������.
    
    //������ ����� ������(RL - rotation) :
    //������ "����������" � ������ ���������, ��� ����� ��������� ������� ���� ����� �������.����������� ������� ������ ������� �� ������ ���������, ����� ����� �������.
   //������ ������: O(1)
   //������� ������ : O(log n)
   //������ ������ : O(log n)
    AVLTreeNode<T>* balanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        updateBalanceFactor(node);
        // ����� ����� ������
        if (node->balanceFactor > 1 && node->getLeft()->balanceFactor >= 0)
            return rotateRight(node);
        // ����� ������ ������
        if (node->balanceFactor > 1 && node->getLeft()->balanceFactor < 0) {
            node->left = rotateLeft(node->getLeft());
            return rotateRight(node);
        }
        // ������ ������ ������
        if (node->balanceFactor < -1 && node->getRight()->balanceFactor <= 0)
            return rotateLeft(node);
        // ������ ����� ������
        if (node->balanceFactor < -1 && node->getRight()->balanceFactor > 0) {
            node->right = rotateRight(node->getRight());
            return rotateLeft(node);
        }
        return node; 
    }


    // ������� ��� �������� ���� �� ������
    //������ ������: O(1)
    //������� ������ : O(log n)
    //������ ������ : O(log n)
    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr;
        }

        if (data < node->n_data) {
            node->n_left = deleteNode(node->getLeft(), data);
        }
        else if (data > node->n_data) {
            node->n_right = deleteNode(node->getRight(), data);
        }
        else {
            if (node->getLeft() == nullptr) {
                AVLTreeNode<T>* temp = node->getRight();
                delete node;
                return temp;
            }
            else if (node->getRight() == nullptr) {
                AVLTreeNode<T>* temp = node->getLeft();
                delete node;
                return temp;
            }

            AVLTreeNode<T>* temp = node->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft();
            }

            node->n_data = temp->n_data;
            node->n_right = deleteNode(node->getRight(), temp->n_data);
        }

        return balanceTree(node);
    }

    // ������� �������� � AVL ������
    // ������ ������: O(1)
    // ������� ������ : O(log n)
    // ������ ������ : O(log n)
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T value) {
        if (node == nullptr) {
            return new AVLTreeNode<T>(value); // ������ ����� ����
        }
        if (value < node->data) {
            node->left = insert(node->getLeft(), value); // ��������� � ����� ���������
        }
        else if (value > node->data) {
            node->right = insert(node->getRight(), value); // ��������� � ������ ���������
        }
        else {
            return node; 
        }
        return balanceTree(node); 
    }

    // ��������������� ����� ��� ������������ ������
    // ������ ������: O(1)
    //������� ������ : O(log n)
     //������ ������ : O(log n)
    AVLTreeNode<T>* findEl(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr; // ���� �� ������
        }

        if (data < node->n_data) {
            return findHelper(node->getLeft(), data); // ���� � ����� ���������
        }
        else if (data > node->n_data) {
            return findHelper(node->getRight(), data); // ���� � ������ ���������
        }
        else {
            return node; 
        }
    }


    //�������� ���� ��������
    void clearAll(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        clearAll(node->getLeft());
        clearAll(node->getRight());
        delete node;
    }



    // ����������� ����� ������
    void PrintT(AVLTreeNode<T>* node) {
        if (node) {
            PrintT(node->getLeft()); // ������� ����� ���������
            cout << node->data << " "; 
            PrintT(node->getRight()); // ������� ������ ���������
        }
    }

public:
    // �����������
    AVLTree() : root(nullptr) {}

    // ������� �������� � ������
    void insert(T value) {
        // ������� �������� � ���������� �����
        root = insert(root, value); 
    }

    // ���������� ������
    void display() {
        PrintT(root);
        cout << endl; 
    }

    // ������� ��� �������� �������� �� ������
    void remove(const T& data) {
        root = deleteNode(root, data);
    }

    // ����� ��� ������ �������� � ������
        AVLTreeNode<T>*find(const T & data) {
        return findEl(root, data);
    }


        //����� �������� ��� AVLTreeNode (LNR, Inorder)
        class Iterator {
        private:
            AVLTreeNode<T>* root;
            stack<AVLTreeNode<T>*> nodeSc;

        public:
            // ����������� ��������� 
            Iterator(AVLTreeNode<T>* n_root) {
                root = n_root;
                //����� ��� ���������� 
                pushLeftBranch(n_root);
            } 

            // �������� �������� �� ���������
            bool operator==(const Iterator& other) const {
                return nodeSc.empty() == other.nodeSc.empty();
            }

            // �������� ���� �� ��������� �������
            bool hasNext() const {

                return !nodeSc.empty();
            }

            // �������� �������� �� �����������
            bool operator!=(const Iterator& other) const {
                return !(hasNext() == false && other.hasNext() == false);
            }
            // �������� �������������
            T& operator*() const {
                return nodeSc.top()->data;
            }

            // ��������� ���������� 
            T& data() {
                return nodeSc.top()->data;
            }

            // �������� ����������
            Iterator& operator++() {
                return next();
            }

            // ����� ���������
            void reset() {
                while (!nodeSc.empty())
                    nodeStack.pop();
                pushLeftBranch(root);
            }

            // ������� � ���������� ��������
            Iterator& next() {
                AVLTreeNode<T>* currentNode;
                if (!hasNext()) {
                    throw std::out_of_range("No more elements in the iterator");
                }
                currentNode = nodeSc.top();
                nodeSc.pop();
                pushLeftBranch(currentNode->getRight());
                return *this;
            }

        private:
            // ����� ���������� ��� ����� ���� ���� node � nodeStack
            void pushLeftBranch(AVLTreeNode<T>* node) {
                while (node != nullptr) {
                    nodeSc.push(node);
                    node = node->getLeft();
                }
            }
        };

        // ���������� �������� �� ������ ������
        Iterator begin() const {
            return Iterator(root);
        }

        // ��������� �������� �� ����� ������
        Iterator end() const {
            return Iterator(nullptr);
        }

        //�������� ������
        void clear() {
            if (root)
            {
                clearAll(root);
                root = nullptr;
            }
        }

};






template<typename T>
void testInsert() {
    AVLTree<int> tree;

    // ������ ������: ������� � ������ ������
    AVLTreeNode<int>* root = tree.insert(nullptr, 10);
    assert(root != nullptr && root->data == 10);
    assert(root->balanceFactor == 0);

    // ������� ������: ������� ���������������� �����, �������� ������
    root = tree.insert(root, 5);
    root = tree.insert(root, 15);
    root = tree.insert(root, 12);
    root = tree.insert(root, 17);

    // ��������, ��� ������������ �����������
    assert(root->data == 10);
    assert(root->balanceFactor == 0);  // ������ ������ ���� ��������������
    assert(root->getLeft()->data == 5);
    assert(root->getRight()->data == 15);
    

    // 1. �������� �� ������ ������: ������� ���� �� ������� ������
    assert(tree.deleteNode(nullptr, 10) == nullptr); // ������ �������� ������

    // 2. ��������� �������� ��� �������� �������� �� ��������� ��������: 
    //    (����� ������������ 1, 2, 3, 4, 5, ����� ������� ���������������� ������)
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    tree.insert(5);

    // 3. �������� ��������� ������ ����� �������
    assert(tree.root->n_data == 3); // ������ ������ ���� 3
    assert(tree.root->getLeft()->data == 1); // ����� ���������
    assert(tree.root->getRight()->n_data == 4); // ������ ���������
    assert(tree.root->getRight()->getRight()->data == 5); // ������ ��������� 4
    assert(tree.root->getLeft()->getRight()->data == 2); // ������ ��������� 1

    // 4. ������� ������: �������� ���� � ����� ��������
    assert(tree.deleteNode(tree.root, 1) != nullptr); // ������� 1
    assert(tree.root->getLeft()->data == 2); // 2 ������ � ����� ���������

    // 5. �������� ���� � ����� ���������
    assert(tree.deleteNode(tree.root, 3) != nullptr); // ������� 3 (���� � ����� ���������)
    assert(tree.root->data == 4); // ������ ������ ������ ���� 4

    // 6. ������ ������: �������� ����, ������� �������� � �������������� ������
    assert(tree.deleteNode(tree.root, 5) != nullptr); // ������� 5, ��� ����� ����������� ��������������

    // 7. ��������� ��������� ������ ����� ���� ��������
    assert(tree.root->data == 4); // ������ �������� 4 ����� �������� 5
    assert(tree.root->getLeft()->data == 2); // ����� ���������
    assert(tree.root->getRight() == nullptr); // ������ ��������� ������ ���� nullt(root->getRight()->getLeft()->data == 12);
    assert(root->getRight()->getRight()->data == 17);

    // ������ ������: �������, ��������� ���������� ���������
    root = tree.insert(root, 3);
    root = tree.insert(root, 2); // ��� ������� RR-rotation
    assert(root->data == 5);
    assert(root->getLeft()->data == 2);
    assert(root->getLeft()->getLeft()->data == 3);
    assert(root->getRight()->data == 10); // ������ ������ ���� �������������
}

template<typename T>
void testInsert2() {
    AVLTree<int> tree;

    // �������� ���������
    AVLTreeNode<int>* node1 = new AVLTreeNode<int>(2);
    AVLTreeNode<int>* node2 = new AVLTreeNode<int>(1);
    AVLTreeNode<int>* node3 = new AVLTreeNode<int>(3);

    node1->left = node2;  // 2 - ��� ��������, 1 - ����� �������
    node1->right = node3; // 3 - ������ �������

    // �������� ������� ��������
    AVLTreeNode<int>* new_root = tree.rotateRight(node1);
    assert(new_root->n_data == 1); // ����� ������ ������ ���� 1
    assert(new_root->getRight()->data == 2); // 2 ������ ������ �������
    assert(new_root->getRight()->getRight()->data == 3); // 3 �������� ������ �������� 2

    // �������� ������ ��������
    AVLTreeNode<int>* node4 = new AVLTreeNode<int>(4);
    AVLTreeNode<int>* node5 = new AVLTreeNode<int>(5);

    node4->right = node5;  // 4 - ��������, 5 - ������ �������

    AVLTreeNode<int>* new_root_left = tree.rotateLeft(node4);
    assert(new_root_left->n_data == 5); // ����� ������ ������ ���� 5
    assert(new_root_left->getLeft()->data == 4); // 4 ������ ����� �������
}


template<typename T>
void testInsert3() {
AVLTree<int> tree;

// 1. �������� ������� � ������
tree.insert(10);
tree.insert(20);
tree.insert(5);
tree.insert(15);
tree.insert(25);

// ��������, ��� �������� ����������
assert(tree.search(10) != nullptr); // 10 ������ ������������
assert(tree.search(15) != nullptr); // 15 ������ ������������
assert(tree.search(5) != nullptr);  // 5 ������ ������������
assert(tree.search(20) != nullptr); // 20 ������ ������������
assert(tree.search(25) != nullptr); // 25 ������ ������������

// ��������, ��� �������������� �������� ���������� nullptr
assert(tree.search(100) == nullptr); // 100 �� ����������
assert(tree.search(-1) == nullptr);   // -1 �� ����������
}



template<typename T>
void testInsert4() {
AVLTree<int> tree;

// 1. ������������ �������
tree.insert(30);
tree.insert(20);
tree.insert(40);
tree.insert(10);
tree.insert(25);
tree.insert(50);

// �������� ���������
std::vector<int> expected = { 10, 20, 25, 30, 40, 50 };
std::vector<int> result;

for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}

assert(result == expected); // ��������� ������ ��������� � ��������� ��������

// 2. �������� �� ���������
tree.insert(20); // ��������, �� ������ ���� ���������
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected); // ��������� ������ ��������� � ��������� ��������

// 3. �������� ��������
// �������� ����� � ������� ���������
tree.remove(10); // ������� ����
expected = { 20, 25, 30, 40, 50 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

tree.remove(30); // ������� ���� � ����� ������
expected = { 20, 25, 40, 50 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

tree.remove(40); // ������� ���� � ����� ��������
expected = { 20, 25, 50 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

// 4. �������� ��������� ����� ���������� ��������
tree.remove(50); // ������� ��������� �������
tree.remove(20); // ������� ��������� �������
expected = { 25 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

// 5. �������� ���� ���������
tree.remove(25); // ������ ������ �����
expected = {};
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

// ��������, ��� ������ ������������� ������
assert(tree.begin() == tree.end());
}