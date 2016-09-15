/* Grid.h
*  Jenna Czeck
*  EECE 2560 Project 3
*  Header file of the grid class
*/

#ifndef PROJECT3_GRID_H_
#define PROJECT3_GRID_H_

#include <fstream>

#include "d_matrix.h"

using namespace std;

class Grid {
public:
    Grid(); //Constuctor
    void ReadFile(string fileName); //Reads file of passed fileName
    int GetNumRows(); //Returns the number of rows
    int GetNumColumns(); //Returns the number of columns
    string GetCharacter(int r, int c); //Gets the character at the position
private:
    matrix<string> grid; //Matrix of all the characters
};

#endif