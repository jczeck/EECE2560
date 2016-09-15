/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 6
*  Main function of Project 6
*  Developed using Visual Studio
*/

#include <iostream>
#include <fstream>
#include <stack>

#include <boost\graph\adjacency_list.hpp>

#include "d_except.h"
#include "heapV.h"

using namespace boost;
using namespace std;

int INFINTIY = 99999999;

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

//Mark all nodes in g as not visited
void clearVisited(Graph &g) {
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].visited = false;
    }
}

//Does dfs for a graph starting a v and only from v
void dfsSearch(Graph &g, Graph::vertex_descriptor v) {
    stack<Graph::vertex_descriptor> sVertices;
    sVertices.push(v);
    Graph::vertex_descriptor currV;

    while (!sVertices.empty()) {
        currV = sVertices.top();
        sVertices.pop();
        if (!g[currV].visited) {
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
}

//Returns true if there is a cycle accessible from v
bool dfsSearchCyclic(Graph &g, Graph::vertex_descriptor v) {
    stack<Graph::vertex_descriptor> sVertices;
    sVertices.push(v);
    Graph::vertex_descriptor currV;

    while (!sVertices.empty()) {
        currV = sVertices.top();
        sVertices.pop();
        if (!g[currV].visited) {
            g[currV].visited = true;
            pair<Graph::adjacency_iterator, Graph::adjacency_iterator>
                vItrRange = adjacent_vertices(currV, g);
            for (Graph::adjacency_iterator vItr = vItrRange.first;
            vItr != vItrRange.second; ++vItr) {
                if (*vItr == g[currV].pred) {}
                else if (g[*vItr].visited) {
                    return true;
                } else {
                    g[*vItr].pred = currV;
                    sVertices.push(*vItr);
                }
            }
        }
    }
    return false;
}

//Returns true if the graph is connected, otherwise returns false
bool isConnected(Graph &g) {
    clearVisited(g);
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    dfsSearch(g, *vItrRange.first);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
        if(!g[*vItr].visited)
            return false;
    }
    return true;
}

//Returns true if the graph contains a cycle, otherwise returns false
bool isCyclic(Graph &g) {
    clearVisited(g);
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
        if (!g[*vItr].visited) {
            if (dfsSearchCyclic(g, *vItr)) {
                return true;
            }
        }
    }
    return false;
}

//Returns the number of connected components in the graph
int numConnectedComponents(Graph &g) {
    int numConnected = 0;
    clearVisited(g);
    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr) {
        if (!g[*vItr].visited) {
            dfsSearch(g, *vItr);
            numConnected++;
        }
    }
    return numConnected;
}

//Returns the total cost of the graph
int totalCost(Graph &g) {
    int cost = 0;
    pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
    for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) {
        cost += g[*eItr].weight;
    }
    return cost / 2;
}

//Create a graph sf that contains a spanning forest on the graph g
void findSpanningForest(Graph &g1, Graph &sf) {

    sf = g1;
    if (!isCyclic(sf)) {
        return;
    }
    else {
        clearVisited(sf);
        pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g1);
        for (Graph::vertex_iterator vItr = vItrRange.first; 
        vItr != vItrRange.second; ++vItr) {
            if (!sf[*vItr].visited) {
                stack<Graph::vertex_descriptor> sVertices;
                sVertices.push(*vItr);
                Graph::vertex_descriptor currV;
                stack<Graph::vertex_descriptor> toRemove;

                while (!sVertices.empty()) {
                    currV = sVertices.top();
                    sVertices.pop();
                    if (!sf[currV].visited) {
                        sf[currV].visited = true;
                        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> uItrRange 
                            = adjacent_vertices(currV, sf);
                        for (Graph::adjacency_iterator uItr = uItrRange.first; uItr != uItrRange.second; ++uItr) {
                            if (*uItr == sf[currV].pred) {}
                            else if (sf[*uItr].visited) {
                                toRemove.push(*uItr);
                            }
                            else {
                                sf[*uItr].pred = currV;
                                sVertices.push(*uItr);
                            }
                        }
                        while (!toRemove.empty()) {
                            remove_edge(toRemove.top(), currV, sf);
                            remove_edge(currV, toRemove.top(), sf);
                            toRemove.pop();
                        }
                    }
                }
            }
        }
    }
}

