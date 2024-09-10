
#include <iostream>
#include <cassert>

#include "TreeNode.h" 

using namespace std;
int main() {

    BinaryTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(9);
    tree.insert(6);
    //tree.insert(12);
    //tree.insert(13);
    //tree.insert(10);
    tree.insert(1);
    tree.insert(-22);
    tree.insert(2);
    tree.insert(3);
    //tree.insert(4);
    //tree.insert(5);
    //tree.insert(8);
 

    const int data = tree.getNodeData(tree.root->right);

    cout << "Data : " << data << endl;

    tree.printTree(tree.root);
    NLR(tree.root);

}