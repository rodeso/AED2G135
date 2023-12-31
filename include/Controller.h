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
#include <csignal>
#include <cmath>
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
    unordered_map<tuple<string, string>, vector<Airport>,AirportHash> cityHashTable;
    /// Data Structure for Airlines with Constant Look-up Time
    unordered_map<string, Airline> airlineHashTable;

    /// Simple HashTable Creation Method
    void addAirportToHashTable(const Airport& airport) {
        airportHashTable[airport.getCode()] = airport;
        tuple<string, string> key = make_tuple(airport.getCity(), airport.getCountry());
        cityHashTable[key].push_back(airport);
    }
    /// Simple HashTable Creation Method
    void addAirlineToHashTable(const Airline& airline) {
        airlineHashTable[airline.getCode()] = airline;
    }
    /// Simple Auxiliary Function for showFlights Function
    vector<Airport> BFSWithLayovers(const Airport& source, const Airport& destination, int maxLayovers);
    /// DFS Auxiliary Function for findLongestPath Function
    void findLongestPathDFS(Vertex<Airport>* currentVertex, vector<Airport>& currentRoute, int& maxStops, vector<Airport>& maxRoute);
    /// DFS Auxiliary for Articulation Points
    void ArticulationPointsDFS(Vertex<Airport>* currentVertex, set<Vertex<Airport>*>& articulationPoints, int& time, Vertex<Airport>* parent) const;
    /// DFS Auxiliary for Longest Trip
    void findLongestPathDFS(Vertex<Airport>* currentVertex, Airport destination, std::vector<Airport>& currentRoute, std::vector<std::pair<Airport, Airport>>& maxRoutePairs, int& maxStops);
    /// Dijkstra Algorithm
    void dijkstraShortestPaths(Vertex<Airport>* source, std::vector<vector<double>>& dist);
    size_t getCodeIndex(const std::string& code) const;
        /// Haversine Formula
    double haversine(double lat1, double lon1, double lat2, double lon2);
    /// Main Data Structure for the Program
    Graph<Airport> g;
public:
    /// Default Constructor
    Controller();
    /// Program's Centre Function
    ///  O(1)
    void displayMenu();
    /// Calculates the Total Airport Number
    ///  O(1)
    void numAirports();
    /// Calculates the Total Airline Number
    ///  O(1)
    void numAirlines();
    /// Calculates the Total Flight Number
    ///  O(1)
    void numFlights();
    /// Shows the Trip with the most Stops
    ///  O(V + E)
    void findLongestPath();
    /// Shows Top X Airports with Most Flights (InDegree+OutDegree)
    ///  O(V⋅E+V⋅log(V)+X)
    void topAirports();
    /// Shows Articulation Points, meaning Airports that when removed create unreachable destinations
    ///  O(V + E)
    void ArticulationPoints() const;
    /// Shows Longest Flight Path Pair
    ///  O(V^2)
    std::vector<std::pair<Airport, Airport>> findLongestShortestPathPairs();
    /// Calculates the Departing Flights Number from a given Airport
    ///  O(outgoing edges)
    void numDepartures(Airport a);
    /// Calculates the Arriving Flights Number to a given Airport
    ///  O(V * outgoing edges)
    void numArrivals(Airport a);
    /// Shows all Possible Destinations from a given Airport
    ///  O(outgoing edges)
    void showDestinations(Airport a);
    /// Shows all Possible Arrivals from a given Airport
    ///  O(V * outgoing edges)
    void showArrivals(Airport a);
    /// Shows the Possible Flights from a given Airport to a chosen Airport
    ///  O(V + E)
    void showFlightsTo(Airport a);
    /// Shows the Possible Flights from a chosen Airport to a given Airport
    ///  O(V + E)
    void showFlightsFrom(Airport a);
    /// Number of reachable destinations (airports, cities or countries) from a given airport in a maximum number of X stops (lay-overs)
    ///  O(V + E)
    void possibleDestinations(const Airport& chosenSource, int maxLayovers);
    /// Shows the Number of Flights a given Airline flies
    ///  O(N)
    void numAirlineFlights(Airline a);
    /// Shows the Number of Flights a given Airline flies from a chosen Airport
    ///  O(E)
    void numAirlineFlightsFrom(Airline a);
    /// Shows the Number of Flights a given Airline flies to a chosen Airport
    ///  O(V * E)
    void numAirlineFlightsTo(Airline a);
    /// Shows the Number of Flights a given Airline flies from a chosen Airport to a chosen Airport
    ///  O(V * E)
    void topAirportsDepartures(Airline a);
    /// Shows the Number of Flights a given Airline flies to a chosen Airport from a chosen Airport
    ///  O(V * E)
    void topAirportsArrivals(Airline a);
    /// Tells if Airline has Certain Flight
    ///  O(N)
    void hasFlight(Airline a);
    /// Shows the Distance between the two Airports of the Flight
    ///  O(1)
    void showDistance(Flight f);
    /// Finds the Closest Airport to a specified Location
    ///  O(V)
    Airport findClosest(double targetLat, double targetLon);
    /// Shows All Available Airlines for the Specified Route
    ///  O(V * E)
    void airlinesAvailable(const vector<Airport>& chosenRoute);
    /// Calculates the Total Distance of the Flights in the Route
    ///  O(N)
    void totalDistance(const vector<Airport>& chosenRoute);
    /// Simple Credits
    ///  O(1)
    void displayCredits();
};


#endif //AED2G135_CONTROLLER_H
