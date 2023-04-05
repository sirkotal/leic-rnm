#include "manager.h"

#define networkF "../data/network.csv"
#define stationF "../data/stations.csv"
#define grapViwerFile "../graph_viewer/graph.gv"
#define grapViwerMaxTrainFile "../graph_viewer/graph_maxTrain.gv"
#define grapViwerMaxArrivalTrainsAt "../graph_viewer/graph_MaxArrivalTrainsAt.gv"

Manager::Manager() {
    this->railway = new Graph();
    buildRailway(stationF);
    buildNetwork(networkF);
    buildGraphviz(grapViwerFile);
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


void Manager::buildGraphviz(const string& filename) {
    ofstream dotfile(filename);


    // Write the graph header
    dotfile << "digraph G {" << endl << "layout: neato;" << endl << endl;


    for(auto i : this->railway->getVertexSet())
    {
        for(auto j : i->getAdj())
        {
            dotfile << "\t\"" << j->getOrig()->getStation().getName() << "\" -> \"" << j->getDest()->getStation().getName() << "\" [label=\""
            << j->getService() << " (" << j->getWeight() << ")\"];\n";
        }
    }


    dotfile << "}";
    dotfile.close();
}

void Manager::buildGraphvizWithFlows(const string &filename) {
    ofstream dotfile(filename);


    // Write the graph header
    dotfile << "digraph G {" << endl << "layout: neato;" << endl << endl;


    for(auto i : this->railway->getVertexSet())
    {
        for(auto j : i->getAdj())
        {
            if(j->getFlow())
            dotfile << "\t\"" << j->getOrig()->getStation().getName() << "\" -> \"" << j->getDest()->getStation().getName() << "\" [label=\"Flow:"
                    << j->getFlow() << " | Cap:" << j->getWeight() << "\"," << " color=red,"
                                                                             << " penwidth=" << j->getFlow() << "];\n";
        }
    }


    dotfile << "}";
    dotfile.close();
}

void Manager::testing() {
    cout << railway->getNumVertex() << endl;
    cout << railway->getNumEdges() << endl;
    cout << railway->getVertexSet().at(507)->getStation().getName() << endl;
}

double Manager::maxTrains(const string source, const string destination) {
    double maxNumTrains = railway->edmondsKarp(source, destination);
    buildGraphvizWithFlows(grapViwerMaxTrainFile);
    return maxNumTrains;
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
    double maxArrivalNum = railway->maxArrivalTrains(dest);
    buildGraphvizWithFlows(grapViwerMaxArrivalTrainsAt);
    return maxArrivalNum;
}

int Manager::maxTrainsMinCost(const string &src, const string &dst) {
    vector<Vertex*> path;
    railway->dijkstra(src, path);
    /*for (auto element: path) {
        cout << element->getStation().getName() << ", ";
    }
    cout << endl;*/
    int cost = railway->findVertex(dst)->getDistance();
    cout << "|" << cost << "|" << endl;
    return cost * railway->findBottleneck(path);
}