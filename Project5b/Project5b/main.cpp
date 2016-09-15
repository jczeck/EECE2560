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

//Clear Predecesors
void clearPred(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].pred = -1;
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

//Traverse function for recursive depth first search
bool traverseDFSRecursive(Graph& g, Graph::vertex_descriptor v,
    Graph::vertex_descriptor end, stack<Graph::vertex_descriptor>& path) {
    //Check if we are at the end
    if (v == end) {
        path.push(v);
        return true;
    }
    else {
        g[v].visited = true;
        bool found = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
            vItrRange = adjacent_vertices(v, g);
        for (Graph::adjacency_iterator vItr = vItrRange.first;
        vItr != vItrRange.second; ++vItr) {
            if (!g[*vItr].visited) {
                found = traverseDFSRecursive(g, *vItr, end, path);
            }
            if (found) break;
        }
        if (found) {
            path.push(v);
        }
        return found;
    }
}

//Depth First Search that is recursive
bool findPathDFSRecursive(Graph& g, Graph::vertex_descriptor start,
    Graph::vertex_descriptor end, stack<Graph::vertex_descriptor>& path) {
    clearVisited(g);
    return traverseDFSRecursive(g, start, end, path);
}

//Depth First Search that uses a stack
bool findPathDFSStack(Graph& g, Graph::vertex_descriptor start,
    Graph::vertex_descriptor end, stack<Graph::vertex_descriptor>& path) {
    clearVisited(g);
    bool found = false;
    stack<Graph::vertex_descriptor> sVertices;
    sVertices.push(start);
    Graph::vertex_descriptor currV;
    
    while (!sVertices.empty() && !found) {
        currV = sVertices.top();
        sVertices.pop();
        if (!g[currV].visited) {
            if (currV == end) {
                found = true;
            }
            g[currV].visited = true;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
                vItrRange = adjacent_vertices(currV, g);
            for (Graph::adjacency_iterator vItr = vItrRange.first;
            vItr != vItrRange.second; ++vItr) {
                if (!g[*vItr].visited) {
                    g[*vItr].pred = currV;
                    sVertices.push(*vItr);
                }
            }
        }
    }
    if (found) {
        while (currV != -1) {
            path.push(currV);
            currV = g[currV].pred;
        }
    }
    return found;
}

//Traverse function for recursive depth first search for shortest path
bool traverseDFSShortest(Graph& g, Graph::vertex_descriptor v,
    Graph::vertex_descriptor end, stack<Graph::vertex_descriptor>& path, 
    stack<Graph::vertex_descriptor>& tempPath) {

    tempPath.push(v);

    //Check if we are at the end
    if (v == end) {
        if (path.empty()) {
            path = tempPath;
        }
        else if (path.size() > tempPath.size()) {
            path = tempPath;
        }
        return true;
    }
    else {
        g[v].visited = true;
        bool found = false;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
            vItrRange = adjacent_vertices(v, g);
        for (Graph::adjacency_iterator vItr = vItrRange.first;
        vItr != vItrRange.second; ++vItr) {
            if (!g[*vItr].visited) {
                found = traverseDFSShortest(g, *vItr, end, path, tempPath);
                tempPath.pop();
            }
        }
        return found;
    }
}

//Find the shortest path using depth first search
bool findShortestPathDFS(Graph& g, Graph::vertex_descriptor start,
    Graph::vertex_descriptor end, stack<Graph::vertex_descriptor>& path) {
    clearVisited(g);
    stack<Graph::vertex_descriptor> tempPath;
    return traverseDFSShortest(g, start, end, path, tempPath);
}

//Finds the shortest path uses breadth first search
bool findShortestPathBFS(Graph& g, Graph::vertex_descriptor start,
    Graph::vertex_descriptor end, stack<Graph::vertex_descriptor>& path) {
    clearVisited(g);
    clearPred(g);
    bool found = false;

    queue<Graph::vertex_descriptor> qVertices;
    qVertices.push(start);
    Graph::vertex_descriptor currV;
    
    while (!qVertices.empty() && !found) {
        currV = qVertices.front();
        qVertices.pop();
        if (!g[currV].visited) {
            g[currV].visited = true;
            if (currV == end) {
                found = true;
            }
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
                vItrRange = adjacent_vertices(currV, g);
            for (Graph::adjacency_iterator vItr = vItrRange.first;
            vItr != vItrRange.second; ++vItr) {
                if (!g[*vItr].visited) {
                    g[*vItr].pred = currV;
                    qVertices.push(*vItr);
                }
            }
        }

    }
    if (found) {
        currV = end;
        while (currV != start) {
            path.push(currV);
            currV = g[currV].pred;
        }
        path.push(start);
    }
    return found;
}
   
int main() {
   try {
      ifstream fin;
      string filename;

      cout << "What maze file would you like to use?" << endl;
      cin >> filename;

      // Read the maze from the file.
      filename = "maze-files/" + filename;
      
      fin.open(filename.c_str());
      if (!fin) {
         cerr << "Cannot open " << filename << endl;
         exit(1);
      }

      maze m(fin);
      fin.close();

      Graph g;
      m.mapMazeToGraph(g);

      clearVisited(g);
      clearMarked(g);
      setNodeWeights(g, 1);
      
      Graph::vertex_descriptor start = m.getVertex(0, 0);
      Graph::vertex_descriptor end = m.getVertex(m.numRows()-1, m.numCols()-1);

      stack<Graph::vertex_descriptor> path1, path2, path3, path4;
      findPathDFSRecursive(g, start, end, path1);
      cout << "DFS Recursive, Path Size: " << path1.size() << endl;
      findPathDFSStack(g, start, end, path2);
      cout << "DFS Stack, Path Size: " << path2.size() << endl;
      findShortestPathDFS(g, start, end, path3);
      cout << "DFS Shortest, Path Size: " << path3.size() << endl;
      bool isSolution = findShortestPathBFS(g, start, end, path4);
      cout << "BFS Shortest, Path Size: " << path4.size() << endl;
      if (isSolution) {
          m.printPath(end, path4, g);
      } else {
          cout << "No path exists" << endl;
      }

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
