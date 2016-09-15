/* Board.h
*  Jenna Czeck
*  EECE 2560 Project 4
*  Header file of the board class
*/

#ifndef PROJECT4_BOARD_H_
#define PROJECT4_BOARD_H_


#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int blank = -1;  // Indicates that a cell is blank

const int squareSize = 3;  //  The number of cells in a small square
                           //  (usually 3).  The board has
                           //  SquareSize^2 rows and SquareSize^2
                           //  columns.

const int boardSize = squareSize * squareSize;

const int minValue = 1;
const int maxValue = 9;

//int numSolutions = 0;

class Board
    // Stores the entire Sudoku board
{
public:
    Board(int sqSize); //Constructor
    void Clear(); //Clears the board
    void Initialize(ifstream &fin); //Initalizes the board with ifstream
    bool IsSolved(); //Returns if the board is solved
    void Print(); //Prints out the board
    void PrintConflicts(); //Prints out the conflicts

    bool IsBlank(int i, int j) const; //Returns if cell is blank
    ValueType GetCell(int i, int j) const; //Returns value of cell
    void SetCell(int i, int j, ValueType val); //Sets the cell to val
    void ClearCell(int i, int j); //Clears the cell

    //Would it cause conflict
    bool CausesConflict(int i, int j, ValueType val) const; 
    void AddConflict(int i, int j, ValueType val); //Add a conflict
    void RemoveConflict(int i, int j, ValueType val); //Remove conflict

private:

    // The following matrices go from 1 to BoardSize in each
    // dimension.  I.e. they are each (BoardSize+1) X (BoardSize+1)
    matrix<ValueType> value;
    matrix<bool> rowConflicts;
    matrix<bool> colConflicts;
    matrix<bool> sqConflicts;
};

#endif