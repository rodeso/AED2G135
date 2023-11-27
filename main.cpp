#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

// Assume you have a Graph class provided in your practical classes

// Function to read and parse the dataset
void readAndParseData(Graph& flightGraph) {
    // Implement data reading and parsing here
    // Populate the flightGraph with airports, airlines, and connections
}

// Function to calculate and list statistics
void calculateAndListStatistics(const Graph& flightGraph) {
    // Implement statistics calculations and listing here
}

// Function to find the best flight option
void findBestFlightOption(const Graph& flightGraph, const std::string& source, const std::string& destination) {
    // Implement the search for the best flight option based on criteria
}

// Main menu function
void displayMenu() {
    // Implement a user-friendly menu to display features
    // You can include options for data loading, statistics, flight search, etc.
}

int main() {
    Graph flightGraph;  // Assume you have a Graph class

    // Step 1: Read and parse data
    readAndParseData(flightGraph);

    // Step 2: Display the main menu
    displayMenu();

    // You can implement a loop for user interaction, where the user can choose various options from the menu

    return 0;
}
