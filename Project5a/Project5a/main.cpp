/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 5
*  Main function of Project 5
*  Developed using Visual Studio
*/

#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>

#include "d_except.h"
#include "maze.h"

//using namespace boost;
using namespace std;


//Mark all nodes in g as not visited
void clearVisited(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].visited = false;
    }
}

//Set all node weights to w
void setNodeWeights(Graph &g, int w) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].weight = w;
    }
}

//Unmark all nodes
void clearMarked(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].marked = false;
    }
}

//Output operator for the Graph class. Prints out all nodes and their
//properties, and all their edges and their properties
ostream &operator<<(ostream &ostr, const Graph &g) {
    int numEdge = 0, numVertex = 0;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    for (Graph::edge_iterator eItr = eItrRange.first;
    eItr != eItrRange.second; ++eItr) {
        numEdge++;
        ostr << "Edge: " << *eItr << endl;
        ostr << "Origin Vertex: " << source(*eItr, g) << endl;
        ostr << "Target Vertex: " << target(*eItr, g) << endl;
        ostr << "Weight: " << g[*eItr].weight << endl;
        ostr << "Visited: " << g[*eItr].visited << endl;
        ostr << "Marked: " << g[*eItr].marked << endl << endl;
    }
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        ostr << "Vertex: " << *vItr << endl;
        ostr << "Cell: (" << g[*vItr].cell.first << ", " <<
            g[*vItr].cell.second << ")" << endl;
        ostr << "Predecesor: " << g[*vItr].pred << endl;
        ostr << "Weight: " << g[*vItr].weight << endl;
        ostr << "Visited: " << g[*vItr].visited << endl;
        ostr << "Marked: " << g[*vItr].marked << endl << endl;
    }
    return ostr;
}
   
int main() {
   try {
      ifstream fin;

      // Read the maze from the file.
      string fileName = "maze-files/maze2.txt";
      
      fin.open(fileName.c_str());
      if (!fin) {
         cerr << "Cannot open " << fileName << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();
      
      m.print(m.numRows()-1,m.numCols()-1,0,0);

      Graph g;
      m.mapMazeToGraph(g);

      clearVisited(g);
      clearMarked(g);
      setNodeWeights(g, 1);

      cout << g;
   }
   catch (baseException & be) {
       cout << be.what() << endl;
       exit(1);
   }

   //Waits for the user to exit
   cout << "Press any key and enter to exit" << endl;
   string ending;
   cin >> ending;

   return 0;
}
