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

private:
    Graph* railway;
};

#endif
