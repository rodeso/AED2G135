#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <queue>
#include "Graph.h"

using namespace std;
// Assume you have a Graph class provided in your practical classes

// Function to read and parse the dataset
void readAndParseData(Graph& flightGraph) {
    // Read airports data
    ifstream airportsFile("../airports.csv");
    if (!airportsFile.is_open()) {
        cerr << "Error opening airports file." << endl;
        return;
    }

    string airportLine;
    getline(airportsFile, airportLine); // Skip header line
    while (getline(airportsFile, airportLine)) {
        stringstream ss(airportLine);
        string code, name, city, country;
        double latitude, longitude;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        ss >> latitude;
        ss.ignore(); // Ignore the comma
        ss >> longitude;

        flightGraph.addAirport(code);
        // You can store additional information about airports if needed
    }

    airportsFile.close();

    // Read airlines data
    ifstream airlinesFile("../airlines.csv");
    if (!airlinesFile.is_open()) {
        cerr << "Error opening airlines file." << endl;
        return;
    }

    string airlineLine;
    getline(airlinesFile, airlineLine); // Skip header line
    while (getline(airlinesFile, airlineLine)) {
        stringstream ss(airlineLine);
        string code, name, callsign, country;

        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country, ',');

        // You can store additional information about airlines if needed
    }

    airlinesFile.close();

    // Read flights data
    ifstream flightsFile("../flights.csv");
    if (!flightsFile.is_open()) {
        cerr << "Error opening flights file." << endl;
        return;
    }

    string flightLine;
    getline(flightsFile, flightLine); // Skip header line
    while (getline(flightsFile, flightLine)) {
        stringstream ss(flightLine);
        string source, target, airline;

        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, ',');

        flightGraph.addAirport(source);
        flightGraph.addAirport(target);
        flightGraph.addFlight(source, target, airline);
    }

    flightsFile.close();
}

// Function to calculate and list statistics
void calculateAndListStatistics(const Graph& flightGraph) {
    // Implement statistics calculations and listing here
}

// Function to find the best flight option
void findBestFlightOption(const Graph& flightGraph, const string& source, const string& destination) {
    unordered_set<string> visited;
    queue<vector<string>> bfsQueue;  // Vector: Airport Path

    bfsQueue.push({source});  // Start from the source airport

    while (!bfsQueue.empty()) {
        auto currentPath = bfsQueue.front();
        bfsQueue.pop();

        string currentAirport = currentPath.back();

        // Check if we reached the destination
        if (currentAirport == destination) {
            cout << "Best flight option from " << source << " to " << destination << " with the least stops:\n";
            for (size_t i = 0; i < currentPath.size() - 1; ++i) {
                cout << "  " << currentPath[i] << " to " << currentPath[i + 1]
                          << " using airline(s): " << flightGraph.getAirlines(currentPath[i], currentPath[i + 1])[0] << "\n";
            }
            return;
        }

        // Mark the current airport as visited
        visited.insert(currentAirport);

        // Enqueue neighboring airports
        for (const auto& neighbor : flightGraph.getDestinations(currentAirport)) {
            if (visited.find(neighbor) == visited.end()) {
                auto newPath = currentPath;
                newPath.push_back(neighbor);
                bfsQueue.push(newPath);
            }
        }
    }

    cout << "No direct or connecting flights found from " << source << " to " << destination << endl;
}


// Main menu function
void displayMenu(Graph& flightGraph) {
    int choice;
    string source, destination;

    while (true) {
        cout << "\nFlight Management System Menu:\n";
        cout << "1. Load Dataset\n";
        cout << "2. Calculate Statistics\n";
        cout << "3. Find Best Flight Option\n";
        cout << "4. Exit\n";
        cout << "Enter your choice (1-4): ";

        cin >> choice;

        switch (choice) {
            case 1:
                readAndParseData(flightGraph);
                cout << "Dataset loaded successfully.\n";
                break;
            case 2:
                calculateAndListStatistics(flightGraph);
                break;
            case 3:
                cout << "Enter source airport code: ";
                cin >> source;
                cout << "Enter destination airport code: ";
                cin >> destination;
                findBestFlightOption(flightGraph, source, destination);
                break;
            case 4:
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }

        // Clear the input buffer to prevent infinite loop on invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    Graph flightGraph;

    displayMenu(flightGraph);
    
    return 0;
}
