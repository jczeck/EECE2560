/* WordList.h
*  Jenna Czeck
*  EECE 2560 Project 3
*  Header file of the word list class
*/

#ifndef PROJECT3_WORD_LIST_H_
#define PROJECT3_WORD_LIST_H_

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "d_except.h"

using namespace std;

class WordList {
public:
    WordList(); //Constructor
    void ReadList(); //Reads the words from the wordlist.txt file
    void InsertionSort(); //Sorts the words using insertion sort
    void QuickSort(); //Sorts the words using quick sort
    void MergeSort(); //Sorts the words using merge sort

    bool LookUpWord(string word); //Looks up to see if a word exists in list

    //Override of print fuction
    friend ostream& operator<<(ostream& os, const WordList& list);
private:
    vector<string> wordList; //Wordlist stored in a vector

    void QuickSort(int p, int r); //Recurisive function of quicksort
    int Partition(int p, int r); //Partition function for quicksort

    void MergeSort(int p, int r); //Recursive function of merge sort
    void Merge(int p, int q, int r); //Merge function for merge sort
    
};

#endif