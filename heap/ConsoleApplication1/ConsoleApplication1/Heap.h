#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

using namespace std;

/// <summary>
/// ��������� ����� ��� ���� min-heap
/// ������-������ ������� 
/// ���� ��� 
/// ����������� ������� ���
/// </summary>
template<typename T>
class MinHeap {
private:
    /// <summary>
    /// ������ ��� �������� ��������� ����
    /// </summary>
    vector<T> heap;

    /// <summary>
    /// ��������������� ������� ��� "�������" ��������
    /// ��������� ��� ����������� ������� ������ ��������
    /// � ������ ������� � ��������� ���� true
    /// BigO
    /// ������:O(1)
    /// �������:O(n)
    /// ������:O( n)
    /// </summary>
    /// <param name="index">������� ��������</param>
    void heapifyUp(size_t index) {
        //heapifyUpp(index);

        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            //���� ������� ��� ������ ��������, �� �������
            if (heap[index] >= heap[parentIndex]) return;
            // ������ �������
            swap(heap[index], heap[parentIndex]);
            // ��������� � ��������
            index = parentIndex;
        }
    }


    /// <summary>
    ///  ��������������� ������� ��� "���������" �������� � ����������� ����
    /// BigO
    /// ������:O(1)
    /// �������:O(n)
    /// ������:O(n)
    /// </summary>
    /// <param name="index">������� ��������</param>
    void heapifyDown(size_t index) {
        //heapifyDownn(index);

        int leftChild, rightChild, smallest; // ������� ��� ������ � ������� �����, � ����� ��� �����������
        // ���������, ���� �� ������� ��� ��������, ���� �� ����� ������� ����
        while (index < heap.size()) {
            leftChild = 2 * index + 1;  // ���������� ������� ������ �������
            rightChild = 2 * index + 2; // ���������� ������� ������� �������
            smallest = index; // �������������� smallest ������� ��������
            // ������� ���������� ������� ����� �������� � ��� �����(��������� ����� ���������)
            if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
                smallest = leftChild; // ��������� smallest, ���� ����� baby ������
            }
            if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
                smallest = rightChild; // ��������� smallest, ���� ������ baby ������
            }
            // ���� �������� ������ ��� ����� ����������� �� baby, ������� �� �������
            if (smallest == index) return;
            // ������ ������� ������� ������� � ���������� �� �����
            swap(heap[index], heap[smallest]);
            // ��������� � ����������� �������� ��� ���������� ��������
            index = smallest;
        }
    }

    //����� ��������� ��� ���� 
    class Iterator {
    private:
        // ������ �� ���� � ������� ������
        MinHeap<T>& minHeap;
        size_t index;

    public:
        // ����������� ���������
        Iterator(MinHeap<T>& heap, size_t idx) : minHeap(heap), index(idx) {}

        // �������� ������������� ��� ��������� ��������
        T& operator*() {
            return heap[index];
        }

        // �������� ���������� ��� ��������� ++
        Iterator& operator++() {
            ++index; // ����������� ������
            return *this; // ���������� ������� �������� ���������
        }

        //�������� ��������� ���������
        bool operator==(const Iterator& other) const {
            return &heap == &other.minHeap && index == other.index;
        }
        
        // �������� ��������� �����������
        bool operator!=(const Iterator& other) const {
            return index != other.index; // ���������� �������
        }

        //�������� �� ��������� ���������� �������� 
        bool HasNext() const{
            return index != heap.size();
    }
         //��������� �������� ����� ����������
         T& data() const {
             return heap[index];
        }


         //���������� ��������� � ������ ���� ��� ���� ��������
         Iterator& next() {
             if (!HasNext()) {
                 throw out_of_range("Iter null");
             }
             ++index;
             return *this;
         }

         //����� ���������� 
         void reset() {
             index = 0;
         }
         
    };


