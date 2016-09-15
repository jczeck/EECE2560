/* HastTable.h
*  Jenna Czeck
*  EECE 2560 Project 3
*  Header file of the hash table template class
*/

#ifndef PROJECT3_HASH_TABLE_H_
#define PROJECT3_HASH_TABLE_H_

#include <vector>
#include <functional>

#include "d_except.h"

using namespace std;

template <typename T>
class HashTable {
public:
    HashTable<T>(); //Constructor
    void AddItem(T& item); //Adds item to the hash table
    void DeleteItem(T& item); //Deletes item from the hash table
    bool InList(T& item); //Returns if the item is in the list
    int Hash(T& item); //Gives the hash table index of item

    bool LookUpWord(T item); //Returns InList, for template function in main

private:
    vector<vector<T> > hashTable;
    int size;
};

#endif

//Constructor
//Size is chosen to be a prime number that handles about 3 collisions
//For the word list
template<typename T>
HashTable<T>::HashTable() :
size(30707) {
    hashTable = vector<vector<T> >(size); //Initialize hash table
}

//Adds item to the hash table
template<typename T>
void HashTable<T>::AddItem(T & item) {
    int hash = Hash(item); //Look up hash index
    hashTable.at(hash).push_back(item); //Push back item to hash index vector
}

//Delete item from table
template<typename T>
void HashTable<T>::DeleteItem(T & item) {
    int hash = Hash(item); //Look up hash index
    vector<T>& collisions = hashTable.at(hash); //Get hash index vector
    int colliSize = collisions.size(); //Declare the size of collisions vector
    int indItem = -1; //Declare index of the item in list

    //For each element in collisions check if it is the item
    for (int i = 0; i < colliSize; i++) {
        if (collisions.at(i) == item) {
            indItem = i; //If it is item, set indItem to i
        }
    }
    //If the item is in the list
    if (indItem != -1) {
        //If the item is not at the end of the vector, switch it to end
        if (indItem != colliSize - 1) {
            T temp = collisions.at(indItem);
            collisions.at(indItem) = collisions.at(colliSize);
            collisions.at(colliSize - 1) = temp;
        }
        collisions.pop_back(); //Pop back last element
    }
} //End DeleteItem

//Returns if the item is in the hash table
template<typename T>
bool HashTable<T>::InList(T & item) {
    int hash = Hash(item); //Look up hash index of item
    vector<T> & collisions = hashTable.at(hash); //Get the hash index vector

    //For each item in collisions
    for (T i : collisions) {
        if (i == item) {
            return true; //If it is the item, return true
        }
    }
    return false; //Else return false
} //End InList

template<typename T>
int HashTable<T>::Hash(T & item) {
    hash<T> h; //Initialize hash for T
    return h(item) % size; //Return the hash index
}

//Returns InList, for template function in main
template<typename T>
bool HashTable<T>::LookUpWord(T item) {
    return InList(item);
}