//Finds the minimum spanning tree using Prim's algorithm
void msfPrim(Graph &g, Graph &sf) {
    heapV<Graph::vertex_descriptor, Graph> Q;

    pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
    for (Graph::vertex_iterator vItr = vItrRange.first;
    vItr != vItrRange.second; ++vItr) {
        g[*vItr].pred = -1;
        g[*vItr].weight = INFINTIY;
        Graph::vertex_descriptor newV = add_vertex(sf);
        sf[newV].marked = false;
        if (vItr == vItrRange.first) {
            g[*vItr].weight = 0;
        }
        Q.minHeapInsert(newV, g);
 
    }
    g[*vItrRange.first].weight = 0;
    
    while (Q.size() != 0) {
        Q.minHeapify(0, Q.size(), g); //Resort the heap
        Graph::vertex_descriptor u = Q.extractMinHeapMinimum(g);
        sf[u].marked = true;
        if (g[u].pred != -1) {
            pair<Graph::edge_descriptor, bool> newEdge =
                add_edge(u, g[u].pred, sf);
            sf[newEdge.first].weight = g[u].weight;
            pair<Graph::edge_descriptor, bool> newEdge2 =
                add_edge(g[u].pred, u, sf);
            sf[newEdge2.first].weight = g[u].weight;
        }
        pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = 
            adjacent_vertices(u, g);
        for (Graph::adjacency_iterator vItr = vItrRange.first;
        vItr != vItrRange.second; ++vItr) {
            pair<Graph::edge_descriptor, bool> e = edge(u, *vItr, g);
            int a = g[e.first].weight;
            int b = g[*vItr].weight;
            bool c = sf[*vItr].marked;
            if (!sf[*vItr].marked && g[e.first].weight < g[*vItr].weight) {
                g[*vItr].pred = u;
                g[*vItr].weight = g[e.first].weight;
            }
        }
    }
    
}

int main() {
    try {
        ifstream fin;
        string filename;

        cout << "What graph file would you like to use?" << endl;
        cin >> filename;

        // Read the maze from the file.
        filename = "graphs/" + filename;

        fin.open(filename.c_str());
        if (!fin) {
            cerr << "Cannot open " << filename << endl;
            exit(1);
        }

        Graph g, sf, msf;
        Graph::vertex_descriptor start;
        Graph::vertex_descriptor end;

        initializeGraph(g, start, end, fin);

        cout << "Is Connected: " << isConnected(g) << endl;
        cout << "Is Cyclic: " << isCyclic(g) << endl;
        findSpanningForest(g, sf);
        cout << "Spanning Forest" << endl;
        cout << "Total Cost: " << totalCost(sf) << endl;
        cout << "Number of Connected Components: " << numConnectedComponents(sf) << endl;
        cout << "Edges: " << endl;
        pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(sf);
        for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr) {
            cout << "From " << source(*eItr, sf) << " to " << target(*eItr, sf);
            cout << " Weight: " << sf[*eItr].weight << endl;
        }
        msfPrim(g, msf);
        cout << "Minimum Spanning Forest" << endl;
        cout << "Total Cost: " << totalCost(msf) << endl;
        cout << "Number of Connected Components: " << numConnectedComponents(msf) << endl;
        cout << "Edges: " << endl;
        pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange2 = edges(msf);
        for (Graph::edge_iterator eItr = eItrRange2.first; eItr != eItrRange2.second; ++eItr) {
            cout << "From " << source(*eItr, msf) << " to " << target(*eItr, msf);
            cout << " Weight: " << msf[*eItr].weight << endl;
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