public:
    //����������� ������ ��� ���������� 
    MinHeap() {};

    /// <summary>
    /// ����������� ������ ���� � �����������
    /// </summary>
    /// <param name="data">������ �� ����������� ������
    ///  heap ������ � ���� ��� ���� </param>
    MinHeap(const vector<int>& data) : heap (data){
        buildMinHeap();
    };
    
    /// <summary>
    /// ������ ����������� ����
    /// </summary>
    void buildMinHeap() {
        // �������� � ���������� �� ��������� ���� � "����������" ����
        for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // �����, ������������ �������� �� ������
    Iterator begin() {
        return Iterator(*this, 0); // ���������� �������� �� ������ �������
    }

    // �����, ������������ �������� �� �����
    Iterator end() {
        return Iterator(*this, heap.size()); // ���������� �������� �� ��������� �������
    }

    /// <summary>
    /// ����� ��� ���������� ��������
    /// BigO
    /// ������:O(1)
    /// �������:O(log n)
    /// ������:O(log n)
    /// </summary>
    /// <param name="value"> ��������� ��������</param>
    void insert(T value) {
        heap.push_back(value); // ��������� ������� � ����� �������
        heapifyUp(heap.size() - 1); // ��������� ������� �����
    }

    /// <summary>
    /// ����� ��� �������� ������������ ��������
    /// ������:O(1)
    /// �������:O(1)
    /// ������:O(1)
    /// </summary>
    /// <returns>��������� ��� �������</returns>
    T extractMin() {
        //extractMini();
        if (heap.empty()) throw std::runtime_error("Heap is empty.");
        T minValue = heap[0]; // ��������� ����������� �������
        heap[0] = heap.back(); // �������� ��� ��������� ���������
        heap.pop_back(); // ������� ��������� �������
        heapifyDown(0); // �������� ����� ������
        return minValue; // ���������� ����������� �������
    }


    /// <summary>
    /// ����� ��� ������� � ������������ ��������
    /// BigO
    /// ������:O(1)
    /// �������:O(1)
    /// ������:O(1)
    /// </summary>
    /// <returns>���������� ������</returns>
    T peek() const {
        if (heap.empty()) throw std::runtime_error("Heap is empty.");
        return heap[0]; // ���������� ������
    }


    /// <summary>
    /// ����� ��� ��������� ������� ����
    ///  BigO
    /// ������:O(1)
    /// �������:O(1)
    /// ������:O(1)
    /// </summary>
    /// <returns>���������� ������ �������</returns>
    size_t size() const {
        return heap.size(); // ���������� ������ �������
    }

    /// <summary>
    /// ����� ��� ��������, ����� �� ����
    /// BigO
    /// ������:O(1)
    /// �������:O(1)
    /// ������:O(1)
    /// </summary>
    /// <returns>true ���� �����</returns>
    bool isEmpty() const {
        return heap.empty(); // ��������� �� ������� �������
    }

    // ��� ������������: ���������� ������� ��������� ���� � �� ������
    const vector<T>& getHeap() const {
        return heap;
    }



    /// <summary>
    /// ����� ��� ��������� �������, ��������������� ����
    /// BigO
    /// ������:O(1)
    /// �������:O(1)
    /// ������:O(1)
    /// </summary>
    /// <returns>���������� ������</returns>
    const vector<T>& toArray() const {
        return heap; // ���������� ������
    }

    ///// <summary>
    ///// ����� ��������� ��� ���� 
    ///// �� �������� ����� ���� 
    ///// </summary>
    //class Iterator {
    //private:
    //    // �������� �� ������� ������� ������� ���������
    //    typename vector<T>::iterator current;
    //public:
    //    // ����������� ���������, ����������� �������� ������ �������
    //    Iterator(typename vector<T>::iterator start) : current(start) {}
    //    // �������� �������������
    //    T& operator*() {
    //        return *current; // ��������� �������� ������ � �������� ��������
    //    }
    //    // �������� ������������� (����������)
    //    Iterator& operator++() {
    //        ++current; // ������� � ���������� ��������
    //        return *this; // ����������� �������� ���������
    //    }
    //    // �������� �����������
    //    bool operator!=(const Iterator& other) const {
    //        return current != other.current; // �������� �� ����������� ���� ����������
    //    }
    //    // ���������� �������� �� ������ �������
    //    Iterator begin() {
    //        return Iterator(heap.begin());
    //    }
    //    // ���������� �������� �� �������, ��������� �� ���������
    //    Iterator end() {
    //        return Iterator(heap.end());
    //    }
    //};

};



