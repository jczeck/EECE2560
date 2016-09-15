/* Grid.cpp
*  Jenna Czeck
*  EECE 2560 Project 3
*  Implimentation of the grid class
*/

#include "Grid.h"

//Default Constructor of Grid
Grid::Grid() :
    grid() {
}

//Reads the file with the passed fileName
void Grid::ReadFile(string fileName) {
    //Declare variables
    ifstream fin;
    string letter;
    int rows, cols;
    int r, c;
    string line;

    fin.open(fileName.c_str()); //Open the file
    //Check that the file was opened and if not throw an error
    if (!fin) {
        throw fileOpenError("Unable to open grid file");
    }
    //Get the number of rows and the number of columns
    getline(fin, line, ' ');
    rows = stoi(line);
    getline(fin, line);
    cols = stoi(line);
    grid.resize(rows, cols); //Resize the grid based on the read size

    //For each element of the matrix
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols - 1; c++) {
            //Get the next letter and place it in the grid
            getline(fin, letter, ' ');
            grid[r][c] = letter;
        }
        //Get the last letter of the line and place it in the grid
        getline(fin, letter);
        grid[r][c] = letter;
    }
    fin.close(); //Close the file
} //End ReadFile

//Returns the number of rows in the grid
int Grid::GetNumRows() {
    return grid.rows();
}

//Returns the number of columns in the grid
int Grid::GetNumColumns() {
    return grid.cols();
}

//Returns the character at the given location
string Grid::GetCharacter(int r, int c) {
    //Checks that the indexes are within the grid and if not throws error
    if (r > GetNumRows() || r < 0 || c > GetNumColumns() || c < 0) {
        throw rangeError("Character search outside of grid");
    }
    return grid[r][c];
}
