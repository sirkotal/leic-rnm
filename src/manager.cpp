#include "manager.h"

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

            int cap = stoi(capacity);

            railway->addEdge(src, tar, cap, service);
        }
        thefile.close();
    }
    else
    {
        cout << "Error: The program was unable to open the file.";
    }
}
