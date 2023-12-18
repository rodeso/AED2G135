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
    unordered_map<string, Airport> airportHashTable;
    unordered_map<string, vector<Airport>> cityHashTable;
    unordered_map<string, Airline> airlineHashTable;
    void addAirportToHashTable(const Airport& airport) {
        airportHashTable[airport.getCode()] = airport;
        cityHashTable[airport.getCity()].push_back(airport);
    }
    void addAirlineToHashTable(const Airline& airline) {
        airlineHashTable[airline.getCode()] = airline;
    }
    Graph<Airport> g;
public:
    Controller();
    void displayMenu();
    void numAirports();
    void numAirlines();
    void numFlights();
    void displayCredits();
};


#endif //AED2G135_CONTROLLER_H