/// <summary>
///  ��������������� ������� ��� "���������" �������� � ����������� ����
/// BigO
/// ������:O(1)
/// �������:O(log n)
/// ������:O(log n)
/// </summary>
/// <param name="index">������� ��������</param>
// template<typename T>
//void heapifyDownn(int index) {
//    int leftChild, rightChild, smallest; // ������� ��� ������ � ������� �����, � ����� ��� �����������
//    // ���������, ���� �� ������� ��� ��������, ���� �� ����� ������� ����
//    while (index < heap.size()) {
//        leftChild = 2 * index + 1;  // ���������� ������� ������ �������
//        rightChild = 2 * index + 2; // ���������� ������� ������� �������
//        smallest = index; // �������������� smallest ������� ��������
//        // ������� ���������� ������� ����� �������� � ��� �����(��������� ����� ���������)
//        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
//            smallest = leftChild; // ��������� smallest, ���� ����� baby ������
//        }
//        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
//            smallest = rightChild; // ��������� smallest, ���� ������ baby ������
//        }
//        // ���� �������� ������ ��� ����� ����������� �� baby, ������� �� �������
//        if (smallest == index) return;
//        // ������ ������� ������� ������� � ���������� �� �����
//        swap(heap[index], heap[smallest]);
//        // ��������� � ����������� �������� ��� ���������� ��������
//        index = smallest;
//    }
//}

/// <summary>
    /// ��������������� ������� ��� "�������" ��������
    /// ��������� ��� ����������� ������� ������ ��������
    /// � ������ ������� � ��������� ���� true
    /// BigO
    /// ������:O(1)
    /// �������:O(log n)
    /// ������:O(log n)
    /// </summary>
    /// <param name="index">������� ��������</param>
//template<typename T>
//void heapifyUpp(int index) {
//    while (index > 0) {
//        int parentIndex = (index - 1) / 2;
//        //���� ������� ��� ������ ��������, �� �������
//        if (heap[index] >= heap[parentIndex]) return;
//        // ������ �������
//        swap(heap[index], heap[parentIndex]);
//        // ��������� � ��������
//        index = parentIndex;
//    }
//}


    /// <summary>
    /// ����� ��� �������� ������������ ��������
    /// ������:O(1)
    /// �������:O(1)
    /// ������:O(1)
    /// </summary>
    /// <returns>��������� ��� �������</returns>
//template<typename T>
//T extractMini() {
//    if (heap.empty()) throw std::runtime_error("Heap is empty.");
//    T minValue = heap[0]; // ��������� ����������� �������
//    heap[0] = heap.back(); // �������� ��� ��������� ���������
//    heap.pop_back(); // ������� ��������� �������
//    heapifyDown(0); // �������� ����� ������
//    return minValue; // ���������� ����������� �������
//}


/// <summary>
/// BigO
/// ������:O(1)
/// �������:O(n log n)
/// ������:O(n log n)
/// �������� ���������� � �������������� ����������� ���� (MinHeap) �� ������ � �����������
/// 
///  ������� ��������� ������ ����������� ���� heap.
/// ������ ������� �� ����������� ������� array ����������� � ���� 
/// � ������� ������ insert
/// ��������� ������ ������ sortedArray
///����� � �����, ���� ���� �� �����, ����������� ����������� �������� 
/// �� ����(����������� ������� ������ ��������� �� �������� ������)
///������ ����������� ������� ����������� � sortedArray
/// </summary>
/// <param name="array">������</param>
/// <returns>��������������� ������</returns>
template<typename T>
vector<T> heapSort(vector<T> array) {
    MinHeap<T> heap;
    for (const auto& item : array) {
        heap.insert(item); // ��������� ������ ������� � ����
    }
    vector<T> sortedArray;
    while (!heap.isEmpty()) {
        sortedArray.push_back(heap.extractMin()); // ��������� ����������� ��������
    }
    return sortedArray; // ���������� ��������������� ������
}

