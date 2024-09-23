
#pragma once
//��������� ���� ���-22
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


/// <summary>
//��������� ����� ��� ���� ������
//     18
//   /   \ 
//  5     20
// / \   /  \
//4   7  21  22
/// </summary>
template<typename T>
class TreeNode {
public:
    //������, ������� �������� � ����
    T data;
    //��������� �� ����� ����
    TreeNode<T>* left;
    //��������� �� ������ ����
    TreeNode<T>* right;

    /// <summary>
    /// ����������� �� ���������
    /// </summary>
    TreeNode() : data(T()), left(nullptr), right(nullptr) {}

    /// <summary>
    /// ������������ � ����������� (����������� �� ����� � ������ ����)
    /// </summary>
    /// <param name="data"> ������ ���� ������ </param>
    /// <param name="l"> ����� ���� </param>
    /// <param name="r"> ������ ���� </param>
    TreeNode(const T& data, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr) : data(data), left(l), right(r) {}
};


/// <summary>
/// ��������� ������ ��������� ������ ������
/// </summary>
template<typename T>
class BinaryTree {
public:
    //������ ������
    TreeNode<T>* root;

    /// <summary>
    /// ����������� ������ ��� ���������
    /// </summary>
    BinaryTree() : root(nullptr) {}

    /// <summary>
    /// ���������� ������
    /// </summary>
    ~BinaryTree() {
        deleteTree(root);
    }

    /// <summary>
    /// ������� ��� ������� ���� � ������
    /// </summary>
    /// <param name="data"> ������ ��� ������� </param>
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


    /// <summary>
    /// �������� ������ (����� lrn)
    /// </summary>
    /// <param name="node"> ���� ������� ����� ������� </param>
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

    /// <summary>
    /// ����� ������ �� ����� 
    /// </summary>
    /// <param name="node"> ���� ������� ����� �������</param>
    /// <param name="level"> ��������� ������� ��� ������</param>
    template<typename T>
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
    template<typename T>
    const T& getNodeData(TreeNode<T>* node) {
        return node->data;
    }


    /// <summary>
    /// LNR ������������ ����� ������ (��������� �����)
    /// </summary>
    /// <returns> ��������� ��������� ������ ������� ������ ���������, ����� �������� ���� , ����� ������ ��������� </returns>
    vector<T> inorder() {
        vector<T> result;
        LNR(root, result);
        return result;
    }
   

    /// <summary>
    /// NLR ������ ����� ������ 
    /// </summary ��������� �������� ����� ����� ����� ����������� ������ � �������>
    /// <returns></returns>
    vector<T> preorder() {
        vector<T> result;
        NLP(root, result);
        return result;
    }


    /// <summary>
    /// LRN �������� ����� ������
    /// </summary>
    /// <returns>��������� ��������� ������ � ������� ��������� � ����� ����� </returns>
    vector<T> postorder() {
        vector<T> result;
        LRN(root, result);
        return result;
    }


    /// <summary>
    /// ����� ������� ������
    /// </summary>
    void depth() const {
        return getDepth(root);
    }

    /// <summary>
    /// ����� ���������� ����� ������
    /// </summary>
    void count() const {
        return getNodeCount(root);
    }

