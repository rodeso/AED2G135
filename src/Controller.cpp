#include <csignal>
#include "../include/Controller.h"


Controller::Controller() {
    // Specify the file paths for your CSV files
    string airportsFile = "../csv/airports.csv";
    string airlinesFile = "../csv/airlines.csv";
    string flightsFile = "../csv/flights.csv";

    // Parse airports
    airports = CSVParser::parseAirports(airportsFile);
    for (auto x : airports) addAirportToHashTable(x);
    // Parse airlines
    airlines = CSVParser::parseAirlines(airlinesFile);
    airlines.erase(airlines.begin());
    for (auto y : airlines) addAirlineToHashTable(y);
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
    int choice, i, ii, iii;
    int n, m;
    string source, destination;
    string airport, airline;
    vector<Airport> res;
    Airport chosen;
    Airport chosen2;
    Airline cho;
    Flight flosen;

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
            case 1: {
                while (true) {
                    cout << "\n========= General Statistics ========\n ";
                    cout << "1. Number of Airports\n ";
                    cout << "2. Number of Airlines\n ";
                    cout << "3. Number of Flights\n ";
                    cout << "4. \n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> i;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        break;
                    }
                    switch (i) {
                        case 1:
                            numAirports();
                            break;
                        case 2:
                            numAirlines();
                            break;
                        case 3:
                            numFlights();
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }
            case 2: {
                //Choose Airport
                cout << "Enter Airport Code or City: ";
                cin >> airport;
                if (airport.size() > 3) {
                    auto cityIter = cityHashTable.find(airport);

                    if (cityIter != cityHashTable.end()) {
                        res = cityIter->second;
                    } else {
                        res = {};
                    }
                    cout << "\n========= Airport(s) Found ========\n ";
                    cout << "             ";
                    for (auto a: res) {
                        cout << a.getCode();
                    }
                    if (res.size() == 1) {
                        chosen = res[0];
                        cout << "\n=====================================\n";
                    } else {
                        cout << "\n                Choose One";
                        cout << "\n=====================================\n";
                        cin >> n;
                        while (n >= res.size()) {
                            cout << "Invalid Number, please try again!\n";
                            cin >> n;
                        }
                        chosen = res[n];
                    }

                } else {
                    auto airportIter = airportHashTable.find(airport);

                    if (airportIter != airportHashTable.end()) {
                        chosen = airportIter->second;
                    }
                    else {cout << "Airport Not Found!\n"; break;}
                }
                cout << chosen.getCode() << " Airport, in " << chosen.getCity() << ", " << chosen.getCountry()
                     << " was Selected!\n";
                while (true) {
                    cout << "\n========= Airport Statistics ========\n ";
                    cout << "1. Number of Departing Flights\n ";
                    cout << "2. Number of Arriving Flights\n ";
                    cout << "3. Possible Direct Destinations\n ";
                    cout << "4. Find Flight To\n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> ii;
                    if (ii == 0) {
                        cout << "Returning to the Main Menu!\n";
                        break;
                    }
                    switch (ii) {
                        case 1:
                            numDepartures(chosen);
                            break;
                        case 2:
                            numArrivals(chosen);
                            break;
                        case 3:
                            showDestinations(chosen);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }
            case 3: {
                //Choose Airline
                cout << "Enter Airline Code: ";
                cin >> airline;
                auto airlineIter = airlineHashTable.find(airline);
                if (airlineIter != airlineHashTable.end()) {
                    cho = airlineIter->second;
                }
                else {cout << "Airline Not Found!\n"; break;}
                cout << "\n========= Airline Found ========\n ";
                cout << "             " << cho.getCallsign();
                cout << "\n=====================================\n";


                cout << cho.getName() << " was Selected!\n";
                while (true) {
                    cout << "\n========= Airline Statistics ========\n ";
                    cout << "1. \n ";
                    cout << "2. \n ";
                    cout << "3. \n ";
                    cout << "4. \n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> iii;
                    if (iii == 0) {
                        cout << "Returning to the Main Menu!\n";
                        break;
                    }
                    switch (iii) {
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }
            case 4: {
                //Choose Flight //TODO
                cout << "Enter Source Airport Code: ";
                cin >> source;
                auto airsource = airportHashTable.find(source);
                if (airsource != airportHashTable.end()) {
                    chosen = airsource->second;
                }
                else {cout << "Airport Not Found!\n"; break;}
                cout << "Enter Destination Airport Code: ";
                cin >> destination;
                auto airdest = airportHashTable.find(destination);
                if (airdest != airportHashTable.end()) {
                    chosen2 = airdest->second;
                }
                else {cout << "Airport Not Found!\n"; break;}
                cout << "Enter Airline Code: ";
                cin >> airline;
                auto airlineIter = airlineHashTable.find(airline);
                if (airlineIter != airlineHashTable.end()) {
                    cho = airlineIter->second;
                }
                else {cout << "Airline Not Found!\n"; break;}
                auto v = g.findVertex(chosen);
                bool flightFound = false;
                for (auto u : v->getAdj()) {
                    if (u.getDest()->getInfo() == chosen2 && u.getAirline() == cho) {
                        flightFound = true;
                    }
                }
                if (flightFound) {
                    for (auto f: flights) {
                        if (f.getAirline() == cho && f.getTargetAirport() == chosen2 &&
                            f.getSourceAirport() == chosen)
                            flosen = f;
                    }
                    cout << "\n============ Flight Found ===========\n";
                    cout << flosen.ticket();
                    cout << "\n=====================================\n";
                } else {
                    cout << "No Flight was Found!\n";
                }


                while (true) {
                    cout << "\n========= Flight Statistics ========\n ";
                    cout << "1. \n ";
                    cout << "2. \n ";
                    cout << "3. \n ";
                    cout << "4. \n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> iii;
                    if (iii == 0) {
                        cout << "Returning to the Main Menu!\n";
                        break;
                    }
                    switch (iii) {
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }

            case 9:
                displayCredits();
                break;
            case 0:
                cout << "Exiting the program. Thank you for using our Software!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        // Clear the input buffer to prevent infinite loop on invalid input
        cin.clear();
        sleep(3);
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
    cout << "\n=========== Airline Count ===========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::numFlights() {
    unsigned long n = flights.size();
    cout << "\n=========== Flight Count ===========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::numDepartures(Airport a) {
    unsigned long n = 0;
    auto v = g.findVertex(a);
    for (auto u : v->getAdj()) {
        n++;
    }
    cout << "\n========= Departures Count =========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::numArrivals(Airport a) {
    unsigned long n = 0;
    for (auto v : g.getVertexSet()) {
        for (auto u : v->getAdj()) {
            if (u.getDest()->getInfo() == a)
                n++;
        }
    }
    cout << "\n========== Arrivals Count ==========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::showDestinations(Airport a) {
    cout << "\n============ Destinations ==========\n ";
    auto v = g.findVertex(a);
    for (auto u : v->getAdj()) {
        cout << u.getDest()->getInfo().getCity() << ", " << u.getDest()->getInfo().getCountry() << " (" << u.getDest()->getInfo().getCode() << ")\n ";
    }
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



