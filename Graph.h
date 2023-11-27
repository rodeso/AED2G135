//
// Created by Rodri_5 on 27/11/23.
//

#ifndef AED2G135_GRAPH_H
#define AED2G135_GRAPH_H


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
private:
    unordered_map<string, unordered_set<string>> airports;
    unordered_map<string, unordered_map<string, unordered_set<string>>> flights;

public:
    // Function to add a new airport to the graph
    void addAirport(const string& airportCode);// Adding an empty set for connections


    // Function to add a new flight to the graph
    void addFlight(const string& sourceAirport, const string& destinationAirport, const string& airline);

    // Function to get the list of airports
    vector<string> getAirports() const;

    // Function to get the list of destinations from a given airport
    vector<string> getDestinations(const string& sourceAirport) const;

    // Function to get the list of airlines for a given flight
    vector<string> getAirlines(const string& sourceAirport, const string& destinationAirport) const;
};

#endif //AED2G135_GRAPH_H
