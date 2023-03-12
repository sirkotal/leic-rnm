#ifndef LEIC_RNM_STATION_H
#define LEIC_RNM_STATION_H

#include <bits/stdc++.h>

using namespace std;

class Station {
public:
    Station(const string &name, const string &district, const string &municipality, const string &township, const string &line);

    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;

    bool operator==(const Station &s2) const;

private:
    string name;
    string district;
    string municipality;
    string township;
    string line;
};

#endif //LEIC_RNM_STATION_H
