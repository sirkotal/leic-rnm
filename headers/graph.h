#ifndef LEIC_RNM_GRAPH_H
#define LEIC_RNM_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
class Vertex;
#include "vertexedge.h"
#include "station.h"

using namespace std;

class Graph {
public:
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const string &id) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Station station);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const string &source, const string &dest, double w, const string &serv);
    bool addBidirectionalEdge(const string &source, const string &dest, double w, const string &serv);

    int getNumVertex() const;

    vector<Vertex*> getVertexSet() const;

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const string &id) const;
private:
    vector<Vertex*> vertexSet;    // vertex set
};

#endif
