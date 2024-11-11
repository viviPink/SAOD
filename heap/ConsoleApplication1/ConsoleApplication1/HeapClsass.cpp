

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

#include "Heap.h"



int main() {
    std::vector<int> array = { 3, 1, 4, 1, 5, 9, 2, 6, 5 }; // Исходный массив
    std::vector<int> sortedArray = heapSort(array); // Сортировка с помощью кучи
    std::cout << "Sorted array: ";
    for (const auto& item : sortedArray) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    ///testMinHeap(); 
    ///testHeapifyMethods();

}
