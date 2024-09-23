
#pragma once
//Пинчукова Гера ИВТ-22
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


/// <summary>
//Шаблонный класс для узла дерева
//     18
//   /   \ 
//  5     20
// / \   /  \
//4   7  21  22
/// </summary>
template<typename T>
class TreeNode {
public:
    //данные, которые хранятся в узле
    T data;
    //указатель на левый узел
    TreeNode<T>* left;
    //указатель на правый узел
    TreeNode<T>* right;

    /// <summary>
    /// конструктор по умолчанию
    /// </summary>
    TreeNode() : data(T()), left(nullptr), right(nullptr) {}

    /// <summary>
    /// констртуктор с параметрами (указателями на левый и правый узлы)
    /// </summary>
    /// <param name="data"> данные узла дерева </param>
    /// <param name="l"> левый узел </param>
    /// <param name="r"> правый узел </param>
    TreeNode(const T& data, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr) : data(data), left(l), right(r) {}
};


/// <summary>
/// Шаблонный классс бинарного дерева поиска
/// </summary>
template<typename T>
class BinaryTree {
public:
    //корень дерева
    TreeNode<T>* root;

    /// <summary>
    /// Кончтруктор дерева без параметра
    /// </summary>
    BinaryTree() : root(nullptr) {}

    /// <summary>
    /// Деструктор дерева
    /// </summary>
    ~BinaryTree() {
        deleteTree(root);
    }

    /// <summary>
    /// функция для вставки узла в дерево
    /// </summary>
    /// <param name="data"> данные для вставки </param>
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


    /// <summary>
    /// удаление дерева (обход lrn)
    /// </summary>
    /// <param name="node"> узел который нужно удалить </param>
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

    /// <summary>
    /// Вывод дерева на экран 
    /// </summary>
    /// <param name="node"> узел который нужно вывести</param>
    /// <param name="level"> начальный уровень для вывода</param>
    template<typename T>
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
    template<typename T>
    const T& getNodeData(TreeNode<T>* node) {
        return node->data;
    }


    /// <summary>
    /// LNR симметричный обход дерева (Инфиксный обход)
    /// </summary>
    /// <returns> возращает результат обхода сначала левого поддерева, затем текущего узла , потом правое поддерево </returns>
    vector<T> inorder() {
        vector<T> result;
        LNR(root, result);
        return result;
    }
   

    /// <summary>
    /// NLR прямой обход дерева 
    /// </summary возращает значение охода корня потом поддеревьев левого и правого>
    /// <returns></returns>
    vector<T> preorder() {
        vector<T> result;
        NLP(root, result);
        return result;
    }


    /// <summary>
    /// LRN обратный обход дерева
    /// </summary>
    /// <returns>возращает результат левого и правого поддерева а затем корня </returns>
    vector<T> postorder() {
        vector<T> result;
        LRN(root, result);
        return result;
    }


    /// <summary>
    /// поиск глубины дерева
    /// </summary>
    void depth() const {
        return getDepth(root);
    }

    /// <summary>
    /// поиск количества узлов дерева
    /// </summary>
    void count() const {
        return getNodeCount(root);
    }

    /// <summary>
    /// вывод инордерного массива
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
    /// вывод постордерного массива
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
    /// вывод преордерного массива
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
/// рекурсивная вспомогательная функция прямого обхода NLR и записи данных в вектор 
/// </summary>
/// <typeparam name="T"> тип данных </typeparam>
/// <param name="node"> указатель на текущий узел  </param>
 template<typename T>
 void NLR(TreeNode<T>* node, vector<T>& res) {
     if (node) {
         result.push_back(node->data);
         NLRApply(node->left, res);
         NLRApply(node->right, res);
     }
 }

 /// <summary>
 /// рекурсивная вспомогательная функция LNR симметричного обхода и записи данных в вектор  
 /// </summary>
 /// <param name="node"> указатель на текущий узел </param>
 template<typename T>
 void LNR(TreeNode<T>* node, vector<T>& res) {
     if (node) {
         LNRApply(node->left, res);
         result.push_back(node->data);
         LNRApply(node->right, res);
     }
 }

