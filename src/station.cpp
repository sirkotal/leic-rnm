#include "station.h"

Station::Station(const string &name, const string &district, const string &municipality, const string &township, const string &line) {
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

string Station::getName() const {
    return this->name;
}

string Station::getDistrict() const {
    return this->district;
}

string Station::getMunicipality() const {
    return this->municipality;
}

string Station::getTownship() const {
    return this->township;
}

string Station::getLine() const {
    return this->line;
}

bool Station::operator==(const Station &s2) const {
    return this->name == s2.name;
}
