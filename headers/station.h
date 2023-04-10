#ifndef LEIC_RNM_STATION_H
#define LEIC_RNM_STATION_H

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Represents a station
 */
class Station {
public:
    Station(const string &name, const string &district, const string &municipality, const string &township, const string &line);

    /**
     * @brief Gets the station's name
     * @return The name of the station
     */
    string getName() const;

    /**
     * @brief Gets the station's district
     * @return The district of the station
     */
    string getDistrict() const;

    /**
     * @brief Gets the station's municipality
     * @return The municipality of the station
     */
    string getMunicipality() const;

    /**
     * @brief Gets the station's township
     * @return The township of the station
     */
    string getTownship() const;

    /**
     * @brief Gets the station's line
     * @return The line of the station
     */
    string getLine() const;

    /**
     * @brief Checks if two stations are the same
     * @param s2 The second station
     * @return True if they are the same station; otherwise, it returns false
     */
    bool operator==(const Station &s2) const;

private:
    /**
     * @brief The station's name
     */
    string name;

    /**
     * @brief The station's district
     */
    string district;

    /**
     * @brief The station's municipality
     */
    string municipality;

    /**
     * @brief The station's township
     */
    string township;

    /**
     * @brief The station's line
     */
    string line;
};

#endif //LEIC_RNM_STATION_H