 /// <summary>
 /// рекурсивная вспомогательная функция LRN обратного обхода и записи данных в вектор  
 /// </summary>
 /// <param name="node"> указатель на текущий узел </param>
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
/// рекурсивная вспомогательная функция прямого обхода и печати дерева NLR
/// </summary>
/// <typeparam name="T"> тип данных </typeparam>
/// <param name="node"> указатель на текущий узел  </param>
template<typename T>
void NLRApply(TreeNode<T>* node, const function<void(T&)>& funct) {
    if (node) {
        funct(node->data);
        NLRApply(node->left, funct);
        NLRApply(node->right, funct);
    }
}

/// <summary>
/// рекурсивная вспомогательная функция симметричного обхода и печати дерева LNR
/// </summary>
/// <param name="node"> указатель на текущий узел </param>
template<typename T>
void LNRApply(TreeNode<T>* node, const function<void(T&)>& funct) {
    if (node) {
        LNRApply(node->left);
        funct(node->data);
        LNRApply(node->right);
    }
}

/// <summary>
/// рекурсивная вспомогательная функция обратного обхода и печати дерева LRN
/// </summary>
/// <param name="node"> указатель на текущий узел </param>
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
/// функция для получения глубины дерева
/// </summary>
/// <typeparam name="Type"></typeparam>
/// <param name="node">указатель на текущий узел </param>
/// <returns>Возвращаем максимальную глубину из левого и правого поддеревьев, увеличенную на 1</returns>
template <typename Type>
int getDepth(TreeNode<Type>* node) {
    if (node == nullptr) {
        return 0; // Если узел пустой, глубина равна 0
    }
    else {
        // Рекурсивно находим глубину левого и правого поддеревьев
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        // Возвращаем максимальную глубину из левого и правого поддеревьев, увеличенную на 1
        return max(leftDepth, rightDepth) + 1;
    }
}

/// <summary>
/// функция для поиска количества узлов в дереве
/// </summary>
/// <param name="node"> указатель на текущий узел </param>
/// <returns>Возвращаем общее количество узлов, увеличенное на 1</returns>
template <typename Type>
int getNodeCount(TreeNode<Type>* node) {
    if (node == nullptr) {
        return -1; // Если узел пустой, количество узлов равно -1
    }
    else {
        // Рекурсивно находим количество узлов в левом и правом поддеревьях
        int leftCount = getNodeCount(node->left);
        int rightCount = getNodeCount(node->right);
        // Возвращаем общее количество узлов, увеличенное на 1 (текущий узел)
        return leftCount + rightCount + 1;
    }
}


template <typename Type>
TreeNode<Type>* copyTree(TreeNode<Type>* node) {
    if (node == nullptr) {
        return nullptr; // Если узел пустой, возвращаем nullptr
    }

    // Создаем новый узел с такими же данными, как в текущем узле
    TreeNode<Type>* newNode = new TreeNode<Type>(node->data);

    // Рекурсивно копируем левое и правое поддерево
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode; // Возвращаем указатель на корень новой копии дерева
}

template <typename Type>
TreeNode<Type>* removeNode(TreeNode<Type>** root, const Type& data, TreeNode<Type>* parent = nullptr) {
    // Если корень дерева равен nullptr, значит узел не найден, возвращаем nullptr
    if (*root == nullptr) {
        return nullptr;
    }

    // Если значение, которое нужно удалить, меньше значения в текущем узле,
    // то ищем его в левом поддереве
    if (data < (*root)->data) {
        (*root)->left = removeNode(&(*root)->left, data, *root);
    }
    // Если значение, которое нужно удалить, больше значения в текущем узле,
    // то ищем его в правом поддереве
    else if (data > (*root)->data) {
        (*root)->right = removeNode(&(*root)->right, data, *root);
    }
    // Если значение в текущем узле равно значению, которое нужно удалить,
    // значит мы нашли узел для удаления
    else {
        // Сохраняем указатель на узел, который нужно удалить
        TreeNode<Type>* nodeToDelete = *root;

        // Если у узла нет детей
        if ((*root)->left == nullptr && (*root)->right == nullptr) {
            // Если это корень дерева, то просто устанавливаем корень в nullptr
            if (parent == nullptr) {
                *root = nullptr;
            }
            // Иначе обновляем ссылку на этот узел в родительском узле
            else if (parent->left == *root) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            // Удаляем узел
            delete nodeToDelete;
            return nullptr;
        }
        // Если у узла есть только левый ребенок
        else if ((*root)->left != nullptr && (*root)->right == nullptr) {
            // Обновляем указатель на корень, чтобы он указывал на левого ребенка
            *root = (*root)->left;
            // Удаляем удаляемый узел
            delete nodeToDelete;
            return *root;
        }
        // Если у узла есть только правый ребенок
        else if ((*root)->left == nullptr && (*root)->right != nullptr) {
            // Обновляем указатель на корень, чтобы он указывал на правого ребенка
            *root = (*root)->right;
            // Удаляем удаляемый узел
            delete nodeToDelete;
            return *root;
        }
        // Если у узла есть оба ребенка
        else {
            // Находим преемника (самый левый элемент в правом поддереве)
            TreeNode<Type>* successor = (*root)->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            // Копируем данные преемника в удаляемый узел
            (*root)->data = successor->data;
            // Рекурсивно удаляем преемника из правого поддерева
            (*root)->right = removeNode(&(*root)->right, successor->data, *root);
        }
    }

    // Возвращаем обновленный указатель на корень
    return *root;
}

/// <summary>
/// Поиск минимального элемента массива
/// </summary>
template <typename Type>
TreeNode<Type>* findMinNode(TreeNode<Type>* node) {
    if (node->left == nullptr) {
        return node; // Если левый ребенок nullptr, то текущий узел - минимальный
    }
    return findMinNode(node->left); // Иначе ищем минимальный элемент в левом поддереве
}

/// <summary>
   /// Функция для поиска элемента в дереве
   /// </summary>
   /// <param name="value"> значение элемента, который нужно найти </param>
   /// <returns> указатель на найденный узел или nullptr, если элемент не найден </returns>
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
/// Функция для поиска следующего максимального элемента в дереве
/// </summary>
/// <param name="node"> узел, для которого нужно найти следующий максимальный элемент </param>
/// <returns> указатель на следующий максимальный узел или nullptr, если такого нет </returns>
template <typename Type>
TreeNode<Type>* succ(TreeNode<Type>* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->right != nullptr) {
        // Если у текущего узла есть правый потомок, то следующий максимальный
        // элемент - это самый левый элемент правого поддерева
        TreeNode<T>* current = node->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    else {
        // Если у текущего узла нет правого потомка, то следующий максимальный элемент -
        // это первый предок, для которого текущий узел находится в левом поддереве
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


int main() {
    // Создаем дерево
    BinaryTree<int> tree;
    tree.insert(18);
    tree.insert(5);
    tree.insert(20);
    tree.insert(4);
    tree.insert(7);
    tree.insert(21);  
    tree.insert(22);

    // Проверяем глубину дерева
    int depth = getDepth(tree.root);
    std::cout << "Depth  " << depth << std::endl; // Ожидаемый вывод: 4

    // Проверяем количество узлов в дереве
    int nodeCount = getNodeCount(tree.root);
    std::cout << "Number " << nodeCount << std::endl; // Ожидаемый вывод: 7

    // Создаем копию дерева
    BinaryTree<int> treeCopy;
    treeCopy.root = copyTree(tree.root);

    // Удаляем узел по значению
    bool removed = removeNode(&tree.root, 5);
    std::cout << "Node removed " << removed << std::endl; // Ожидаемый вывод: true

}
