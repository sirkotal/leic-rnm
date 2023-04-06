#ifndef LEIC_RNM_GRAPH_H
#define LEIC_RNM_GRAPH_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
class Vertex;
#include "vertexedge.h"
#include "station.h"

using namespace std;

class Graph {
public:
    /**
     * @brief Finds a vertex in the graph with the given id
     * @param id The vertex's id
     * @return The vertex with the specified id; if it doesn't exist, it returns nullptr
     */
    Vertex *findVertex(const string &id) const;

    /**
     * @brief Adds a vertex representing a specific train station to the graph
     * @param station The train station the vertex represents
     * @return True if the vertex was successfully added; if the vertex already exists, it returns false
     */
    bool addVertex(const Station &station);

    /**
     * @brief Adds an edge between to vertexes of a graph
     * @param source The id of the source vertex
     * @param dest The id of the destination vertex
     * @param w The capacity of the edge
     * @param serv The service provided in the edge
     * @return True if the edge was successfully added; if the source or destination vertex does not exist, it returns false
     */
    bool addEdge(const string &source, const string &dest, double w, const string &serv);

    /**
     * @brief Adds two edges: one from a source to a destination vertex and another one in the opposite direction
     * @param source The id of the source vertex
     * @param dest The id of the destination vertex
     * @param w The capacity of the edge
     * @param serv The service provided in the edge
     * @return True if the edges were successfully added; if the source or destination vertex does not exist, it returns false
     */
    bool addBidirectionalEdge(const string &source, const string &dest, double w, const string &serv);

    /**
     * @brief Gets the graph's number of vertexes
     * @return The number of vertexes in the graph
     */
    int getNumVertex() const;

    /**
     * @brief Gets the graph's number of edges
     * @return The number of edges in the graph
     */
    int getNumEdges() const;

    /**
     * @brief Gets the graph's vertexes
     * @return A vector with all of the graph's vertexes
     */
    vector<Vertex*> getVertexSet() const;

    /**
     * @brief Finds the index of the vertex with a given id
     * @param id The vertex's id
     * @return The vertex's index
     */
    int findVertexIdx(const string &id) const;

    /**
     * @brief Finds the maximum flow between a source and a destination vertex using the Edmonds-Karp algorithm
     * @param source The source station
     * @param target The target station
     * @return The maximum number of trains that can simultaneously travel between a source station and a target station.
     */
    double edmondsKarp(const string source, const string target);

    /**
     * @brief Finds the minimum cost path between a source and a destination vertex using a modified Dijkstra algorithm
     * @param source The source station
     * @param target The target station
     * @param path The vector that stores the minimum cost path between the source and the destination
     */
    void dijkstra(const string &source, const string &target, vector<Vertex*> &path);

    /**
     * @brief Finds the bottleneck in a specific vertex path
     * @param path The vertex path
     * @return The bottleneck of the given path
     */
    double findBottleneck(vector<Vertex*> &path);

    /**
     * @brief Finds an augmenting path in the graph using a breadth-first search
     * @param s The source vertex
     * @param t The target vertex
     * @return True if an augmenting path is found; otherwise, it returns false
     */
    inline bool findAugmentingPath(Vertex* s, Vertex* t);


    inline void testAndVisit(std::queue<Vertex*> &q, Edge* e, Vertex* w, double residual);
    inline double findMinResidualAlongPath(Vertex* s, Vertex* t);
    inline void augmentFlowAlongPath(Vertex* s, Vertex* t, double f);

    vector<pair<string,string>> maxTrainsPairs();
    vector<pair<string, double>> topFlowMunicipalities();
    vector<pair<string, double>> topFlowDistricts();


    /*
    * Calculate the max trains that can arrive at a certain destination, using all the network
    */
    double maxArrivalTrains(const string dest);

private:
    vector<Vertex*> vertexSet;    // vertex set
    bool removeVertex(const string &target);
};

#endif
