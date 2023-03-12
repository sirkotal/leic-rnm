#ifndef LEIC_RNM_GRAPH_H
#define LEIC_RNM_GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "VertexEdge.h"

class Graph {
public:
    /*
    * Auxiliary function to find a vertex with a given ID.
    */
    Vertex *findVertex(const int &id) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    int getNumVertex() const;

    std::vector<Vertex*> getVertexSet() const;

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;
private:
    std::vector<Vertex*> vertexSet;    // vertex set
};

#endif
