/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 3
*  Main function of Project 3
*  Developed using Visual Studio
*/

#include <iostream>
#include <string>
#include <time.h>

#include "d_except.h"
#include "WordList.h"
#include "Grid.h"

//Finds the matches in the word list and grid
void FindMatches(WordList& list, Grid& grid) {
    //Declare Variables
    int maxLength = 15, minLength = 5; //Max and min lengths of words
    int l, row, col;
    string word;

    //For each element in the grid
    for (int r = 0; r < grid.GetNumRows(); r++) {
        for (int c = 0; c < grid.GetNumColumns(); c++) {

            //Search the North Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
            //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) { 
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (col == 0) {
                    col = grid.GetNumColumns() - 1;
                } else {
                    col--;
                }
            } //End North

            //Search the Northeast Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (col == 0) {
                    col = grid.GetNumColumns() - 1;
                } else {
                    col--;
                }
                if (row == grid.GetNumRows() - 1) {
                    row = 0;
                } else {
                    row++;
                }
            } //End Northeast

            //Search the East Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (row == grid.GetNumRows() - 1) {
                    row = 0;
                } else {
                    row++;
                }
            } //End East

            //Search the Southeast Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (col == grid.GetNumColumns() - 1) {
                    col == 0;
                } else {
                    col++;
                }
                if (row == grid.GetNumRows() - 1) {
                    row = 0;
                } else {
                    row++;
                }
            } //End Southeast

            //Search the South Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (col == grid.GetNumColumns() - 1) {
                    col = 0;
                } else {
                    col++;
                }
            } //End South

            //Search the Southwest Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (col == grid.GetNumColumns() - 1) {
                    col = 0;
                } else {
                    col++;
                }
                if (row == 0) {
                    row = grid.GetNumRows() - 1;
                } else {
                    row--;
                }
            } //End Southwest

            //Search the West Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (row == 0) {
                    row = grid.GetNumRows() - 1;
                } else {
                    row--;
                }
            } //End West

            //Search the Northwest Direction
            row = r, col = c; //Set row and col to current row and col
            word = ""; //Clear out the word
                       //Add up to the maxLength of characters
            for (l = 0; l <= maxLength; l++) {
                //Add on the current character
                word += grid.GetCharacter(row, col);
                //If the word length is greater or equal to the min length 
                if (word.length() >= minLength) {
                    //Look up the word and if it exists, print it out
                    if (list.LookUpWord(word)) {
                        cout << word << endl;
                    }
                }
                //If we are at the edge wrap, else iterate
                if (col == 0) {
                    col = grid.GetNumColumns() - 1;
                }
                else {
                    col--;
                }
                if (row == 0) {
                    row = grid.GetNumRows() - 1;
                } else {
                    row--;
                }
            } //End Northwest

        } //End col iterator
    } //End row interator
} //End Find Matches

//Searches the wordlist based on given algorithm
void Search(int algo) {
    //Declare variables
    string fileName;
    clock_t startTime, endTimeSort, endTimeSearch;
    int diffSort, diffSearch, diffTotal;

    //Create WordList and read it
    WordList list = WordList();
    list.ReadList();

    //Ask what grid file the user would like to use
    cout << "What grid file would you like to use?" << endl;
    cin >> fileName;

    //Create Grid and read given file
    Grid grid = Grid();
    grid.ReadFile(fileName);

    //Based on passed algorithm sort the list
    //Each algorithm sorts the list and times it
    switch (algo) {
    //Insertion Sort
    case(0) :
        cout << "Using Insertion Sort: " << endl;
        startTime = clock();
        list.InsertionSort();
        endTimeSort = clock();
        break;
    //Quick Sort
    case(1) :
        cout << "Using Quick Sort: " << endl;
        startTime = clock();
        list.QuickSort();
        endTimeSort = clock();
        break;
    //Merge Sort
    case(2) :
        cout << "Using Merge Sort: " << endl;
        startTime = clock();
        list.MergeSort();
        endTimeSort = clock();
        break;
    //Throw error if selection is not one of the choices
    default:
        throw rangeError("Sorting algorithm selected is not a choice");
    }

    //Call Find Matches
    FindMatches(list, grid);
    endTimeSearch = clock();

    //Print out timing information
    cout << "Start Time: " << startTime << endl;
    cout << "End Sort Time: " << endTimeSort << endl;
    diffSort = endTimeSort - startTime;
    cout << "CPU Cycles for Sort: ";
    cout << (float)diffSort / CLOCKS_PER_SEC << endl;
    cout << "End Search Time: " << endTimeSearch << endl;
    diffSearch = endTimeSearch - endTimeSort;
    cout << "CPU Cycles for Search: ";
    cout << (float)diffSearch / CLOCKS_PER_SEC << endl;
    diffTotal = endTimeSearch - startTime;
    cout << "Total CPU Cycles: ";
    cout << (float)diffTotal / CLOCKS_PER_SEC << endl;

} //End Search

int main(){   
    //Try the main function
    try {
        //Asks user for sorting algorithm selection and then performs Search
        //based on choice
        int sortSelection = 0;
        while (sortSelection != 3) {
            cout << "What sorting algorithm would you like to use?" << endl;
            cout << "Enter 0 for Insertion Sort" << endl;
            cout << "Enter 1 for Quick Sort" << endl;
            cout << "Enter 2 for Merge Sort" << endl;
            cout << "Enter 3 to Exit" << endl;
            cin >> sortSelection;
            if (sortSelection == 3) {
                break;
            }
            Search(sortSelection);
        }
        
    }
    //Catch file open error
    catch (const fileOpenError& foe) {
        cout << foe.what() << endl;
        exit(1);
    }
    //Catch range error
    catch (const rangeError& re) {
        cout << re.what() << endl;
        exit(1);
    }
    //Catch base exception
    catch (const baseException& be) {
        cout << be.what() << endl;
        exit(1);
    }


    //Waits for the user to exit
    cout << "Press any key and enter to exit" << endl;
    string exit;
    cin >> exit;

    return 0;
}