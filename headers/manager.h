#ifndef LEIC_RNM_MANAGER_H
#define LEIC_RNM_MANAGER_H

#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

class Manager {
public:
    Manager();
    ~Manager();

    void buildRailway(const string &filename);
    void buildNetwork(const string& filename);

    void testing();

    double maxTrains(const string source, const string destination);
    vector<pair<string,string>> maxCapacityTrainsPairs();
    void topFlowMunicipalities(int &k);

    double maxArrivalTrainsAtCertain(const string dest);

    int maxTrainsMinCost(const string &src, const string &dst);

    double maxTrainsWithReducedRailway(const string source, const string destination);

private:
    Graph* railway;
    Graph* reducedRailway;

    void buildGraphviz(const string &filename);

    void buildGraphvizWithFlows(const string &filename);

    void buildGraphvizWithFlowsSecondaryRailway(const string &filename);
};

#endif
