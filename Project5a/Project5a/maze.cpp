/* maze.cpp
*  Jenna Czeck
*  EECE 2560 Project 5
*  Implimentation of the maze class
*/

#include "maze.h"

//Initializes a maze by reading values from fin.  Assumes that the
//number of rows and columns indicated in the file are correct
maze::maze(ifstream &fin) {
    fin >> rows;
    fin >> cols;

    char x;

    value.resize(rows, cols);
    for (int i = 0; i <= rows - 1; i++)
        for (int j = 0; j <= cols - 1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }

    vertices.resize(rows, cols);
}

//Print out a maze, with the goal and current cells marked on the board
void maze::print(int goalI, int goalJ, int currI, int currJ) {
    cout << endl;

    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");

    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");

    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else
                if (i == currI && j == currJ)
                    cout << "+";
                else
                    if (value[i][j])
                        cout << " ";
                    else
                        cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}


//Return the value stored at the (i,j) entry in the maze, indicating
//whether it is legal to go to cell (i,j).
bool maze::isLegal(int i, int j) {
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");

    return value[i][j];
}

//Create a graph g that represents the legal moves in the maze m
void maze::mapMazeToGraph(Graph &g) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (value[i][j]) {
                Graph::vertex_descriptor v = add_vertex(g);
                g[v].cell = pair<int, int>(i, j);
                vertices[i][j] = v;
                g[v].pred = 1;
                if (i != 0 && value[i - 1][j]) {
                    add_edge(vertices[i - 1][j], v, g);
                }
                if (j != 0 && value[i][j - 1]) {
                    add_edge(vertices[i][j - 1], v, g);
                }
            }
        }
    }
}

void maze::printPath(Graph::vertex_descriptor end,
    stack<Graph::vertex_descriptor> &s, Graph g) {

    Graph::vertex_descriptor currVertex;
    
    while (!s.empty()) {
        currVertex = s.top();
        s.pop();
        print(g[end].cell.first, g[end].cell.second, 
            g[currVertex].cell.first, g[currVertex].cell.second);
    }
}
