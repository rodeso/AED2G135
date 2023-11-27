//
// Created by Rodri_5 on 27/11/23.
//

#include "Graph.h"

using namespace std;

// Function to add a new airport to the graph
void Graph::addAirport(const std::string &airportCode) {
    airports[airportCode];  // Adding an empty set for connections
}

// Function to add a new flight to the graph
void Graph::addFlight(const string& sourceAirport, const string& destinationAirport, const string& airline) {
    flights[sourceAirport][destinationAirport].insert(airline);
    flights[destinationAirport][sourceAirport].insert(airline);  // Assuming flights are bidirectional
}

// Function to get the list of airports
vector<string> Graph::getAirports() const {
    vector<string> airportList;
    for (const auto& entry : airports) {
        airportList.push_back(entry.first);
    }
    return airportList;
}

// Function to get the list of destinations from a given airport
vector<string> Graph::getDestinations(const string& sourceAirport) const {
    vector<string> destinationList;
    auto it = airports.find(sourceAirport);
    if (it != airports.end()) {
        for (const auto& destination : it->second) {
            destinationList.push_back(destination);
        }
    }
    return destinationList;
}

// Function to get the list of airlines for a given flight
vector<string> Graph::getAirlines(const string& sourceAirport, const string& destinationAirport) const {
    vector<string> airlineList;
    auto it = flights.find(sourceAirport);
    if (it != flights.end()) {
        auto airlineIt = it->second.find(destinationAirport);
        if (airlineIt != it->second.end()) {
            for (const auto& airline : airlineIt->second) {
                airlineList.push_back(airline);
            }
        }
    }
    return airlineList;
}
