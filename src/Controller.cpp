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
    int choice, i;
    int n, m;
    string source, destination;
    string airport, airline;
    vector<Airport> res;
    Airport chosenSource;
    Airport chosenDest;
    Airline chosenAirline;
    Flight chosenFlight;

    while (true) {
        cout <<"\n===== Airport Management System =====\n ";
        cout << "1. General Statistics\n ";
        cout << "2. Airport Info\n ";
        cout << "3. Airline Info\n ";
        cout << "4. Flight Info\n ";
        cout << "5. Book a Flight\n "; //TODO (4) (Present the Best Flight Options)
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
                    cout << "4. Longest Trip\n "; //TODO (7) (Most Stops)
                    cout << "5. Top X Airports\n "; //TODO (8) (In+Out Degree Max)
                    cout << "6. Essential Airports\n "; //TODO (9) (Bridge)
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> i;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1:
                            numAirports();
                            sleep(3);
                            break;
                        case 2:
                            numAirlines();
                            sleep(3);
                            break;
                        case 3:
                            numFlights();
                            sleep(3);
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
                        cout << "City Not Found!";
                        sleep(1);
                        break;
                    }
                    cout << "\n========== Airport(s) Found =========\n";
                    for (auto a: res) {
                        cout << "                ";
                        cout << a.getCode() << endl;
                    }
                    cout << "=====================================\n";
                    if (res.size() == 1) {
                        chosenSource = res[0];

                    } else {
                        cout << "Choose One: ";
                        cin >> n;
                        while (n > res.size()) {
                            cout << "Invalid Number, please try again!\n";
                            cin >> n;
                        }
                        chosenSource = res[n-1];
                    }

                } else {
                    auto airportIter = airportHashTable.find(airport);

                    if (airportIter != airportHashTable.end()) {
                        chosenSource = airportIter->second;
                    }
                    else {cout << "Airport Not Found!\n"; sleep(1);break;}
                }
                cout << chosenSource.getName() << " Airport, in " << chosenSource.getCity() << ", " << chosenSource.getCountry()
                     << " was Selected!\n";
                while (true) {
                    cout << "\n========= Airport Statistics ========\n ";
                    cout << "1. Number of Departing Flights\n ";
                    cout << "2. Number of Arriving Flights\n ";
                    cout << "3. Show Unique Departures\n ";
                    cout << "4. Show Unique Arrivals\n ";
                    cout << "5. Find Airline with Flight To\n ";
                    cout << "6. Find Airline with Flight From\n ";
                    cout << "7. Number of Possible Destinations\n "; //TODO (6)
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> i;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1:
                            numDepartures(chosenSource);
                            sleep(3);
                            break;
                        case 2:
                            numArrivals(chosenSource);
                            sleep(3);
                            break;
                        case 3:
                            showDestinations(chosenSource);
                            sleep(3);
                            break;
                        case 4:
                            showArrivals(chosenSource);
                            sleep(3);
                            break;
                        case 5:
                            showFlightsTo(chosenSource);
                            sleep(3);
                            break;
                        case 6:
                            showFlightsFrom(chosenSource);
                            sleep(3);
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
                    chosenAirline = airlineIter->second;
                }
                else {cout << "Airline Not Found!\n"; break;}
                cout << "\n=========== Airline Found ===========\n ";
                cout << "             " << chosenAirline.getCallsign();
                cout << "\n=====================================\n";


                cout << chosenAirline.getName() << " was Selected!\n";
                while (true) {
                    cout << "\n========= Airline Statistics ========\n ";
                    cout << "1. Number of Flights\n ";
                    cout << "2. Flights From a Location\n ";
                    cout << "3. Flights To a Location\n ";
                    cout << "4. Top X Airports (Departures)\n "; //TODO
                    cout << "5. Top X Airports (Arrivals)\n ";   //TODO
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> i;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1:
                            numAirlineFlights(chosenAirline);
                            sleep(3);
                            break;
                        case 2:
                            numAirlineFlightsFrom(chosenAirline);
                            sleep(3);
                            break;
                        case 3:
                            numAirlineFlightsTo(chosenAirline);
                            sleep(3);
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
                //Choose Flight //TODO Airport City or Location (coordinates)
                cout << "Enter Source Airport Code: ";
                cin >> source;
                auto airsource = airportHashTable.find(source);
                if (airsource != airportHashTable.end()) {
                    chosenSource = airsource->second;
                }
                else {cout << "Airport Not Found!\n"; break;}
                cout << "Enter Destination Airport Code: ";
                cin >> destination;
                auto airdest = airportHashTable.find(destination);
                if (airdest != airportHashTable.end()) {
                    chosenDest = airdest->second;
                }
                else {cout << "Airport Not Found!\n"; break;}
                cout << "Enter Airline Code: ";
                cin >> airline;
                auto airlineIter = airlineHashTable.find(airline);
                if (airlineIter != airlineHashTable.end()) {
                    chosenAirline = airlineIter->second;
                }
                else {cout << "Airline Not Found!\n"; sleep(1);break;}
                auto v = g.findVertex(chosenSource);
                bool flightFound = false;
                for (auto u : v->getAdj()) {
                    if (u.getDest()->getInfo() == chosenDest && u.getAirline() == chosenAirline) {
                        flightFound = true;
                    }
                }
                if (flightFound) {
                    for (auto f: flights) {
                        if (f.getAirline() == chosenAirline && f.getTargetAirport() == chosenDest &&
                            f.getSourceAirport() == chosenSource)
                            chosenFlight = f;
                    }
                    cout << "\n============ Flight Found ===========\n";
                    cout << chosenFlight.ticket();
                    cout << "\n=====================================\n";
                } else {
                    cout << "No Flight was Found!\n";
                    sleep(1);
                    break;
                }


                while (true) {
                    cout << "\n========= Flight Statistics ========\n ";
                    cout << "1. Distance\n "; //TODO
                    cout << "2. \n ";
                    cout << "3. \n ";
                    cout << "4. \n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> i;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1:
                            showDistance(chosenFlight);
                            sleep(3);
                            break;
                        case 2:
                            sleep(3);
                            break;
                        case 3:
                            sleep(3);
                            break;
                        case 4:
                            sleep(3);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
                break;
            }
            case 5: {
                //Choose Flight //TODO Airport City or Location (coordinates)
                cout << "Enter Source Airport Code: ";
                cin >> source;
                auto airsource = airportHashTable.find(source);
                if (airsource != airportHashTable.end()) {
                    chosenSource = airsource->second;
                }
                else {cout << "Airport Not Found!\n"; break;}
                cout << "Enter Destination Airport Code: ";
                cin >> destination;
                auto airdest = airportHashTable.find(destination);
                if (airdest != airportHashTable.end()) {
                    chosenDest = airdest->second;
                }
                else {cout << "Airport Not Found!\n"; break;}
                cout << "Enter Airline Code: ";
                cin >> airline;
                auto airlineIter = airlineHashTable.find(airline);
                if (airlineIter != airlineHashTable.end()) {
                    chosenAirline = airlineIter->second;
                }
                else {cout << "Airline Not Found!\n"; sleep(1);break;}
                auto v = g.findVertex(chosenSource);
                bool flightFound = false;
                for (auto u : v->getAdj()) {
                    if (u.getDest()->getInfo() == chosenDest && u.getAirline() == chosenAirline) {
                        flightFound = true;
                    }
                }
                if (flightFound) {
                    for (auto f: flights) {
                        if (f.getAirline() == chosenAirline && f.getTargetAirport() == chosenDest &&
                            f.getSourceAirport() == chosenSource)
                            chosenFlight = f;
                    }
                    cout << "\n============ Flight Found ===========\n";
                    cout << chosenFlight.ticket();
                    cout << "\n=====================================\n";
                } else {
                    cout << "No Flight was Found!\n";
                    sleep(1);
                    break;
                }


                while (true) {
                    cout << "\n========= Flight Statistics ========\n ";
                    cout << "1. Distance\n "; //TODO
                    cout << "2. \n ";
                    cout << "3. \n ";
                    cout << "4. \n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";
                    cin >> i;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1:
                            sleep(3);
                            break;
                        case 2:
                            sleep(3);
                            break;
                        case 3:
                            sleep(3);
                            break;
                        case 4:
                            sleep(3);
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
                sleep(3);
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
    unordered_set<string> uniqueAirlines;
    auto v = g.findVertex(a);

    for (auto u : v->getAdj()) {
        uniqueAirlines.insert(u.getAirline().getCode());
    }

    cout << "\n========== Departures Count =========\n";
    cout << " Unique Airlines: " << uniqueAirlines.size() << "\n";
    cout << " Total Departures: " << v->getAdj().size() << "\n";
    cout << "=====================================\n";
}
void Controller::numArrivals(Airport a) {
    unordered_set<string> uniqueAirlines;
    unsigned long n = 0;

    for (auto v : g.getVertexSet()) {
        for (auto u : v->getAdj()) {
            if (u.getDest()->getInfo() == a) {
                uniqueAirlines.insert(u.getAirline().getCode());
                n++;
            }
        }
    }

    cout << "\n=========== Arrivals Count ==========\n";
    cout << " Unique Airlines: " << uniqueAirlines.size() << "\n";
    cout << " Total Arrivals: " << n;
    cout << "\n=====================================\n";
}
void Controller::showDestinations(Airport a) {
    cout << "\n============ Destinations ===========\n ";
    auto v = g.findVertex(a);
    set<string> visitedDestinations;  // Use a set to store unique destinations
    set<string> visitedCountries;     // Use a set to store unique countries

    for (auto u : v->getAdj()) {
        const Airport &destination = u.getDest()->getInfo();
        string destinationInfo = destination.getCity() + destination.getCountry() + destination.getCode();

        if (visitedDestinations.find(destinationInfo) == visitedDestinations.end()) {
            std::cout << destination.getCity() << ", " << destination.getCountry() << " (" << destination.getCode()
                      << ")\n ";
            visitedDestinations.insert(destinationInfo);
        }

        if (visitedCountries.find(destination.getCountry()) == visitedCountries.end()) {
            // Print unique countries
            visitedCountries.insert(destination.getCountry());
        }
    }
    cout << "\n Unique Countries: " << visitedCountries.size();
    cout << "\n=====================================\n";
}

void Controller::showArrivals(Airport a) {
    cout << "\n============ Arriving Flights ===========\n ";
    set<string> visitedOrigins; // Use a set to store unique origins

    for (const auto &vertex : g.getVertexSet()) {
        for (const auto &edge : vertex->getAdj()) {
            const Airport &destination = edge.getDest()->getInfo();
            if (destination == a) {
                const Airport &origin = vertex->getInfo();
                string originInfo = origin.getCity() + origin.getCountry() + origin.getCode();

                if (visitedOrigins.find(originInfo) == visitedOrigins.end()) {
                    std::cout << origin.getCity() << ", " << origin.getCountry() << " (" << origin.getCode() << ")\n ";
                    visitedOrigins.insert(originInfo);
                }
                break; // Break to avoid printing the same origin multiple times for different incoming edges.
            }
        }
    }

    set<string> visitedCountries; // Use a set to store unique countries

    for (const auto &origin : visitedOrigins) {
        const Airport &originAirport = airportHashTable.find(origin.substr(origin.size() - 3))->second;
        if (visitedCountries.find(originAirport.getCountry()) == visitedCountries.end()) {
            // Print unique countries
            visitedCountries.insert(originAirport.getCountry());
        }
    }
    cout << "\n Unique Countries: " << visitedCountries.size();
    cout << "\n=====================================\n";
}

void Controller::showFlightsTo(Airport a) {
    string destination;
    Airport dest;
    bool direct = false;
    cout << "Enter Destination Airport Code: ";
    cin >> destination;
    auto airdest = airportHashTable.find(destination);
    if (airdest != airportHashTable.end()) {
        dest = airdest->second;
    }
    else {cout << "Airport Not Found!\n";
        return;}
    auto v1 = g.findVertex(a);
    auto v2 = g.findVertex(dest);

    for (auto u : v1->getAdj()) {
        if (u.getDest() == v2){
            direct = true;
        }
    }
    if (direct) {
        cout << "\n=========== Direct Flights ==========\n ";
        for (auto u: v1->getAdj()) {
            if (u.getDest() == v2) {
                cout << "                " << u.getAirline().getCode() << "\n ";
            }
        }
        cout << "=====================================\n";
    } else {
        cout << "Direct Flights Not Found!\n";
        cout << "Show Connecting Flights? (Y/n) ";
        string answer;
        int x;
        cin >> answer;
        if (answer == "n") return;
        else{
            cout << "Number of lay-overs: ";
            cin >> x;
            BFSWithLayovers(a, dest, x);
        }
    }
}
void Controller::showFlightsFrom(Airport a) {
    string sourceCode;
    Airport source;

    cout << "Enter Source Airport Code: ";
    cin >> sourceCode;

    auto sourceIter = airportHashTable.find(sourceCode);
    if (sourceIter != airportHashTable.end()) {
        source = sourceIter->second;
    } else {
        cout << "Airport Not Found!\n";
        return;
    }

    auto sourceVertex = g.findVertex(source);
    auto destinationVertex = g.findVertex(a);

    bool direct = false;
    for (const auto& neighbor : destinationVertex->getAdj()) {
        if (neighbor.getDest() == sourceVertex) {
            direct = true;
            break;
        }
    }

    if (direct) {
        cout << "\n=========== Direct Flights ==========\n";
        for (const auto& neighbor : destinationVertex->getAdj()) {
            if (neighbor.getDest() == sourceVertex) {
                cout << "                " << neighbor.getAirline().getCode() << "\n";
            }
        }
        cout << "=====================================\n";
    } else {
        cout << "Direct Flights Not Found!\n";
        cout << "Show Connecting Flights? (Y/n) ";
        string answer;
        cin >> answer;
        if (answer == "n") return;

        cout << "Number of lay-overs: ";
        int x;
        cin >> x;
        BFSWithLayovers(source, a, x);
    }
}
void Controller::BFSWithLayovers(const Airport& source, const Airport& destination, int maxLayovers) {
    queue<pair<Airport, vector<Airport>>> q;
    vector<Airport> visited;

    q.push({source, {source}});
    visited.push_back(source);

    while (!q.empty()) {
        auto front = q.front();
        q.pop();

        Airport currentAirport = front.first;
        const vector<Airport>& currentRoute = front.second;

        // Check if the current airport is the destination
        if (currentAirport == destination && currentRoute.size() - 2 <= maxLayovers) {
            std::cout << "Found a flight with " << currentRoute.size() - 2 << " layovers to " << destination.getCode() << "\n";
            std::cout << "Route: ";
            for (size_t i = 0; i < currentRoute.size() - 1; ++i) {
                std::cout << currentRoute[i].getCode() << " -> ";
            }
            std::cout << destination.getCode() << "\n";
        }

        // Enqueue neighboring airports
        for (const auto& neighbor : g.findVertex(currentAirport)->getAdj()) {
            auto it = std::find(visited.begin(), visited.end(), neighbor.getDest()->getInfo());
            if (it == visited.end()) {
                std::vector<Airport> newRoute = currentRoute;
                newRoute.push_back(neighbor.getDest()->getInfo());
                q.push({neighbor.getDest()->getInfo(), newRoute});
                visited.push_back(neighbor.getDest()->getInfo());
            }
        }
    }

    auto it = std::find(visited.begin(), visited.end(), destination);
    if (it == visited.end()) {
        std::cout << "No flights found to " << destination.getCode() << " with " << maxLayovers << " or fewer layovers\n";
    }
}

void Controller::numAirlineFlights(Airline a) {
    unsigned long n = 0;
    for (auto b : flights) {
        if (b.getAirline() == a) n++;
    }
    cout << "\n=========== Flights Count ===========\n";
    cout << "                " << n << "\n=====================================\n";
}
void Controller::numAirlineFlightsFrom(Airline a) {
    string sourceCode;
    Airport source;

    cout << "Enter Source Airport Code: ";
    cin >> sourceCode;

    auto sourceIter = airportHashTable.find(sourceCode);
    if (sourceIter != airportHashTable.end()) {
        source = sourceIter->second;
    } else {
        cout << "Airport Not Found!\n";
        return;
    }

    auto sourceVertex = g.findVertex(source);
    if (sourceVertex) {
        unsigned long numFlights = 0;

        for (const auto& edge : sourceVertex->getAdj()) {
            if (edge.getAirline() == a) {
                numFlights++;
            }
        }

        cout << "\n======= Airline Flights Count =======\n";
        cout << "                  " << numFlights;
        cout << "\n=====================================\n";
    } else {
        cout << "Source Airport Vertex Not Found!\n";
    }
}
void Controller::numAirlineFlightsTo(Airline a) {
    string destCode;
    Airport destination;

    cout << "Enter Destination Airport Code: ";
    cin >> destCode;

    auto destIter = airportHashTable.find(destCode);
    if (destIter != airportHashTable.end()) {
        destination = destIter->second;
    } else {
        cout << "Destination Airport Not Found!\n";
        return;
    }

    auto destVertex = g.findVertex(destination);

    if (destVertex) {
        unsigned long numFlights = 0;

        for (const auto& vertex : g.getVertexSet()) {
            for (const auto& edge : vertex->getAdj()) {
                if (edge.getDest()->getInfo() == destination && edge.getAirline() == a) {
                    numFlights++;
                }
            }
        }

        cout << "\n======= Airline Flights Count =======\n";
        cout << "                  " << numFlights;
        cout << "\n=====================================\n";
    } else {
        cout << "Destination Airport Vertex Not Found!\n";
    }
}
void Controller::showDistance(Flight f) {
    cout << "\n========== Flight Distance =========\n";
    cout << "              " << f.getDistance() << " km";
    cout << "\n=====================================\n";
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





