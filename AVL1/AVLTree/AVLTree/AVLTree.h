#pragma once
#include "TreeNode.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Класс AVLTreeNode наследуется от TreeNode бинарного дерева поиска
template<typename T>
class AVLTreeNode : public TreeNode<T> {
public:
    // Коэффициент баланса узла
    signed char balanceFactor;

    // Конструктор по умолчанию
    AVLTreeNode() : TreeNode<T>(), balanceFactor(0) {}

    // Конструктор с параметрами
    AVLTreeNode(const T& data) : TreeNode<T>(data), balanceFactor(0) {}

    // Конструктор с параметрами 
    // (данные и указатели на предыдущий и следующий узлы)
    AVLTreeNode(const T& data, TreeNode<T>* getLeft, TreeNode<T>* getRight)
        : TreeNode<T>(data, getLeft, getRight), balanceFactor(0) {}


    // Преобразователь указателя на AVLTreeNode
    // возращается указатель на левого ребенка узла дерева
    //static_cast он используется для приведения указателя на базовый класс TreeNode<T> к указателю на производный класс AVLTreeNode<T>
    AVLTreeNode<T>* getLeft() {
        return static_cast<AVLTreeNode<T>*>(this->left);
    }

    // Преобразователь указателя на AVLTreeNode
    // возращается указатель на правого ребенка узла дерева на базовый класс TreeNode<T> к указателю на производный класс AVLTreeNode<T>
    AVLTreeNode<T>* getRight() {
        return static_cast<AVLTreeNode<T>*>(this->right);
    }

    //// Преобразователь указателя на (на левый)
    // TreeNode в указатель на AVLTreeNode (const версия)
    //const AVLTreeNode<T>* getLeft() const {
    //    return static_cast<const AVLTreeNode<T>*>(this->left);
    //}

    //// Преобразователь указателя на (на правый) 
    // TreeNode в указатель на AVLTreeNode (const версия)
    //const AVLTreeNode<T>* getRight() const {
    //    return static_cast<const AVLTreeNode<T>*>(this->right);
    //}
};

