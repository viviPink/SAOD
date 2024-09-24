// TreeNodes.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "TreeNode.h"

///----------------
int main() {
    // Создаем узлы
    TreeNode<int>* node18 = new TreeNode<int>(18);
    TreeNode<int>* node5 = new TreeNode<int>(5);
    TreeNode<int>* node20 = new TreeNode<int>(20);
    TreeNode<int>* node4 = new TreeNode<int>(4);
    TreeNode<int>* node7 = new TreeNode<int>(7);
    TreeNode<int>* node21 = new TreeNode<int>(21);
    TreeNode<int>* node22 = new TreeNode<int>(22);

    // Связываем узлы
    node18->left = node5;
    node18->right = node20;
    node5->left = node4;
    node5->right = node7;
    node20->left = node21;
    node20->right = node22;

    // Создаем дерево
    BinaryTree<int> tree;
    tree.root = node18;

    // Проверяем глубину дерева
    int depth = getDepth(tree.root);
    cout << "Depth " << depth << endl; // Ожидаемый вывод: 4

    // Проверяем количество узлов в дереве
    int nodeCount = getNodeCount(tree.root);
    cout << "Number of nodes  " << nodeCount << endl; // Ожидаемый вывод: 7

    // Удаляем дерево
    tree.deleteTree(tree.root);
}


//int main() {
    // Создаем дерево
   // BinaryTree<int> tree;
    //tree.insert(18);
    //tree.insert(5);
    //tree.insert(20);
    //tree.insert(4);
    //tree.insert(7);
    //tree.insert(21);
    //tree.insert(22);

    // Проверяем глубину дерева
    //int depth = getDepth(tree.root);
    //std::cout << "Depth  " << depth << std::endl; // Ожидаемый вывод: 4

    // Проверяем количество узлов в дереве
    //int nodeCount = getNodeCount(tree.root);
   // std::cout << "Number " << nodeCount << std::endl; // Ожидаемый вывод: 7

    // Создаем копию дерева
    //BinaryTree<int> treeCopy;
    //treeCopy.root = copyTree(tree.root);

    // Удаляем узел по значению
    //bool removed = removeNode(&tree.root, 5);
   // std::cout << "Node removed " << removed << std::endl;

