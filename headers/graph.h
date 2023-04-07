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

/**
 * @brief Represents the railway network
 */
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

    /**
     * @brief Tests if the destination vertex is visited and if there is remaining capacity in the edge
     * @param q The queue of visited vertexes
     * @param e The edge that leaves the source vertex
     * @param w The destination vertex
     * @param residual The residual capacity of the edge
     */
    inline void testAndVisit(std::queue<Vertex*> &q, Edge* e, Vertex* w, double residual);

    /**
     * @brief Finds the minimum flow in the path
     * @param s The source vertex
     * @param t The target vertex
     * @return The minimum flow in the given path
     */
    inline double findMinResidualAlongPath(Vertex* s, Vertex* t);

    /**
     * @brief Updates the flow in the path
     * @param s The source vertex
     * @param t The target vertex
     * @param f The minimum flow in the given path
     */
    inline void augmentFlowAlongPath(Vertex* s, Vertex* t, double f);

    /**
     * @brief Gets the pair(s) of stations that require the maximum amount of trains to travel between them
     * @return A vector with the pair(s) of stations with maximum flow between them
     */
    vector<pair<string,string>> maxTrainsPairs();

    /**
     * @brief Finds the municipalities with the most importance in the network in terms of flow centrality
     * @return A vector of municipalities sorted by flow centrality
     */
    vector<pair<string, double>> topFlowMunicipalities();

    /**
     * @brief Finds the districts with the most importance in the network in terms of flow centrality
     * @return A vector of districts sorted by flow centrality
     */
    vector<pair<string, double>> topFlowDistricts();

    /**
     * @brief Gets the maximum number of trains that can simultaneously arrive at a given station, using the entire railway network
     * @param dest The target station
     * @return The maximum number of trains that can arrive at the designated station simultaneously
     */
    double maxArrivalTrains(const string dest);

private:
    /**
     * @brief A vector containing all of the graph's vertexes
     */
    vector<Vertex*> vertexSet;    // vertex set

    /**
     * @brief Removes a vertex from the graph
     * @param target The vertex we want to remove
     * @return True if the vertex was successfully removed; if the vertex does not exist, it returns false
     */
    bool removeVertex(const string &target);
};

#endif

// Using the flow centrality, find the most important municipalities and districts in the network
// The sum of the maximum flow between all pairs of stations in the municipality/district