// Класс AVLTree (само сбалансированное бинарное дерево поиска)
template<typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root; // Указатель на корень дерева

    // Функция для обновления коэффициента баланса узла
    // O(log n/2) л
    // O(log n/2) c
    // O(log n/2) х
    void updateBalanceFactor(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        int leftHeight = getHeight(node->getLeft());
        int rightHeight = getHeight(node->getRight());
        node->balanceFactor = leftHeight - rightHeight;
    }

    // Функция для получения высоты узла
    //(Best Case): O(1)
    //(Average Case): O(log n)
    //(Worst Case) : O(n)
    int getHeight(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(getHeight(node->getLeft()), getHeight(node->getRight()));
    }

    // Функция для правого поворота
    // Лучший случай(Best Case) : O(1)
    // Средний случай(Average Case) : O(1)
    // Худший случай(Worst Case) : O(1)
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getLeft();
        node->left = temp->getRight();
        temp->right = node;
        updateBalanceFactor(node);
        updateBalanceFactor(temp);

        return temp;
    }

    // Функция для левого поворота
    // Лучший случай(Best Case) : O(1)
    // Средний случай(Average Case) : O(1)
    // Худший случай(Worst Case) : O(1)
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* temp = node->getRight();
        node->right = temp->getLeft();
        temp->left = node;

        updateBalanceFactor(node);
        updateBalanceFactor(temp);

        return temp;
    }

    // Функция для балансировки дерева
    //- Левый левый случай (LL-rotation):
    //Указатель node имеет положительный коэффициент баланса, что означает, что левое поддерево выше правого.Если левое поддерево также не имеет слишком большого правого поддерева, выполняется правый поворот.

    //Левый правый случай(LR - rotation) :
    //Здесь мы имеем преобладание левого поддерева, но правое поддерево левого узла выше(это "правый случай").Сначала выполняется левый поворот на левом поддереве, затем правый поворот на родительском узле.
    
    //Правый правый случай(RR - rotation) :
    //В этом случае узел имеет отрицательный коэффициент баланса(правое поддерево выше), и правое поддерево также не имеет длинного левого поддерева.Здесь выполняется левый поворот.
    
    //Правый левый случай(RL - rotation) :
    //Дерево "перекошено" в правом поддереве, где левое поддерево правого узла более высокое.Выполняется сначала правый поворот на правом поддереве, затем левый поворот.
   //Лучший случай: O(1)
   //Средний случай : O(log n)
   //Худший случай : O(log n)
    AVLTreeNode<T>* balanceTree(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        updateBalanceFactor(node);
        // Левый левый случай
        if (node->balanceFactor > 1 && node->getLeft()->balanceFactor >= 0)
            return rotateRight(node);
        // Левый правый случай
        if (node->balanceFactor > 1 && node->getLeft()->balanceFactor < 0) {
            node->left = rotateLeft(node->getLeft());
            return rotateRight(node);
        }
        // Правый правый случай
        if (node->balanceFactor < -1 && node->getRight()->balanceFactor <= 0)
            return rotateLeft(node);
        // Правый левый случай
        if (node->balanceFactor < -1 && node->getRight()->balanceFactor > 0) {
            node->right = rotateRight(node->getRight());
            return rotateLeft(node);
        }
        return node; 
    }


    // Функция для удаления узла из дерева
    //Лучший случай: O(1)
    //Средний случай : O(log n)
    //Худший случай : O(log n)
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

    // Вставка значения в AVL дерево
    // Лучший случай: O(1)
    // Средний случай : O(log n)
    // Худший случай : O(log n)
    AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T value) {
        if (node == nullptr) {
            return new AVLTreeNode<T>(value); // Создаём новый узел
        }
        if (value < node->data) {
            node->left = insert(node->getLeft(), value); // Вставляем в левое поддерево
        }
        else if (value > node->data) {
            node->right = insert(node->getRight(), value); // Вставляем в правое поддерево
        }
        else {
            return node; 
        }
        return balanceTree(node); 
    }

    // Вспомогательный метод для рекурсивного поиска
    // Лучший случай: O(1)
    //Средний случай : O(log n)
     //Худший случай : O(log n)
    AVLTreeNode<T>* findEl(AVLTreeNode<T>* node, const T& data) {
        if (node == nullptr) {
            return nullptr; // Узел не найден
        }

        if (data < node->n_data) {
            return findHelper(node->getLeft(), data); // Ищем в левом поддереве
        }
        else if (data > node->n_data) {
            return findHelper(node->getRight(), data); // Ищем в правом поддереве
        }
        else {
            return node; 
        }
    }


    //удаление всех элеменов
    void clearAll(AVLTreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        clearAll(node->getLeft());
        clearAll(node->getRight());
        delete node;
    }



    // Рекурсивный обход дерева
    void PrintT(AVLTreeNode<T>* node) {
        if (node) {
            PrintT(node->getLeft()); // Обходим левое поддерево
            cout << node->data << " "; 
            PrintT(node->getRight()); // Обходим правое поддерево
        }
    }

