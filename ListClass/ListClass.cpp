
#include <iostream>
#include <cassert>

#include "List_class.h" 

using namespace std;

int main()
{
	DoublyLinkedList<int> myList;
	myList.assertInsert();


    DoublyLinkedList<int> list;
    list.insert(0, 3);
    list.insert(1, 5);
    list.insert(2, 6);
    list.insert(3, 7);
    list.insert(4, 4);
    list.insert(5, 3);
    list.insert(6, 0);


    cout << list[1] << " ";
    cout << list.get(0) << " ";  
    cout << list.get(1) << " ";  
    cout << list.get(2) << " ";  
    cout << list.get(3) << " ";  
    cout << list.get(4) << " ";  
    cout << list.get(5) << " ";  
    cout << list.get(6) << " ";  
}

