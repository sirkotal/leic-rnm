#ifndef LEIC_RNM_VERTEXEDGE_H
#define LEIC_RNM_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "station.h"

class Edge;

/************************* Vertex  **************************/

class Vertex {
public:
    Vertex(const Station &station);

    std::vector<Edge *> getAdj() const;
    Station getStation();
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;
    int getDistance() const;

    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setPath(Edge *path);
    void setDistance(int num);
    Edge * addEdge(Vertex *dest, double w, const string &service);
    bool removeEdge(string destID);

    bool operator()(const Vertex* s, const Vertex* t) const;

private:
    Station station;
    //int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges

    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    Edge *path = nullptr;
    std::vector<Edge *> incoming; // incoming edges
    int dist = 0;
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w, const string &service);

    Vertex * getDest() const;
    double getWeight() const;
    Vertex * getOrig() const;
    string getService() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
private:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    string service;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

#endif //LEIC_RNM_VERTEXEDGE_H
