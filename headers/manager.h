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

private:
    Graph* railway;

    void buildGraphviz(const string &filename);

    void buildGraphvizWithFlows(const string &filename);
};

#endif
