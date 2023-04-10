#include "manager.h"

/*#define networkF "../data/network.csv"
#define stationF "../data/stations.csv"*/
#define grapViwerFile "../graph_viewer/graph.gv"
#define grapViwerMaxTrainFile "../graph_viewer/graph_maxTrain.gv"
#define grapViewerMaxReducted "../graph_viewer/graph_maxTrainWithReduced.gv"
#define grapViwerMaxArrivalTrainsAt "../graph_viewer/graph_MaxArrivalTrainsAt.gv"

Manager::Manager() {
    this->railway = new Graph();
    /*buildRailway(stationF);
    buildNetwork(networkF);*/
    buildGraphviz(grapViwerFile);
    this->reducedRailway = new Graph(*this->railway);
}

Manager::~Manager() {
    delete railway;
    delete reducedRailway;
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

void Manager::buildGraphvizWithFlowsSecondaryRailway(const string &filename) {
    ofstream dotfile(filename);


    // Write the graph header
    dotfile << "digraph G {" << endl << "layout: neato;" << endl << endl;


    for(auto i : this->reducedRailway->getVertexSet())
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

double Manager::maxTrains(const string &source, const string &destination) {
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
    railway->dijkstra(src, dst, path);
    /*for (auto element: path) {
        cout << element->getStation().getName() << ", ";
    }
    cout << endl;*/
    int cost = railway->findVertex(dst)->getDistance();
    //cout << "|" << cost << "|" << endl;
    return cost * railway->findBottleneck(path);
}

double Manager::maxTrainsWithReducedRailway(const string source, const string destination) {
    //this->reducedRailway = new Graph(*this->railway);
    //cout << reducedRailway->getNumVertex() << endl;
    //cout << reducedRailway->getNumEdges() << endl;
    vector<Vertex *> path;
    this->railway->edmondsKarp(source, destination);
    map<int, Edge *> vertexMap;
    int counter = 0;
    for(auto i : this->railway->getVertexSet())
    {
        for(auto j: i->getAdj())
        {
            if(j->getFlow())
            {
                vertexMap[counter] = j;
                counter++;
            }
        }
    }

    for(int i = 0;i< vertexMap.size(); i++){
        cout << i << ": FROM: " << vertexMap.at(i)->getOrig()->getStation().getName()  << " | TO: "<< vertexMap.at(i)->getDest()->getStation().getName() << endl;
    }

    int numLines;

    do{
        cout << "How many lines are interdict?";
        cin >> numLines;
    }
    while(numLines < 0 || numLines > vertexMap.size());

    cout << "Which connection(s) is/are interdict? (type the nr of the connection)" << endl;

    int numberPick;
    for(int i = 0; i < numLines; i++){
        do{
            cout << i << "- ";
            cin >> numberPick;
        }
        while(numberPick < 0 || numberPick > vertexMap.size());

        for(auto i : reducedRailway->getVertexSet())
        {
            if(i->getStation().operator==(vertexMap[numberPick]->getOrig()->getStation()))
            {
                i->removeEdge(vertexMap[numberPick]->getDest()->getStation().getName());
            }

            if(i->getStation().operator==(vertexMap[numberPick]->getDest()->getStation()))
            {
                i->removeEdge(vertexMap[numberPick]->getOrig()->getStation().getName());
            }
        }
    }

    double maxNumTrains = reducedRailway->edmondsKarp(source, destination);
    if(!maxNumTrains){
        cout << "We can't access" << destination << " from " << source << "with those line(s) interdict" << endl;
    }
    else
        buildGraphvizWithFlowsSecondaryRailway(grapViewerMaxReducted);
    return maxNumTrains;
}

bool compFunc(const pair<string, double> f, const pair<string, double> s) {
    return f.second > s.second;
}

void Manager::mostImpactedStations(int &k) {
    if (k > railway->getNumVertex() || k < 0) {
        cerr << "Invalid Input!" << endl;
        return;
    }
    vector<pair<string, double>> impact;
    for (auto v : railway->getVertexSet()) {
        double old_max = railway->maxArrivalTrains(v->getStation().getName());
        double new_max = reducedRailway->maxArrivalTrains(v->getStation().getName());
        impact.push_back(make_pair(v->getStation().getName(), old_max - new_max));
    }
    sort(impact.begin(), impact.end(), compFunc);

    for (int i = 0; i < k; i++) {
        if (impact[i].second == 0) {
            break;
        }
        cout << impact[i].first << " -> " << impact[i].second << endl;
    }

}