//
///// <summary>
///// ����� ������� � �����������, ������������� � �������������� ����������� ���� (MinHeap)
//  ������ ��������� ����� ����������� �������
///// </summary>
///// <typeparam name="T"></typeparam>
//template<typename T>
//class PriorityQueue {
//private:
//    MinHeap<T> minHeap; // ���������� MinHeap ��� �������� ���������
//
//public:
//
//    /// <summary>
//    /// ��������� ������� � ����
//    /// </summary>
//    /// <param name="value">�������� ��������</param>
//    void push(T value) {
//        minHeap.insert(value);
//    }
//
//    /// <summary>
//    /// ��������� ����������� �������
//    /// </summary>
//    /// <returns>����������� �������</returns>
//    T pop() {
//        return minHeap.extractMin();
//    }
//
//    /// <summary>
//    /// ���������� ����������� �������
//    /// </summary>
//    /// <returns>vbybvfkmysq 'ktvtyn</returns>
//    T top() const {
//        return minHeap.peek();
//    }
//
//    /// <summary>
//    /// �������� �� �������
//    /// </summary>
//    /// <returns> ��� ���� �����</returns>
//    bool isEmpty() const {
//        return minHeap.isEmpty();
//    }
//};
//
//


//template<typename T>
//void testMinHeap() {
//    MinHeap<int> heap;
//
//    // �������� ���������� ������������ �������� �� ������ ����
//    assert(heap.isEmpty() == true);
//
//    // �������� ���� ������������ �������� �� ������ ����
//    assert(heap.isEmpty() == true);
//
//    heap.insert(5);
//    heap.insert(3);
//    heap.insert(8);
//    heap.insert(1);
//    heap.insert(2);
//
//    // ��������, ��� ����������� ������� �������� ���������
//    assert(heap.peek() == 1);
//
//    // ���������� ������������ �������� � �������� ����
//    assert(heap.extractMin() == 1);
//    assert(heap.peek() == 2);
//
//    assert(heap.extractMin() == 2);
//    assert(heap.peek() == 3);
//
//    // �������� ���������� ��������
//    assert(heap.extractMin() == 3);
//    assert(heap.extractMin() == 5);
//    assert(heap.extractMin() == 8);
//    assert(heap.isEmpty() == true);
//
//
//    // �������� ���������� � ��������� ���� �� ������ ���� ����� ���������� ���� ���������
//    try {
//        heap.peek();
//        assert(false); // ���� �� ��������� ����������, ���� ��������
//    }
//    catch (const runtime_error& e) {
//        // ������� ���������� ��� ������� �������� ����������� ������� �� ������ ����
//    }
//
//    try {
//        heap.extractMin();
//        assert(false); // ���� �� ��������� ����������, ���� ��������
//    }
//    catch (const runtime_error& e) {
//        // ������� ���������� ��� ������� ������� ������� �� ������ ����
//    }
//
//}
//
//
//template<typename T>
//void testHeapifyMethods() {
//    MinHeap<int> heap;
//
//    heap.insert(8);
//    heap.insert(5);
//    heap.insert(3);
//    heap.insert(1);
//    heap.insert(2);
//
//    vector<int> expectedHeap = { 1, 2, 3, 8, 5 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // ��������� ������� (1)
//    heap.extractMin();
//    expectedHeap = { 2, 3, 5, 8 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // ������� ����� ������� (0)
//    heap.insert(0);
//    expectedHeap = { 0, 2, 3, 8, 5 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // ��������� ������� (0)
//    heap.extractMin();
//    expectedHeap = { 2, 3, 5, 8 };
//    assert(heap.getHeap() == expectedHeap);
//
//    // �������� �� ���������� ���� ���������
//    heap.extractMin(); // 2
//    heap.extractMin(); // 3
//    heap.extractMin(); // 5
//    heap.extractMin(); // 8
//
//    // ������ ���� ������ ���� ������
//    assert(heap.isEmpty() == true);
//
//    // �������� ���� ������������ �������� �� ������ ����
//    try {
//        heap.peek();
//        assert(false); // ���� ������ ����������, ���� ���������� �� ���������
//    }
//    catch (const std::runtime_error& e) {
//        // ������� ���������� ��� ������� �������� ����������� ������� �� ������ ����
//    }
//
//    // �������� ���������� ������������ �������� �� ������ ����
//    try {
//        heap.extractMin();
//        assert(false); // ���� ������ ����������, ���� ���������� �� ���������
//    }
//    catch (const std::runtime_error& e) {
//        // ������� ���������� ��� ������� ������� ������� �� ������ ����
//    }
//}
//
//}
//
//
//
//
//
//
//
//
//
//
//template<typename T>
//void heapsortT() {
//
//    //  ������ ������
//    vector<int> emptyarray = {};
//    assert(heapsort(emptyarray) == vector<int>{});
//
//    // ������ � ����� ���������
//    vector<int> singleelementarray = { 5 };
//    assert(heapsort(singleelementarray) == vector<int>{5});
//
//    // ������ ��� ������������
//    vector<int> sortedarray = { 1, 2, 3, 4, 5 };
//    assert(heapsort(sortedarray) == vector<int>{1, 2, 3, 4, 5});
//
//    // ������ ������������ � �������� �������
//    vector<int> reversesortedarray = { 5, 4, 3, 2, 1 };
//    assert(heapsort(reversesortedarray) == vector<int>{1, 2, 3, 4, 5});
//
//    // ������ � �������������� ����������
//    vector<int> arraywithduplicates = { 3, 1, 2, 1, 3 };
//    assert(heapsort(arraywithduplicates) == vector<int>{1, 1, 2, 3, 3});
//
//    // ��������� ��������
//    vector<int> mixedarray = { 9, -1, 3, 2, 0 };
//    assert(heapsort(mixedarray) == vector<int>{-1, 0, 2, 3, 9});
//}
////
////void testpriory() {
////    priorityqueue<int> pq;
////
////    assert(pq.isempty() == true);
////
////    pq.push(10);
////    pq.push(5);
////    pq.push(15);
////    pq.push(2);
////
////    // �������� �������� ��������
////    assert(pq.top() == 2); // ����������� ������� ������ ���� 2
////    assert(pq.isempty() == false); // ������� �� ������ ���� �����
////
////    assert(pq.pop() == 2);
////    assert(pq.top() == 5);
////
////    assert(pq.pop() == 5);
////    assert(pq.pop() == 10);
////    assert(pq.pop() == 15);
////    assert(pq.isempty() == true);
////
////}


