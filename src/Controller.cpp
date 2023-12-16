#include "../include/Controller.h"



int Controller::startController() {
    // Specify the file paths for your CSV files
    string airportsFile = "path/to/airports.csv";
    string airlinesFile = "path/to/airlines.csv";
    string flightsFile = "path/to/flights.csv";

    // Parse airports
    vector<Airport> airports = CSVParser::parseAirports(airportsFile);
    // Parse airlines
    vector<Airline> airlines = CSVParser::parseAirlines(airlinesFile);
    // Parse flights using the previously parsed airports and airlines
    vector<Flight> flights = CSVParser::parseFlights(flightsFile, airports, airlines);

    // Now you have vectors of Airport, Airline, and Flight objects to work with
    // ...

    return 0;
}


/*
// Main menu function
void displayMenu() {
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
 */

