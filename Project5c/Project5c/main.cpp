/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 5
*  Main function of Project 5
*  Developed using Visual Studio
*/

#include <iostream>
#include <fstream>

#include <boost\graph\adjacency_list.hpp>

#include "heapV.h"
#include "d_except.h"

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

struct VertexProperties
{
    pair<int, int> cell; // maze cell (x,y) value
    Graph::vertex_descriptor pred; // predecessor node
    int weight;
    bool visited;
    bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
    int weight;
    bool visited;
    bool marked;
};

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;



void initializeGraph(Graph &g,
    Graph::vertex_descriptor &start,
    Graph::vertex_descriptor &end, ifstream &fin)
    // Initialize g using data from fin.  Set start and end equal
    // to the start and end nodes.
{
    EdgeProperties e;

    int n, i, j;
    int startId, endId;
    fin >> n;
    fin >> startId >> endId;
    Graph::vertex_descriptor v;

    // Add nodes.
    for (int i = 0; i < n; i++)
    {
        v = add_vertex(g);
        if (i == startId)
            start = v;
        if (i == endId)
            end = v;
    }

    while (fin.peek() != '.')
    {
        fin >> i >> j >> e.weight;
        pair<Graph::edge_descriptor, bool> checkEdge = edge(i, j, g);
        if (!checkEdge.second) {
            add_edge(i, j, e, g);
        }
    }
}

void initSingleSource(Graph &g, Graph::vertex_descriptor s) {
    int infinity = 9999999999;
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; 
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].weight = infinity;
        g[*vItr].pred = -1;
    }
    g[s].weight = 0;
}

void relax(Graph &g, Graph::vertex_descriptor u, Graph::vertex_descriptor v) {
    pair<Graph::edge_descriptor, bool> e = edge(u, v, g);
    if (g[v].weight > g[u].weight + g[e.first].weight) {
        g[v].weight = g[u].weight + g[e.first].weight;
        g[v].pred = u;
    }
}

//Dijkstra Algorithm
bool dijkstra(Graph &g, Graph::vertex_descriptor s) {
    initSingleSource(g, s);
    heapV<Graph::vertex_descriptor, Graph> Q;
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        Q.minHeapInsert(*vItr, g);
    }
    while (Q.size() != 0) {
        Graph::vertex_descriptor u = Q.extractMinHeapMinimum(g);
        g[u].visited = true;
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
            uItrRange = adjacent_vertices(u, g);
        for (Graph::adjacency_iterator uItr = uItrRange.first; uItr != uItrRange.second; ++uItr) {
            pair<Graph::edge_descriptor, bool> e = edge(u, *uItr, g);
            if (g[e.first].weight < 0) {
                return false;
            }
            relax(g, u, *uItr);
        }
    }
    return true;
}


//Bellman Ford Algorithm
bool bellmanFord(Graph &g, Graph::vertex_descriptor s) {
    initSingleSource(g, s);
    for (int i = 1; i < num_vertices(g) - 1; i++) {
        pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
        for (Graph::edge_iterator eItr = eItrRange.first;
        eItr != eItrRange.second; ++eItr) {
            relax(g, source(*eItr, g), target(*eItr, g));
        }
    }
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    for (Graph::edge_iterator eItr = eItrRange.first;
    eItr != eItrRange.second; ++eItr) {
        if (g[target(*eItr, g)].weight > g[source(*eItr, g)].weight + g[*eItr].weight) {
            return false;
        }
    }
    return true;
}

int main() {
    try {
        ifstream fin;
        string filename;

        cout << "What graph file would you like to use?" << endl;
        cin >> filename;

        // Read the maze from the file.
        filename = "graph/" + filename;

        fin.open(filename.c_str());
        if (!fin) {
            cerr << "Cannot open " << filename << endl;
            exit(1);
        }

        Graph g;
        Graph::vertex_descriptor start;
        Graph::vertex_descriptor end;

        initializeGraph(g, start, end, fin);
        
        cout << "Bellman Ford" << endl;
        bool bf = bellmanFord(g, start);
        vector<Graph::vertex_descriptor> path;
        if (bf) {
            Graph::vertex_descriptor currVertex = end;
            while (currVertex != -1 && currVertex != start) {
                path.push_back(currVertex);
                currVertex = g[currVertex].pred;
            }
            if(currVertex == start) {
                path.push_back(currVertex);
                for (Graph::vertex_descriptor v : path) {
                    cout << v << endl;
                }
            }
            else {
                cout << "End vertex not reachable from start" << endl;
            }
        }
        else {
            cout << "Negative Cycle Reached" << endl;
        }

        cout << endl << "Dijkstra:" << endl;
        bool d = dijkstra(g, start);
        vector<Graph::vertex_descriptor> dPath;
        Graph::vertex_descriptor currVertex2 = end;
        if (d) {
            while (currVertex2 != -1 && currVertex2 != start) {
                dPath.push_back(currVertex2);
                currVertex2 = g[currVertex2].pred;
            }
            if (currVertex2 == start) {
                dPath.push_back(currVertex2);
                for (Graph::vertex_descriptor v : dPath) {
                    cout << v << endl;
                }
            }
            else {
                cout << "End vertex not reachable from start" << endl;
            }
        }
        else {
            cout << "Negative links, cannot analyze" << endl;
        }
    }
    catch (baseException & be) {
        cout << be.what() << endl;
        exit(1);
    }

    //Waits for the user to exit
    cout << endl << "Press any key and enter to exit" << endl;
    string ending;
    cin >> ending;

    return 0;
}