public:
    // Конструктор
    AVLTree() : root(nullptr) {}

    // Вставка значения в дерево
    void insert(T value) {
        // Вставка значения и обновление корня
        root = insert(root, value); 
    }

    // содержимое дерева
    void display() {
        PrintT(root);
        cout << endl; 
    }

    // Функция для удаления элемента из дерева
    void remove(const T& data) {
        root = deleteNode(root, data);
    }

    // Метод для поиска элемента в дереве
        AVLTreeNode<T>*find(const T & data) {
        return findEl(root, data);
    }


        //Класс Итератор для AVLTreeNode (LNR, Inorder)
        class Iterator {
        private:
            AVLTreeNode<T>* root;
            stack<AVLTreeNode<T>*> nodeSc;

        public:
            // Конструктор итератора 
            Iterator(AVLTreeNode<T>* n_root) {
                root = n_root;
                //засем оно вызывается 
                pushLeftBranch(n_root);
            } 

            // Оператор проверки на равенства
            bool operator==(const Iterator& other) const {
                return nodeSc.empty() == other.nodeSc.empty();
            }

            // Проверка есть ли следующий элемент
            bool hasNext() const {

                return !nodeSc.empty();
            }

            // Оператор проверки на неравенства
            bool operator!=(const Iterator& other) const {
                return !(hasNext() == false && other.hasNext() == false);
            }
            // Оператор разыменования
            T& operator*() const {
                return nodeSc.top()->data;
            }

            // Получение информации 
            T& data() {
                return nodeSc.top()->data;
            }

            // Оператор инкремента
            Iterator& operator++() {
                return next();
            }

            // Сброс итератора
            void reset() {
                while (!nodeSc.empty())
                    nodeStack.pop();
                pushLeftBranch(root);
            }

            // Переход к следующему элементы
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
            // Метод помещающий все левые узлы узла node в nodeStack
            void pushLeftBranch(AVLTreeNode<T>* node) {
                while (node != nullptr) {
                    nodeSc.push(node);
                    node = node->getLeft();
                }
            }
        };

        // возвращает итератор на начало дерева
        Iterator begin() const {
            return Iterator(root);
        }

        // Переносит итератор на конец дерева
        Iterator end() const {
            return Iterator(nullptr);
        }

        //удаление дерева
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

    // Лучший случай: вставка в пустое дерево
    AVLTreeNode<int>* root = tree.insert(nullptr, 10);
    assert(root != nullptr && root->data == 10);
    assert(root->balanceFactor == 0);

    // Средний случай: вставка последовательных узлов, сохраняя баланс
    root = tree.insert(root, 5);
    root = tree.insert(root, 15);
    root = tree.insert(root, 12);
    root = tree.insert(root, 17);

    // Проверка, что балансировка сохранилась
    assert(root->data == 10);
    assert(root->balanceFactor == 0);  // Дерево должно быть сбалансировано
    assert(root->getLeft()->data == 5);
    assert(root->getRight()->data == 15);
    

    // 1. Проверка на лучший случай: удаляем узел из пустого дерева
    assert(tree.deleteNode(nullptr, 10) == nullptr); // Дерево остается пустым

    // 2. Добавляем элементы для создания сценария со случайным доступом: 
    //    (будем использовать 1, 2, 3, 4, 5, чтобы создать сбалансированное дерево)
    tree.insert(3);
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    tree.insert(5);

    // 3. Проверка состояния дерева после вставки
    assert(tree.root->n_data == 3); // Корень должен быть 3
    assert(tree.root->getLeft()->data == 1); // Левое поддерево
    assert(tree.root->getRight()->n_data == 4); // Правое поддерево
    assert(tree.root->getRight()->getRight()->data == 5); // Правое поддерево 4
    assert(tree.root->getLeft()->getRight()->data == 2); // Правое поддерево 1

    // 4. Средний случай: удаление узла с одним потомком
    assert(tree.deleteNode(tree.root, 1) != nullptr); // Удаляем 1
    assert(tree.root->getLeft()->data == 2); // 2 теперь в левом поддереве

    // 5. Удаление узла с двумя потомками
    assert(tree.deleteNode(tree.root, 3) != nullptr); // Удаляем 3 (узел с двумя потомками)
    assert(tree.root->data == 4); // Теперь корень должен быть 4

    // 6. Худший случай: удаление узла, который приводит к ребалансировке дерева
    assert(tree.deleteNode(tree.root, 5) != nullptr); // Удаляем 5, что может потребовать ребалансировки

    // 7. Проверяем состояние дерева после всех удалений
    assert(tree.root->data == 4); // Корень остается 4 после удаления 5
    assert(tree.root->getLeft()->data == 2); // Левое поддерево
    assert(tree.root->getRight() == nullptr); // Правое поддерево должно быть nullt(root->getRight()->getLeft()->data == 12);
    assert(root->getRight()->getRight()->data == 17);

    // Худший случай: вставка, требующая нескольких поворотов
    root = tree.insert(root, 3);
    root = tree.insert(root, 2); // Это вызовет RR-rotation
    assert(root->data == 5);
    assert(root->getLeft()->data == 2);
    assert(root->getLeft()->getLeft()->data == 3);
    assert(root->getRight()->data == 10); // Дерево должно быть приспособлено
}

