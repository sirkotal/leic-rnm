#ifndef LEIC_RNM_MANAGER_H
#define LEIC_RNM_MANAGER_H

#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

/**
 * @brief Represents the interface between the menu and the graph
 */
class Manager {
public:
    Manager();
    ~Manager();

    /**
     * @brief Builds a graph containing the railway's train stations
     * @param filename The name of the file containing the train stations' data
     */
    void buildRailway(const string &filename);

    /**
     * @brief Builds a graph containing the railway's connections
     * @param filename The name of the file containing the railway connections' data
     */
    void buildNetwork(const string& filename);

    /**
     * @brief Creates a copy of the network's graph
     */
    void createReducedGraph();

    /**
     * @brief Tests if the graph was successfully created (not meant for the end user)
     */
    void testing();

    /**
     * @brief Finds the maximum flow between a source and a destination vertex using the Edmonds-Karp algorithm
     * @details Complexity: O(|V||E|²)
     * @param source The source station
     * @param destination The target station
     * @return The maximum number of trains that can simultaneously travel between a source station and a target station
     */
    double maxTrains(const string &source, const string &destination);

    /**
     * @brief Gets the pair(s) of stations that require the maximum amount of trains to travel between them
     * @details Complexity: O(|E|²|V|³)
     * @return A vector with the pair(s) of stations with maximum flow between them
     */
    vector<pair<string,string>> maxCapacityTrainsPairs();

    /**
     * @brief Finds the top-k municipalities with the most importance in the network in terms of flow centrality
     * @details Complexity: O(|E|²|V|³)
     * @param k The number of municipalities to be displayed
     */
    void topFlowMunicipalities(int &k);

    /**
     * @brief Finds the top-k districts with the most importance in the network in terms of flow centrality
     * @details Complexity: O(|E|²|V|³)
     * @param k The number of districts to be displayed
     */
    void topFlowDistricts(int &k);

    /**
     * @brief Gets the maximum number of trains that can simultaneously arrive at a given station, using the entire railway network
     * @details Complexity: O(|V||E|²)
     * @param dest The target station
     * @return The maximum number of trains that can arrive at the designated station simultaneously
     */
    double maxArrivalTrainsAtCertain(const string dest);

    /**
     * @brief Gets the minimum cost of operating the maximum number of trains possible between two stations
     * @details Complexity: O(|E|+|V|log(|V|))
     * @param src The source station
     * @param dst The destination station
     * @return The maximum number of trains that can simultaneously travel between the two stations' minimum cost path
     */
    int maxTrainsMinCost(const string &src, const string &dst);

    /**
     * @brief Gets the maximum number of trains that can simultaneously travel between two stations in a network of reduced connectivity
     * @details Complexity: O(|V||E|²)
     * @param source The source station
     * @param destination The destination station
     * @return The maximum number of trains that can simultaneously travel between the two stations
     */
    double maxTrainsWithReducedRailway(const string source, const string destination);

    /**
     * @brief Gets the top-k most affected stations in terms of flow for a set of segment failures
     * @details Complexity: O(|V|²|E|²)
     * @param k The number of stations to be displayed
     */
    void mostImpactedStations(int &k);

private:
    /**
     * @brief The network's graph
     */
    Graph* railway;

    /**
     * @brief The network's reduced graph
     */
    Graph* reducedRailway;

    /**
     * @brief Creates a visual representation of the network's graph
     * @param filename The name of the file
     */
    void buildGraphviz(const string &filename);

    /**
     * @brief Creates a visual representation of the network's graph with flow display
     * @param filename The name of the file
     */
    void buildGraphvizWithFlows(const string &filename);

    /**
     * @brief Creates a visual representation of the network's reduced graph
     * @param filename The name of the file
     */
    void buildGraphvizWithFlowsSecondaryRailway(const string &filename);
};

#endif
