/* Heap.h
*  Jenna Czeck
*  EECE 2560 Project 3
*  Header file of the heap template class
*/

#ifndef PROJECT3_HEAP_H_
#define PROJECT3_HEAP_H_

#include <vector>

#include "d_except.h"

using namespace std;

template <typename T>
class Heap {
public:
    Heap<T>(); //Default Constructor
    int Parent(int i); //Returns index of parent
    int Left(int i); //Returns index of left child
    int Right(int i); //Returns index of right child
    T& GetItem(int n); //Gets the item at index n
    
    void InitializeMaxHeap(vector<T> list); //Takes list and creates max heap
    void BuildMaxHeap(int size); //Builds the max heap
    void MaxHeapify(int i, int size); //Makes max heap for below i
    void InitializeMinHeap(vector<T> list); //Takes list and creates min heap
    void BuildMinHeap(int size); //Builds the min heap
    void MinHeapify(int i, int size); //Makes min heap for below i

    void Heapsort(int size);
private:
    vector<T> heap;

    void SetItem(int n, T newItem); //Set the item at n with newItem
};

//Default Constructor
template<typename T>
Heap<T>::Heap() {
}

//Returns the parent of i
template<typename T>
int Heap<T>::Parent(int i) {
    return floor(i/2);
}

//Returns the left child of i
template<typename T>
int Heap<T>::Left(int i) {
    return 2*i;
}

//Returns the right child of i
template<typename T>
int Heap<T>::Right(int i) {
    return 2*i+1;
}

//Returns the item at n
template<typename T>
T & Heap<T>::GetItem(int n) {
    if (n > heap.size()) {
        throw rangeError("Index is outside of the heap");
    }
    return heap.at(n - 1); //Since we count from 1 but index from 0
}

//Set the item at n with a new item
template<typename T>
inline void Heap<T>::SetItem(int n, T newItem) {
    //Use n-1 since we count from 1 and index from 0
    heap.at(n - 1) = newItem;
}

//Takes in a list and makes a max heap out of it
template<typename T>
void Heap<T>::InitializeMaxHeap(vector<T> list) {
    heap.clear(); //Clear the heap and set list to heap
    heap = list; 
    BuildMaxHeap(heap.size()); //Call to BuildMaxHeap
}

//Builds a max heap with the heap vector
template<typename T>
void Heap<T>::BuildMaxHeap(int size) {
    //Goes through each element starting at the layer above the leaves
    for (int i = floor(size / 2); i > 0; i--) {
        MaxHeapify(i, size); //MaxHeapify each element
    }

}

//Makes a maxheap below element i
//Assumes the subtrees are maxheaps
template<typename T>
void Heap<T>::MaxHeapify(int i, int size) {
    //Declare variables
    int l, r, largest;
    T temp;
    
    //Get the left and right children
    l = Left(i);
    r = Right(i);

    //If the left child is larger, set as largest
    if (l < size && GetItem(l) > GetItem(i)) {
        largest = l;
    }
    //Else set i to largest
    else {
        largest = i;
    }
    //If the right child is larger than the largest, set as largest
    if (r <= size && GetItem(r) > GetItem(largest)) {
        largest = r;
    }
    //If i is not the largest switch it with the largest
    if (largest != i) {
        temp = GetItem(i);
        SetItem(i, GetItem(largest));
        SetItem(largest, temp);
        MaxHeapify(largest, size); //Float down the tree and heapify subtree
    }
} //End MaxHeapify

//Takes in a list and makes a min heap out of it
template<typename T>
void Heap<T>::InitializeMinHeap(vector<T> list) {
    heap = list;
    BuildMinHeap(heap.size());
}

//Builds a min heap with the heap vector
template<typename T>
void Heap<T>::BuildMinHeap(int size) {
    for (int i = floor(size / 2); i > 0; i--) {
        MinHeapify(i, size);
    }
}

//Makes a minheap below element i
//Assumes the subtrees are minheaps
template<typename T>
void Heap<T>::MinHeapify(int i, int size) {
    //Declare variables
    int l, r, smallest;
    T temp;

    //Get the left and right children
    l = Left(i);
    r = Right(i);

    //If the left child is smaller, set as smallest
    if (l < size && GetItem(l) < GetItem(i)) {
        smallest = l;
    }
    //Else set i to smallest
    else {
        smallest = i;
    }
    //If the right child is smaller than the smallest, set as smallest
    if (r <= size && GetItem(r) < GetItem(smallest)) {
        smallest = r;
    }
    //If i is not the smallest switch it with the smallest
    if (smallest != i) {
        temp = GetItem(i);
        SetItem(i, GetItem(smallest));
        SetItem(smallest, temp);
        MinHeapify(smallest, size); //Float down the tree and heapify subtree
    }
} //End MinHeapify

//Sorts the heap
//Assumes BuildMaxHeap has been called
template<typename T>
void Heap<T>::Heapsort(int size) {
    T temp; //Declare temp variable
    int heapSize = size; //Declare size of heap we are still looking at

    //For each element starting at the end and going until 2
    for (int i = size; i > 1; i--) {
        //Swap heap[1] with heap[i]
        temp = GetItem(i); 
        SetItem(i, GetItem(1));
        SetItem(1, temp);
        heapSize--; //Decriment heap size
        MaxHeapify(1, heapSize); //Make sure remaining heap is still a max heap
    }
} //End Heapsort


#endif
