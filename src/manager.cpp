#include "manager.h"

#define networkF "../data/network.csv"
#define stationF "../data/stations.csv"

Manager::Manager() {
    this->railway = new Graph();
    buildRailway(stationF);
    buildNetwork(networkF);
}

Manager::~Manager() {
    delete railway;
}

void Manager::buildRailway(const string& filename) {
    string name, district, municipality, township, line;

    ifstream thefile(filename);

    if (thefile.is_open())
    {
        string fline;
        getline(thefile, fline);

        while (!thefile.eof()) {
            getline(thefile, name, ',');
            getline(thefile, district, ',');
            getline(thefile, municipality, ',');
            getline(thefile, township, ',');
            getline(thefile, line, '\n');

            if (name.size() == 0) {
                continue;
            }

            railway->addVertex(Station(name, district, municipality, township, line));
        }
        thefile.close();
    }
    else
    {
        cout << "Error: The program was unable to open the file.";
    }
}

void Manager::buildNetwork(const string& filename) {
    string src, tar, capacity, service;

    ifstream thefile(filename);

    if (thefile.is_open())
    {
        string line;
        getline(thefile, line);

        while (!thefile.eof()) {
            getline(thefile, src, ',');
            getline(thefile, tar, ',');
            getline(thefile, capacity, ',');
            getline(thefile, service, '\n');

            double cap = stod(capacity);

            railway->addBidirectionalEdge(src, tar, cap/2, service);
        }
        thefile.close();
    }
    else
    {
        cout << "Error: The program was unable to open the file.";
    }
}

void Manager::testing() {
    cout << railway->getNumVertex() << endl;
    cout << railway->getNumEdges() << endl;
    cout << railway->getVertexSet().at(507)->getStation().getName() << endl;
}

double Manager::maxTrains(const string source, const string destination) {
    return railway->edmondsKarp(source, destination);
}

vector<pair<string,string>> Manager::maxCapacityTrainsPairs() {
    return railway->maxTrainsPairs();
}

void Manager::topFlowMunicipalities(int &k) {
    vector<pair<string, double>> vct = railway->topFlowMunicipalities();

    for (int i = 0; i < k; i++) {
        cout << vct[i].first << " -> " << vct[i].second << endl;
    }
}


double Manager::maxArrivalTrainsAtCertain(const string dest){
    return railway->maxArrivalTrains(dest);
}
