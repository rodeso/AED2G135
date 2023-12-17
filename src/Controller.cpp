#include "../include/Controller.h"



int Controller::run() {
    // Specify the file paths for your CSV files
    string airportsFile = "../csv/airports.csv";
    string airlinesFile = "../csv/airlines.csv";
    string flightsFile = "../csv/flights.csv";

    // Parse airports
    vector<Airport> airports = CSVParser::parseAirports(airportsFile);

    // Parse airlines
    vector<Airline> airlines = CSVParser::parseAirlines(airlinesFile);
    cout << "Loading Data ...\n";
    // Parse flights using the previously parsed airports and airlines
    vector<Flight> flights = CSVParser::parseFlights(flightsFile, airports, airlines);
    flights.erase(flights.begin());

    cout << "Data Loaded!\nInitializing Graph...\n";

    // Create a graph of airports
    Graph<Airport> airportGraph;

    // Add vertices (airports) to the graph
    for (const Airport &airport : airports) {
        airportGraph.addVertex(airport);
    }

    // Add edges (flights) to the graph
    for (const Flight &flight : flights) {
        // Find the source and destination airports in the graph
        Vertex<Airport> *sourceVertex = airportGraph.findVertex(flight.getSourceAirport());
        Vertex<Airport> *destVertex = airportGraph.findVertex(flight.getTargetAirport());

        // Check if vertices are found (they should be since airports are added)
        if (sourceVertex != nullptr && destVertex != nullptr) {
            // Calculate distance and add the flight (edge) to the graph
            double distance = flight.getDistance(); // Implement this function based on coordinates
            airportGraph.addEdge(sourceVertex->getInfo(), destVertex->getInfo(), distance, flight.getAirline());
        } else {
            // Handle error: source or destination airport not found
            cerr << "Error: Airport not found for: \n" << flight.ticket() << endl;
        }
    }

    // Your graph is now initialized with airports and flights
    cout << "Graph Initialized!\n";

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

