/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 4
*  Main function of Project 4
*  Developed using Visual Studio
*/

#include <iostream>
#include <fstream>

#include "Board.h"

//Gives the next location to solve by finding location with least number of
//possible solutions
void NextLocation(const Board& board, int& i, int& j) {
    int possibleSolutions;
    
    //How many possible solutions we are looking for
    //Go through board looking for one first, then two...
    for (int n = 1; n <= 9; n++ ) {
        //Go through board
        for (int r = 1; r <= boardSize; r++) {
            for (int c = 1; c <= boardSize; c++) {
                //If that spot is black
                if (board.IsBlank(r, c)) {
                    possibleSolutions = 0; //Set possilbe to zero
                    //Go through each value and if there are no conflicts
                    //Incriment possible solutions
                    for (ValueType v = minValue; v <= maxValue; v++) {
                        if (!board.CausesConflict(r, c, v)) {
                            possibleSolutions++;
                        }
                    }
                    //If we have found the number of possible solutions we are
                    //looking for, set i and j and return
                    if (possibleSolutions <= n) {
                        i = r;
                        j = c;
                        return;
                    }
                } //End if IsBlank
            } //End c for loop
        } //End r for loop
    } //End n for loop
} //End NextLocation

//Recursively solve the board
//Return if board solved
bool SolveBoard(Board& board, int i, int j, int& numCalls) {
    numCalls++; //Incriment number of calls
    ValueType val = minValue; //Start val at minValue
    bool boardSolved = board.IsSolved(); //Set boardSolved to IsSolved

    //While value is below the max value and the board is not solved
    while (!boardSolved && val <= maxValue) {
        //If there is no conflict at location with val
        if (!board.CausesConflict(i, j, val)) {
            board.SetCell(i, j, val); //Set the cell
            //Find the next location
            int iNext = i, jNext = j;
            NextLocation(board, iNext, jNext);
            //Recursion for next location
            boardSolved = SolveBoard(board, iNext, jNext, numCalls);
            //If we didn't solve the board, backtrack and increment val
            if (!boardSolved) {
                board.ClearCell(i, j);
                val++;
            }
        //If the value causes a conflict, increment val
        } else {
            val++;
        }
    } //End while
    return boardSolved; 
} //End SolveBoard


int main() {
    ifstream fin;

    //Read the sample grid from the file.
    string fileName = "sudoku.txt";

    //Open file and check that it opened
    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }

    try {
        //Initialize variables
        Board b1(squareSize);
        int totalCalls = 0;
        int numBoards = 0;

        //For each board in file
        while (fin && fin.peek() != 'Z') {
            b1.Initialize(fin); //initalize board
            int i, j; //Initialize variables
            int numCalls = 0; //Set numCalls to zero
            NextLocation(b1, i, j); //Find starting location
            SolveBoard(b1, i, j, numCalls); //Solve the board
            totalCalls += numCalls; //Add the numCalls to totalCalls
            numBoards++; //Increment number of boards 
            b1.Print(); //Print solved board
            //Print number of calls for board
            cout << "Number of Calls: " << numCalls << endl;
        }
        //Print average number of calls
        cout << "Average Calls: " << totalCalls / numBoards << endl;
    }
    //Catch range errors
    catch (indexRangeError &ex) {
        cout << ex.what() << endl;
        cout << "Press any key and enter to exit" << endl;
        string end;
        cin >> end;
        exit(1);
    }

    //Waits for the user to exit
    cout << "Press any key and enter to exit" << endl;
    string exit;
    cin >> exit;
}