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

/**
 * @brief Represents a station in the railway network
 */
class Vertex {
public:
    Vertex(const Station &station);

    std::vector<Edge *> getAdj() const;
    Station getStation() const;
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

    Vertex* getSRC();
    void setSRC(Vertex *v);

private:
    /**
     * @brief The vertex's station
     */
    Station station;
    //int id;                // identifier

    /**
     * @brief The vertex's adjacency list (outgoing edges)
     */
    std::vector<Edge *> adj;  // outgoing edges

    /**
     * @brief The vertex has been visited
     */
    bool visited = false; // used by DFS, BFS, Prim ...

    /**
     * @brief The vertex is being processed
     */
    bool processing = false; // used by isDAG (in addition to the visited attribute)

    /**
     * @brief The vertex's indegree
     */
    unsigned int indegree; // used by topsort

    /**
     * @brief The edge that travels to this vertex
     */
    Edge *path = nullptr;

    /**
     * @brief The vertex's incoming edges
     */
    std::vector<Edge *> incoming; // incoming edges

    /**
     * @brief The cost of reaching this vertex
     */
    int dist = INT_MAX;

    /**
     * @brief The previous vertex
     */
    Vertex* src = nullptr;
};

/********************** Edge  ****************************/

/**
 * @brief Represents the path between two stations in a railway network
 */
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
    /**
     * @brief The destination vertex
     */
    Vertex * dest; // destination vertex

    /**
     * @brief The edge's weight/capacity
     */
    double weight; // edge weight, can also be used for capacity

    /**
     * @brief The type of train service provided in the edge
     */
    string service;

    // used for bidirectional edges
    /**
     * @brief The origin vertex
     */
    Vertex *orig;

    /**
     * @brief The reverse edge
     */
    Edge *reverse = nullptr;

    /**
     * @brief The number of trains that are simultaneously in the edge
     */
    double flow; // for flow-related problems
};

#endif //LEIC_RNM_VERTEXEDGE_H
