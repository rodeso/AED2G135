/*! \mainpage Main Page
 * - **Project name:** AED2G135 - Yet Another AirRoute Navigator (YAARN)
 * - **Short description:** Console-based Air Travel Flight Management System
 * - **Environment:** Unix/Windows console
 * - **Tools:** C++
 * - **Institution:** [FEUP](https://sigarra.up.pt/feup/en/web_page.Inicial)
 * - **Course:** [AED](https://sigarra.up.pt/feup/pt/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=520316) (Algorithms and Data Structures)
 * - **Project grade:** TBD
 * - **Group members:**
 *   - Álvaro Tomas Teixeira Silva Pacheco (up202207733@up.pt)
 *   - André Pinto de Sousa (up202109775@up.pt)
 *   - Rodrigo Dias Ferreira Loureiro de Sousa (up202205751@up.pt)
 *
 */



#ifndef AED2G135_CONTROLLER_H
#define AED2G135_CONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
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
    /// Initial Data Structure for Data in airports.csv
    vector<Airport> airports;
    /// Initial Data Structure for Data in airports.csv
    vector<Airline> airlines;
    /// Initial Data Structure for Data in flights.csv
    vector<Flight> flights;
    /// Data Structure for Airports with Constant Look-up Time
    unordered_map<string, Airport> airportHashTable;
    /// Data Structure for Cities with Constant Look-up Time
    unordered_map<string, vector<Airport>> cityHashTable;
    /// Data Structure for Airlines with Constant Look-up Time
    unordered_map<string, Airline> airlineHashTable;

    /// Simple HashTable Creation Method
    void addAirportToHashTable(const Airport& airport) {
        airportHashTable[airport.getCode()] = airport;
        cityHashTable[airport.getCity()].push_back(airport);
    }
    /// Simple HashTable Creation Method
    void addAirlineToHashTable(const Airline& airline) {
        airlineHashTable[airline.getCode()] = airline;
    }
    /// Simple Auxiliary Function for showFlights Function
    void BFSWithLayovers(const Airport& source, const Airport& destination, int maxLayovers);
    /// Main Data Structure for the Program
    Graph<Airport> g;
public:
    /// Default Constructor
    Controller();
    /// Program's Centre Function
    void displayMenu();
    /// Calculates the Total Airport Number
    void numAirports();
    /// Calculates the Total Airline Number
    void numAirlines();
    /// Calculates the Total Flight Number
    void numFlights();
    /// Calculates the Departing Flights Number from a given Airport
    void numDepartures(Airport a);
    /// Calculates the Arriving Flights Number to a given Airport
    void numArrivals(Airport a);
    /// Shows all Possible Destinations from a given Airport
    void showDestinations(Airport a);
    /// Shows the Possible Flights from a given Airport to a chosen Airport
    void showFlights(Airport a);
    /// Shows the Number of Flights a given Airline flies
    void numAirlineFlights(Airline a);
    /// Simple Credits
    void displayCredits();
};


#endif //AED2G135_CONTROLLER_H