    /// <summary>
    /// ����� ����������� �������
    /// </summary>
    void printInorder() {
        vector<Type> result = inorder();
        cout << "Inorder" << endl;
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    /// <summary>
    /// ����� ������������� �������
    /// </summary>
    void printPostorder() {
        vector<Type> result = postorder();
        cout << "Postorder " << endl;
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    /// <summary>
    /// ����� ������������ �������
    /// </summary>
    void printPreorder() {
        vector<Type> result = preorder();
        cout << "Preorder " << endl;
        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }



 };


//-------------------------------------------------------------------------------->
 /// <summary>
/// ����������� ��������������� ������� ������� ������ NLR � ������ ������ � ������ 
/// </summary>
/// <typeparam name="T"> ��� ������ </typeparam>
/// <param name="node"> ��������� �� ������� ����  </param>
 template<typename T>
 void NLR(TreeNode<T>* node, vector<T>& res) {
     if (node) {
         result.push_back(node->data);
         NLRApply(node->left, res);
         NLRApply(node->right, res);
     }
 }

 /// <summary>
 /// ����������� ��������������� ������� LNR ������������� ������ � ������ ������ � ������  
 /// </summary>
 /// <param name="node"> ��������� �� ������� ���� </param>
 template<typename T>
 void LNR(TreeNode<T>* node, vector<T>& res) {
     if (node) {
         LNRApply(node->left, res);
         result.push_back(node->data);
         LNRApply(node->right, res);
     }
 }

 /// <summary>
 /// ����������� ��������������� ������� LRN ��������� ������ � ������ ������ � ������  
 /// </summary>
 /// <param name="node"> ��������� �� ������� ���� </param>
 template<typename T>
 void LRN(TreeNode<T>* node, vector<T>& res) {
     if (node) {
         LRNApply(node->left, res);
         LRNApply(node->right, res);
         res.push_back(node->data);

     }
 }



//-------------------------------------------------------------------------------->

/// <summary>
/// ����������� ��������������� ������� ������� ������ � ������ ������ NLR
/// </summary>
/// <typeparam name="T"> ��� ������ </typeparam>
/// <param name="node"> ��������� �� ������� ����  </param>
template<typename T>
void NLRApply(TreeNode<T>* node, const function<void(T&)>& funct) {
    if (node) {
        funct(node->data);
        NLRApply(node->left, funct);
        NLRApply(node->right, funct);
    }
}

/// <summary>
/// ����������� ��������������� ������� ������������� ������ � ������ ������ LNR
/// </summary>
/// <param name="node"> ��������� �� ������� ���� </param>
template<typename T>
void LNRApply(TreeNode<T>* node, const function<void(T&)>& funct) {
    if (node) {
        LNRApply(node->left);
        funct(node->data);
        LNRApply(node->right);
    }
}

/// <summary>
/// ����������� ��������������� ������� ��������� ������ � ������ ������ LRN
/// </summary>
/// <param name="node"> ��������� �� ������� ���� </param>
template<typename T>
void LRNApply(TreeNode<T>* node, function<void(T&)>& funct) {
    if (node) {
        LRNApply(node->left);
        LRNApply(node->right);
        funct(node->data);

    }
}

//-------------------------------------------------------------->

/// <summary>
/// ������� ��� ��������� ������� ������
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <param name="node">��������� �� ������� ���� </param>
/// <returns>���������� ������������ ������� �� ������ � ������� �����������, ����������� �� 1</returns>
template <typename Type>
int getDepth(TreeNode<Type>* node) {
    if (node == nullptr) {
        return 0; // ���� ���� ������, ������� ����� 0
    }
    else {
        // ���������� ������� ������� ������ � ������� �����������
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        // ���������� ������������ ������� �� ������ � ������� �����������, ����������� �� 1
        return max(leftDepth, rightDepth) + 1;
    }
}

/// <summary>
/// ������� ��� ������ ���������� ����� � ������
/// </summary>
/// <param name="node"> ��������� �� ������� ���� </param>
/// <returns>���������� ����� ���������� �����, ����������� �� 1</returns>
template <typename Type>
int getNodeCount(TreeNode<Type>* node) {
    if (node == nullptr) {
        return -1; // ���� ���� ������, ���������� ����� ����� -1
    }
    else {
        // ���������� ������� ���������� ����� � ����� � ������ �����������
        int leftCount = getNodeCount(node->left);
        int rightCount = getNodeCount(node->right);
        // ���������� ����� ���������� �����, ����������� �� 1 (������� ����)
        return leftCount + rightCount + 1;
    }
}


template <typename Type>
TreeNode<Type>* copyTree(TreeNode<Type>* node) {
    if (node == nullptr) {
        return nullptr; // ���� ���� ������, ���������� nullptr
    }

    // ������� ����� ���� � ������ �� �������, ��� � ������� ����
    TreeNode<Type>* newNode = new TreeNode<Type>(node->data);

    // ���������� �������� ����� � ������ ���������
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode; // ���������� ��������� �� ������ ����� ����� ������
}

template <typename Type>
TreeNode<Type>* removeNode(TreeNode<Type>** root, const Type& data, TreeNode<Type>* parent = nullptr) {
    // ���� ������ ������ ����� nullptr, ������ ���� �� ������, ���������� nullptr
    if (*root == nullptr) {
        return nullptr;
    }

    // ���� ��������, ������� ����� �������, ������ �������� � ������� ����,
    // �� ���� ��� � ����� ���������
    if (data < (*root)->data) {
        (*root)->left = removeNode(&(*root)->left, data, *root);
    }
    // ���� ��������, ������� ����� �������, ������ �������� � ������� ����,
    // �� ���� ��� � ������ ���������
    else if (data > (*root)->data) {
        (*root)->right = removeNode(&(*root)->right, data, *root);
    }
    // ���� �������� � ������� ���� ����� ��������, ������� ����� �������,
    // ������ �� ����� ���� ��� ��������
    else {
        // ��������� ��������� �� ����, ������� ����� �������
        TreeNode<Type>* nodeToDelete = *root;

        // ���� � ���� ��� �����
        if ((*root)->left == nullptr && (*root)->right == nullptr) {
            // ���� ��� ������ ������, �� ������ ������������� ������ � nullptr
            if (parent == nullptr) {
                *root = nullptr;
            }
            // ����� ��������� ������ �� ���� ���� � ������������ ����
            else if (parent->left == *root) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            // ������� ����
            delete nodeToDelete;
            return nullptr;
        }
        // ���� � ���� ���� ������ ����� �������
        else if ((*root)->left != nullptr && (*root)->right == nullptr) {
            // ��������� ��������� �� ������, ����� �� �������� �� ������ �������
            *root = (*root)->left;
            // ������� ��������� ����
            delete nodeToDelete;
            return *root;
        }
        // ���� � ���� ���� ������ ������ �������
        else if ((*root)->left == nullptr && (*root)->right != nullptr) {
            // ��������� ��������� �� ������, ����� �� �������� �� ������� �������
            *root = (*root)->right;
            // ������� ��������� ����
            delete nodeToDelete;
            return *root;
        }
        // ���� � ���� ���� ��� �������
        else {
            // ������� ��������� (����� ����� ������� � ������ ���������)
            TreeNode<Type>* successor = (*root)->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            // �������� ������ ��������� � ��������� ����
            (*root)->data = successor->data;
            // ���������� ������� ��������� �� ������� ���������
            (*root)->right = removeNode(&(*root)->right, successor->data, *root);
        }
    }

    // ���������� ����������� ��������� �� ������
    return *root;
}

/// <summary>
/// ����� ������������ �������� �������
/// </summary>
template <typename Type>
TreeNode<Type>* findMinNode(TreeNode<Type>* node) {
    if (node->left == nullptr) {
        return node; // ���� ����� ������� nullptr, �� ������� ���� - �����������
    }
    return findMinNode(node->left); // ����� ���� ����������� ������� � ����� ���������
}

/// <summary>
   /// ������� ��� ������ �������� � ������
   /// </summary>
   /// <param name="value"> �������� ��������, ������� ����� ����� </param>
   /// <returns> ��������� �� ��������� ���� ��� nullptr, ���� ������� �� ������ </returns>
   template <typename Type>
TreeNode<Type>* find(const Type& value) {
    TreeNode<T>* current = root;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

/// <summary>
/// ������� ��� ������ ���������� ������������� �������� � ������
/// </summary>
/// <param name="node"> ����, ��� �������� ����� ����� ��������� ������������ ������� </param>
/// <returns> ��������� �� ��������� ������������ ���� ��� nullptr, ���� ������ ��� </returns>
template <typename Type>
TreeNode<Type>* succ(TreeNode<Type>* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->right != nullptr) {
        // ���� � �������� ���� ���� ������ �������, �� ��������� ������������
        // ������� - ��� ����� ����� ������� ������� ���������
        TreeNode<T>* current = node->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    else {
        // ���� � �������� ���� ��� ������� �������, �� ��������� ������������ ������� -
        // ��� ������ ������, ��� �������� ������� ���� ��������� � ����� ���������
        TreeNode<T>* current = root;
        TreeNode<T>* successor = nullptr;
        while (current != node) {
            if (current->data > node->data) {
                successor = current;
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return successor;
    }
}


///----------------
int main() {
    // ������� ����
    TreeNode<int>* node18 = new TreeNode<int>(18);
    TreeNode<int>* node5 = new TreeNode<int>(5);
    TreeNode<int>* node20 = new TreeNode<int>(20);
    TreeNode<int>* node4 = new TreeNode<int>(4);
    TreeNode<int>* node7 = new TreeNode<int>(7);
    TreeNode<int>* node21 = new TreeNode<int>(21);
    TreeNode<int>* node22 = new TreeNode<int>(22);

    // ��������� ����
    node18->left = node5;
    node18->right = node20;
    node5->left = node4;
    node5->right = node7;
    node20->left = node21;
    node20->right = node22;

    // ������� ������
    BinaryTree<int> tree;
    tree.root = node18;

    // ��������� ������� ������
    int depth = getDepth(tree.root);
    cout << "Depth " << depth << endl; // ��������� �����: 4

    // ��������� ���������� ����� � ������
    int nodeCount = getNodeCount(tree.root);
    cout << "Number of nodes  " << nodeCount << endl; // ��������� �����: 7

    // ������� ������
    tree.deleteTree(tree.root);
}


int main() {
    // ������� ������
    BinaryTree<int> tree;
    tree.insert(18);
    tree.insert(5);
    tree.insert(20);
    tree.insert(4);
    tree.insert(7);
    tree.insert(21);  
    tree.insert(22);

    // ��������� ������� ������
    int depth = getDepth(tree.root);
    std::cout << "Depth  " << depth << std::endl; // ��������� �����: 4

    // ��������� ���������� ����� � ������
    int nodeCount = getNodeCount(tree.root);
    std::cout << "Number " << nodeCount << std::endl; // ��������� �����: 7

    // ������� ����� ������
    BinaryTree<int> treeCopy;
    treeCopy.root = copyTree(tree.root);

    // ������� ���� �� ��������
    bool removed = removeNode(&tree.root, 5);
    std::cout << "Node removed " << removed << std::endl; // ��������� �����: true

}