template<typename T>
void testMinHeapIterator() {
    MinHeap<int> minHeap;

// �������� ��������� �� ������ ����
assert(minHeap.begin() == minHeap.end()); // �������� ������ ���� ����� ��������� end

// ������� ��������� � ����
minHeap.insert(5);
minHeap.insert(3);
minHeap.insert(8);
minHeap.insert(1);
minHeap.insert(2);

// �������� ��������� �� ����������� ����
vector<int> expectedValues = { 1, 2, 3, 5, 8 };
size_t index = 0;
for (auto it = minHeap.begin(); it != minHeap.end(); ++it) {
    assert(*it == expectedValues[index]); // �������� ������������ ��������
    index++;
}
assert(index == expectedValues.size()); // ��������, ��� ��� �������� ���� ���������

// �������� ���������� ������������ �������� � ��������� �������� ���������

assert(minHeap.extractMin() == 1); // ��������� 1
assert(minHeap.peek() == 2); // ������ ����������� ������� 2 ������ ���� �� �������

index = 0;
for (auto it = minHeap.begin(); it != minHeap.end(); ++it) {
    assert(*it == expectedValues[index + 1]); // ����������� 1 ���������
    index++;
}
assert(index == expectedValues.size() - 1); // ��������, ��� ��� �������� ���� ���������

// ���������� ���� ��������� � �������� �� ������ ����
assert(minHeap.extractMin() == 2);
assert(minHeap.extractMin() == 3);
assert(minHeap.extractMin() == 5);
assert(minHeap.extractMin() == 8);

// �������� �� ������ ���� ����� ����������
assert(minHeap.isEmpty() == true);

// �������� ��������� �� ������ ���� �����
assert(minHeap.begin() == minHeap.end()); // �������� ������ ���� ����� ��������� end

try {
    minHeap.peek(); // ������ ��������� ����������
    assert(false); // ���� ���������� ���, ���� ������ �����������
}
catch (const std::runtime_error&) {
    // ������� ����������
}

try {
    minHeap.extractMin(); // ������ ��������� ����������
    assert(false);
}
catch (const std::runtime_error&) {
}
}