template<typename T>
void testInsert2() {
    AVLTree<int> tree;

    // Проверка поворотов
    AVLTreeNode<int>* node1 = new AVLTreeNode<int>(2);
    AVLTreeNode<int>* node2 = new AVLTreeNode<int>(1);
    AVLTreeNode<int>* node3 = new AVLTreeNode<int>(3);

    node1->left = node2;  // 2 - это родитель, 1 - левый ребенок
    node1->right = node3; // 3 - правый ребенок

    // Проверка правого поворота
    AVLTreeNode<int>* new_root = tree.rotateRight(node1);
    assert(new_root->n_data == 1); // Новый корень должен быть 1
    assert(new_root->getRight()->data == 2); // 2 теперь правый потомок
    assert(new_root->getRight()->getRight()->data == 3); // 3 остается правым потомком 2

    // Проверка левого поворота
    AVLTreeNode<int>* node4 = new AVLTreeNode<int>(4);
    AVLTreeNode<int>* node5 = new AVLTreeNode<int>(5);

    node4->right = node5;  // 4 - родитель, 5 - правый ребенок

    AVLTreeNode<int>* new_root_left = tree.rotateLeft(node4);
    assert(new_root_left->n_data == 5); // Новый корень должен быть 5
    assert(new_root_left->getLeft()->data == 4); // 4 теперь левый потомок
}


template<typename T>
void testInsert3() {
AVLTree<int> tree;

// 1. Проверка вставки и поиска
tree.insert(10);
tree.insert(20);
tree.insert(5);
tree.insert(15);
tree.insert(25);

// Проверка, что элементы существуют
assert(tree.search(10) != nullptr); // 10 должен существовать
assert(tree.search(15) != nullptr); // 15 должен существовать
assert(tree.search(5) != nullptr);  // 5 должен существовать
assert(tree.search(20) != nullptr); // 20 должен существовать
assert(tree.search(25) != nullptr); // 25 должен существовать

// Проверка, что несуществующие элементы возвращают nullptr
assert(tree.search(100) == nullptr); // 100 не существует
assert(tree.search(-1) == nullptr);   // -1 не существует
}



template<typename T>
void testInsert4() {
AVLTree<int> tree;

// 1. Тестирование вставки
tree.insert(30);
tree.insert(20);
tree.insert(40);
tree.insert(10);
tree.insert(25);
tree.insert(50);

// Проверка итератора
std::vector<int> expected = { 10, 20, 25, 30, 40, 50 };
std::vector<int> result;

for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}

assert(result == expected); // Результат должен совпадать с ожидаемым порядком

// 2. Проверка на дубликаты
tree.insert(20); // дубликат, не должно быть изменений
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected); // Результат должен совпадать с ожидаемым порядком

// 3. Проверка удаления
// Удаления узлов с разными условиями
tree.remove(10); // Удаляем лист
expected = { 20, 25, 30, 40, 50 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

tree.remove(30); // Удаляем узел с двумя детьми
expected = { 20, 25, 40, 50 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

tree.remove(40); // Удаляем узел с одним ребенком
expected = { 20, 25, 50 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

// 4. Проверка итератора после нескольких удалений
tree.remove(50); // Удаляем последний элемент
tree.remove(20); // Удаляем последний элемент
expected = { 25 };
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

// 5. Удаление всех элементов
tree.remove(25); // теперь дерево пусто
expected = {};
result.clear();
for (auto it = tree.begin(); it != tree.end(); ++it) {
    result.push_back(*it);
}
assert(result == expected);

// Проверка, что дерево действительно пустое
assert(tree.begin() == tree.end());
}