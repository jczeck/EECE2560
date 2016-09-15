/* WordList.cpp
*  Jenna Czeck
*  EECE 2560 Project 3
*  Implimentation of the word list class
*/


#include "WordList.h"

//Default Constructor of WordList
WordList::WordList() {
}

void WordList::ReadList() {
    //Declare variables
    ifstream fin;
    string word;
    string fileName = "wordlist.txt";

    wordList.clear(); //Clear the word list

    fin.open(fileName.c_str()); //Open the wordlist.txt file
    //Check that it opened and if not throw error
    if (!fin) {
        throw fileOpenError("Unable to open wordlist.txt");
    }
    //For each line, push it into the wordlist
    while (getline(fin, word) ) {
        wordList.push_back(word);
    }
    fin.close(); //Close the file
} //End ReadList

//Insertion Sort of the wordlist
void WordList::InsertionSort() {
    //Declare variables
    int i, j;
    string key; 

    //Iterate over the list
    for (j = 1; j < (int)wordList.size(); j++) {
        key = wordList.at(j); //The item we are inserting
        i = j - 1; //The end of the sorted portion

        while (i >= 0 && wordList.at(i) > key) {
            //Pushes item to the right to add in the key
            wordList.at(i + 1) = wordList.at(i);
            i = i - 1;
            wordList.at(i + 1) = key;
        }
    }
} //End insertion sort

//Quicksort of the wordlist
void WordList::QuickSort() {
    QuickSort(0, wordList.size() - 1); //Calls QuickSort for the entire list
}

//Recursive function of quicksort
void WordList::QuickSort(int p, int r) {
    //As long as p is less than r
    if (p < r) {
        int q = Partition(p, r); //Partition the list
        QuickSort(p, q - 1); //Sort the left partition
        QuickSort(q + 1, r); //Sort the right partition
    }
}

//Partition function of QuickSort
int WordList::Partition(int p, int r) {
    string temp; //A temp variable
    string pivot = wordList.at(r); //Pivot point is last in the range
    int i = p - 1; //Declare i (size of left) one less than start of range

    //For each element in range
    for (int j = p; j < r; j++) {
        //If the element is less than the pivot
        if (wordList.at(j) <= pivot) {
            i++; //Increase the size of the left
            //Exchange wordList[i] with wordList[j]
            temp = wordList.at(i);
            wordList.at(i) = wordList.at(j);
            wordList.at(j) = temp;
        }
    }

    //Move the pivot to the middle of the list
    wordList.at(r) = wordList.at(i + 1);
    wordList.at(i + 1) = pivot;
    return i+1; //Return the pivot location
} //End Partition

//Merge sort of the wordlist
void WordList::MergeSort() {
    MergeSort(0, wordList.size() - 1); //Call merge sort for the whole list
}

//Recursive function of Merge Sort
void WordList::MergeSort(int p, int r) {
    int q; //Declare q
    //If p is less than r
    if (p < r) {
        q = (int)floor((p + r) / 2); //Find the center of portion
        //Sort each half
        MergeSort(p, q); 
        MergeSort(q + 1, r);
        Merge(p, q, r); //Merge the havles together
    }
}

//Merge function of merge sort
void WordList::Merge(int p, int q, int r) {
    //Declare variables
    vector<string> left, right;
    int i, j;
    //Where to end the new vectors
    int n1 = q - p + 1;
    int n2 = r - q;
    //Create new vectors
    left = vector<string>(n1+1);
    right = vector<string>(n2 + 1);
    for (i = 0; i < n1; i++) {
        left.at(i) = wordList.at(p + i);
    }
    left.at(n1) = "zzzzzzzzzzzzzzzzzzzzzzzzzz"; //End vector with large word
    for (j = 0; j < n2; j++) {
        right.at(j) = wordList.at(q + j + 1);
    }
    right.at(n2) = "zzzzzzzzzzzzzzzzzzzzzzzzz"; //End vector with large word
    //Start from zero
    i = 0;
    j = 0;
    //For the section to merge
    for (int k = p; k <= r; k++) {
        //Find the lower of the two in left and right and put that in list
        if (left.at(i) <= right.at(j)) {
            wordList.at(k) = left.at(i);
            i++;
        } else {
            wordList.at(k) = right.at(j);
            j++;
        }
    }
} //End Merge

//Binary sort of wordList, assumes list has been sorted
bool WordList::LookUpWord(string word) {
    //Declare variables
    int left, right, mid;
    left = 0;
    right = wordList.size() - 1;
    //While left is less than or equal than right
    while (left <= right) {
        mid = (left + right) / 2; //Find the mid point
        //If the word is the mid point return true
        if (wordList.at(mid) == word) { 
            return true;
        }
        //Else if the mid is less than the word, search right half
        else if (wordList.at(mid) < word) {
            left = mid + 1;
        } 
        //Else the mid is greater than the word, search left half
        else {
            right = mid - 1;
        }
    }
    return false; //Word is not in list
}

//Override of the print operator
ostream& operator<<(ostream& os, const WordList& list) {
    //For each word in the list, print it out
    for (string word : list.wordList) {
        os << word << endl;
    }
    return os;
}