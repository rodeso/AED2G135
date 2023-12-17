#include <csignal>
#include "../include/Controller.h"


Controller::Controller() {
    // Specify the file paths for your CSV files
    string airportsFile = "../csv/airports.csv";
    string airlinesFile = "../csv/airlines.csv";
    string flightsFile = "../csv/flights.csv";

    // Parse airports
    airports = CSVParser::parseAirports(airportsFile);

    // Parse airlines
    airlines = CSVParser::parseAirlines(airlinesFile);
    airlines.erase(airlines.begin());
    cout << "Loading Data...\n";
    // Parse flights using the previously parsed airports and airlines
    flights = CSVParser::parseFlights(flightsFile, airports, airlines);
    flights.erase(flights.begin());

    cout << "Data Loaded!\nInitializing Graph...\n";



    // Add vertices (airports) to the graph
    for (const Airport &airport : airports) {
        g.addVertex(airport);
    }

    // Add edges (flights) to the graph
    for (const Flight &flight : flights) {
        // Find the source and destination airports in the graph
        Vertex<Airport> *sourceVertex = g.findVertex(flight.getSourceAirport());
        Vertex<Airport> *destVertex = g.findVertex(flight.getTargetAirport());

        // Check if vertices are found (they should be since airports are added)
        if (sourceVertex != nullptr && destVertex != nullptr) {
            // Calculate distance and add the flight (edge) to the graph
            double distance = flight.getDistance(); // Implement this function based on coordinates
            g.addEdge(sourceVertex->getInfo(), destVertex->getInfo(), distance, flight.getAirline());
        } else {
            // Handle error: source or destination airport not found
            cerr << "Error: Airport not found for: \n" << flight.ticket() << endl;
        }
    }

    // Your graph is now initialized with airports and flights
    cout << "Graph Initialized!\n";
}



// Main menu function
void Controller::displayMenu() {
    int choice;
    string source, destination;

    while (true) {
        cout <<"\n===== Airport Management System =====\n ";
        cout << "1. General Statistics\n ";
        cout << "2. Airport Info\n ";
        cout << "3. Airline Info\n ";
        cout << "4. Flight Info\n ";
        cout << "5. \n ";
        cout << "6. \n ";
        cout << "7. \n ";
        cout << "8. \n ";
        cout << "9. Display Credits\n ";
        cout << "0. Exit";
        cout << "\n=====================================\n";

        cin >> choice;

        switch (choice) {
            case 1:
                while (true) {
                    cout << "\n========= Airport Statistics ========\n ";
                    cout << "1. Number of Airports\n ";
                    cout << "2. Number of Airlines\n ";
                    cout << "3. Number of Flights\n ";
                    cout << "3. \n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> choice;
                    if (choice == 0) {
                        break;
                    }
                    switch (choice) {
                        case 1:
                            numAirports();
                            break;
                        case 2:
                            numAirlines();
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            case 2:

                break;
            case 3:
                cout << "Enter source airport code: ";
                cin >> source;
                cout << "Enter destination airport code: ";
                cin >> destination;

                break;
            case 9:
                displayCredits();
                break;
            case 0:
                cout << "Exiting the program.\n";
                return;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }

        // Clear the input buffer to prevent infinite loop on invalid input
        cin.clear();
        sleep(5);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void Controller::numAirports() {
    unsigned long n = g.getNumVertex();
    cout << "\n=========== Airport Count ===========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::numAirlines() {
    unsigned long n = airlines.size();
    cout << "\n=========== Airport Count ===========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::displayCredits() {
    cout << "\n=============== Credits ============= \n";
    cout << "This program was created by:\n  ";
    cout << "André de Sousa\n  ";
    cout << "Álvaro Pacheco\n  ";
    cout << "Rodrigo de Sousa\n ";
    cout << "Date: December 2023";
    cout << "\n=====================================\n";
}



