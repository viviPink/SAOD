
#include <iostream>

#include "TreeNode.h"
#include "AVLTree.h"

// Пример использования
int main() {
    //testInsert2();
    AVLTree<int> avlTree;

    avlTree.insert(20);
    avlTree.insert(30);
    avlTree.insert(10);
    avlTree.insert(5);
    avlTree.insert(3);

    avlTree.display(); // 3 5 10 20 30

    return 0;
}

