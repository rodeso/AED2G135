#ifndef AED2G135_CONTROLLER_H
#define AED2G135_CONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <queue>
#include "../include/Graph.h"
#include "../include/Airline.h"
#include "../include/Airport.h"
#include "../include/Flight.h"
#include "../include/CSVParser.h"

using namespace std;

class Controller {
private:
    vector<Airport> airports;
    vector<Airline> airlines;
    vector<Flight> flights;
    Graph<Airport> g;
public:
    Controller();
    void displayMenu();
    void numAirports();
    void numAirlines();
    void displayCredits();
};


#endif //AED2G135_CONTROLLER_H
