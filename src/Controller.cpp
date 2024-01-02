#include "../include/Controller.h"


Controller::Controller() {
    // Specify the file paths for your CSV files
    // *!* PLEASE CHANGE THESE TO THE CORRECT PATH *!*
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
    string city, country;
    vector<Airport> resA;
    vector<Airport> resB;
    vector<vector<Airport>> resC;
    vector<Airport> chosenRoute;
    Airport chosenSource;
    Airport chosenDest;
    Airline chosenAirline;
    Flight chosenFlight;
    tuple<string, string> key;
    double latitude, longitude;
    vector<pair<Airport, Airport>> longestPairs;
    while (true) {
        cout <<"\n===== Airport Management System =====\n ";
        cout << "1. General Statistics\n ";
        cout << "2. Airport Info\n ";
        cout << "3. Airline Info\n ";
        cout << "4. Flight Info\n ";
        cout << "5. Find a Trip\n ";
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
                    cout << "4. Trip with Most Stops\n ";
                    cout << "5. Top X Airports\n ";
                    cout << "6. Essential Airports\n ";
                    cout << "7. Longest Trip (Half across the Globe)\n ";
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
                        case 4:
                            findLongestPath();
                            sleep(3);
                            break;
                        case 5:
                            topAirports();
                            sleep(3);
                            break;
                        case 6:
                            articulationPoints();
                            sleep(3);
                            break;
                        case 7:
                            findHighestStopsPairs();
                            sleep(3);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            sleep(1);
                            continue;
                    }
                }
                break;
            }
            case 2: {
                //Choose Airport
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Airport Code or City: ";
                getline(cin, airport);
                if (airport.size() > 3) {
                    cout << "Enter Country Name: ";
                    getline(cin, country);
                    cout << "Looking Airports in " << airport << ", " << country << endl;
                    key = make_tuple(airport, country);
                    auto cityIter = cityHashTable.find(key);

                    if (cityIter != cityHashTable.end()) {
                        resA = cityIter->second;
                    } else {
                        cout << "City Not Found!";
                        sleep(1);
                        continue;
                    }
                    cout << "\n========== Airport(s) Found =========\n";
                    int contador = 1;
                    for (auto a: resA) {
                        cout << "                ";
                        cout << contador << ':' << ' ' << a.getCode() << endl;
                        contador++;
                    }
                    cout << "========== Choose a number ==========\n";
                    if (resA.size() == 1) {
                        chosenSource = resA[0];

                    } else {
                        cout << "Choose One: ";
                        cin >> n;
                        while (n > resA.size() || n < 1) {
                            cout << "Invalid Number, please try again!\n";
                            cin >> n;
                        }
                        chosenSource = resA[n-1];
                    }

                } else {
                    auto airportIter = airportHashTable.find(airport);

                    if (airportIter != airportHashTable.end()) {
                        chosenSource = airportIter->second;
                    }
                    else {cout << "Airport Not Found!\n"; sleep(1);
                        continue;}
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
                    cout << "7. Number of Possible Destinations\n ";
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
                        case 7:
                            int x;
                            cout << "Maximum Lay-overs? ";
                            cin >> x;
                            possibleDestinations(chosenSource, x);
                            sleep(3);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            sleep(1);
                            continue;
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
                else {cout << "Airline Not Found!\n";
                    sleep(1);
                    continue;}
                cout << "\n=========== Airline Found ===========\n ";
                cout << "             " << chosenAirline.getCallsign();
                cout << "\n=====================================\n";


                cout << chosenAirline.getName() << " was Selected!\n";
                while (true) {
                    cout << "\n========= Airline Statistics ========\n ";
                    cout << "1. Number of Flights\n ";
                    cout << "2. Flights From a Location\n ";
                    cout << "3. Flights To a Location\n ";
                    cout << "4. Top X Airports (Departures)\n ";
                    cout << "5. Top X Airports (Arrivals)\n ";
                    cout << "6. Flight Availability\n ";
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
                            topAirportsDepartures(chosenAirline);
                            sleep(3);
                            break;
                        case 5:
                            topAirportsArrivals(chosenAirline);
                            sleep(3);
                            break;
                        case 6:
                            hasFlight(chosenAirline);
                            sleep(3);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            sleep(1);
                            continue;
                    }
                }
                break;
            }
            case 4: {
                //Choose Flight
                cout << "Enter Source Airport Code: ";
                cin >> source;
                auto airsource = airportHashTable.find(source);
                if (airsource != airportHashTable.end()) {
                    chosenSource = airsource->second;
                }
                else {cout << "Airport Not Found!\n"; sleep(1); continue;}
                cout << "Enter Destination Airport Code: ";
                cin >> destination;
                auto airdest = airportHashTable.find(destination);
                if (airdest != airportHashTable.end()) {
                    chosenDest = airdest->second;
                }
                else {cout << "Airport Not Found!\n"; sleep(1); continue;}
                cout << "Enter Airline Code: ";
                cin >> airline;
                auto airlineIter = airlineHashTable.find(airline);
                if (airlineIter != airlineHashTable.end()) {
                    chosenAirline = airlineIter->second;
                }
                else {cout << "Airline Not Found!\n"; sleep(1); continue;}
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
                    cout << "1. Distance\n ";
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
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            sleep(1);
                            continue;
                    }
                }
                break;
            }
            case 5: {
                //Choose Flight
                while (true) {
                    cout << "\n======= Choose Starting Point =======\n ";
                    cout << "1. Airport Code\n ";
                    cout << "2. City\n ";
                    cout << "3. Location\n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";

                    cin >> i;
                    resA = {};
                    auto airsource = airportHashTable.find(source);
                    auto cityIter = cityHashTable.find(key);
                    bool multipleSource = false;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1: //CODE
                            cout << "Enter Source Airport Code: ";
                            cin >> source;
                            airsource = airportHashTable.find(source);
                            if (airsource != airportHashTable.end()) {
                                chosenSource = airsource->second;
                            } else {
                                cout << "Airport Not Found!\n";
                                sleep(1);
                                continue;
                            }
                            resA.push_back(chosenSource);
                            break;
                        case 2: //CITY
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Enter City Name: ";
                            getline(cin, city);
                            cout << "Enter Country Name: ";
                            getline(cin, country);
                            cout << "Looking Airports in " << city << ", " << country << endl;
                            key = make_tuple(city, country);
                            cityIter = cityHashTable.find(key);
                            if (cityIter != cityHashTable.end()) {
                                resA = cityIter->second;
                            } else {
                                cout << "City Not Found!";
                                sleep(1);
                                continue;
                            }
                            if (resA.size() > 1) { multipleSource = true; }
                            break;
                        case 3: //LOCATION
                            cout << "Enter Latitude: ";
                            cin >> latitude;
                            cout << "Enter Longitude: ";
                            cin >> longitude;
                            chosenSource = findClosest(latitude, longitude);
                            resA.push_back(chosenSource);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            continue;
                    }
                    cout << "\n======= Chosen Starting Point =======\n";
                    for (auto a: resA) {
                        cout << " ";
                        cout << a.getName() << " in " << a.getCity() << ", " << a.getCountry() << " (" << a.getCode()
                             << ")\n";
                    }
                    cout << "=====================================\n";
                    break;
                }
                while (true) {
                    cout << "\n======== Choose Ending Point ========\n ";
                    cout << "1. Airport Code\n ";
                    cout << "2. City\n ";
                    cout << "3. Location\n ";
                    cout << "0. Go Back ";
                    cout << "\n=====================================\n";

                    cin >> i;
                    resB = {};
                    auto airDest = airportHashTable.find(source);
                    auto cityIter = cityHashTable.find(key);
                    bool multipleDest = false;
                    if (i == 0) {
                        cout << "Returning to the Main Menu!\n";
                        sleep(1);
                        break;
                    }
                    switch (i) {
                        case 1: //CODE
                            cout << "Enter Source Airport Code: ";
                            cin >> source;
                            airDest = airportHashTable.find(source);
                            if (airDest != airportHashTable.end()) {
                                chosenDest = airDest->second;
                            } else {
                                cout << "Airport Not Found!\n";
                                sleep(1);
                                continue;
                            }
                            resB.push_back(chosenDest);
                            break;
                        case 2: //CITY
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Enter City Name: ";
                            getline(cin, city);
                            cout << "Enter Country Name: ";
                            getline(cin, country);
                            cout << "Looking Airports in " << city << ", " << country << endl;
                            key = make_tuple(city, country);
                            cityIter = cityHashTable.find(key);
                            if (cityIter != cityHashTable.end()) {
                                resB = cityIter->second;
                            } else {
                                cout << "City Not Found!";
                                sleep(1);
                                continue;
                            }
                            if (resB.size() > 1) { multipleDest = true; }
                            break;
                        case 3: //LOCATION
                            cout << "Enter Latitude: ";
                            cin >> latitude;
                            cout << "Enter Longitude: ";
                            cin >> longitude;
                            chosenDest = findClosest(latitude, longitude);
                            resB.push_back(chosenDest);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            sleep(1);
                            continue;
                    }
                    cout << "\n======== Chosen Ending Point ========\n";
                    for (auto a: resB) {
                        cout << " ";
                        cout << a.getName() << " in " << a.getCity() << ", " << a.getCountry() << " ("
                             << a.getCode() << ")\n";
                    }
                    cout << "=====================================\n";
                    break;
                }
                // Get Flights
                for (auto a : resA) {
                    for (auto b : resB) {
                        auto v1 = g.findVertex(a);
                        auto v2 = g.findVertex(b);
                        resC.push_back(BFSWithLayovers(a, b, 9));
                    }
                }
                if (resC.size() == 0) {
                    cout << "\nThis Route is Invalid! Try Again.";
                    break;
                }
                cout << "\nChoose Route for More Info: ";
                cin >> i;
                while (i > resC.size() || i < 1) {
                    cout << "Invalid Number, please try again!\n";
                    cin >> i;
                }
                chosenRoute = resC[i-1];
                while (true) {
                    cout << "\n============= Route Info ============\n ";
                    cout << "1. See Airports\n ";
                    cout << "2. See Airlines\n ";
                    cout << "3. See Distance\n ";
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
                            cout << "\n============== Airports =============\n";
                            for (auto a : chosenRoute) {
                                cout << " ";
                                cout << a.getName() << " in " << a.getCity() << ", " << a.getCountry() << " ("
                                     << a.getCode() << ")\n";
                            }
                            cout << "=====================================\n";
                            sleep(3);
                            break;
                        case 2:
                            airlinesAvailable(chosenRoute);
                            sleep(3);
                            break;
                        case 3:
                            totalDistance(chosenRoute);
                            sleep(3);
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            sleep(1);
                            continue;
                    }
                }
                sleep(3);
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
                sleep(1);
                break;
        }

        // Clear the input buffer to prevent infinite loop on invalid input
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
void Controller::findLongestPathDFS(Vertex<Airport>* currentVertex, vector<Airport>& currentRoute, int& maxStops, vector<Airport>& maxRoute) {
    if (currentRoute.size() - 1 > maxStops) {
        maxStops = currentRoute.size() - 1;
        maxRoute = currentRoute;
    }

    currentVertex->setProcessing(true);

    for (const auto& edge : currentVertex->getAdj()) {
        Vertex<Airport>* neighborVertex = edge.getDest();

        if (!neighborVertex->isVisited()) {
            neighborVertex->setVisited(true);
            currentRoute.push_back(neighborVertex->getInfo());
            findLongestPathDFS(neighborVertex, currentRoute, maxStops, maxRoute);
            currentRoute.pop_back();
        }
    }

    currentVertex->setVisited(true);
    currentVertex->setProcessing(false);
}

void Controller::findLongestPath() {
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    int maxStops = 0;
    vector<Airport> maxRoute;

    for (auto v : g.getVertexSet()) {
        if (!v->isVisited()) {
            vector<Airport> currentRoute = {v->getInfo()};
            v->setVisited(true);
            findLongestPathDFS(v, currentRoute, maxStops, maxRoute);
        }
    }
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    cout << "Maximum trip from " << maxRoute[0].getCode() << " to " << maxRoute[maxRoute.size()-1].getCode() << " with " << maxStops << " stops:\n";
    for (const auto& airport : maxRoute) {
        cout << airport.getCode() << " -> ";
    }
    cout << "\n";
}
void Controller::topAirports() {
    int x;
    cout << "X: ";
    cin >> x;
    vector<pair<Airport, int>> airportDegrees;

    for (const auto &vertex : g.getVertexSet()) {
        int inDegree = 0;
        int outDegree = vertex->getAdj().size();

        for (const auto &v : g.getVertexSet()) {
            for (const auto &edge : v->getAdj()) {
                if (edge.getDest() == vertex) {
                    ++inDegree;
                }
            }
        }

        int totalDegree = inDegree + outDegree;
        airportDegrees.emplace_back(vertex->getInfo(), totalDegree);
    }

    sort(airportDegrees.begin(), airportDegrees.end(),
         [](const auto &a, const auto &b) {
             return a.second > b.second;
         });

    cout << "\n============ Top Airports ===========\n";
    for (int i = 0; i < min(x, static_cast<int>(airportDegrees.size())); ++i) {
        const Airport &airport = airportDegrees[i].first;
        int totalDegree = airportDegrees[i].second;
        cout << " " << i + 1 << ": " << airport.getCity() << ", " << airport.getCountry()
             << " (" << airport.getCode() << ") - Total Flights: " << totalDegree << "\n";
    }
    cout << "=====================================\n";
}
void Controller::articulationPoints() const {
    set<Vertex<Airport>*> articulationPoints;
    Graph<Airport> g2 = g;
    for (auto v : g2.getVertexSet()) {
        for (auto e : v->getAdj()) {
            g2.addEdge(e.getDest()->getInfo(),v->getInfo(), 0, Airline());
        }
    }
    for (Vertex<Airport>* v : g2.getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }

    int time = 0;

    for (Vertex<Airport>* v : g2.getVertexSet()) {
        if (!v->isVisited()) {
            ArticulationPointsDFS(v, articulationPoints, time, nullptr);
        }
    }

    cout << "\n======== Essential Airports =========\n";
    for (Vertex<Airport>* v : articulationPoints) {
        cout << " Airport: " << v->getInfo().getName() << ", Code: " << v->getInfo().getCode() << endl;
    }
    cout << "\n======== Essential Airports N =======\n ";
    cout << "                  " << articulationPoints.size();
    cout << "\n=====================================\n";
}

void Controller::ArticulationPointsDFS(Vertex<Airport>* currentVertex, set<Vertex<Airport>*>& articulationPoints, int& time, Vertex<Airport>* parent) const {
    currentVertex->setVisited(true);
    currentVertex->setProcessing(true);
    currentVertex->setNum(time);
    currentVertex->setLow(time);
    time++;

    int children = 0;

    for (Edge<Airport> edge : currentVertex->getAdj()) {
        Vertex<Airport>* neighborVertex = edge.getDest();

        if (!neighborVertex->isVisited()) {
            children++;
            ArticulationPointsDFS(neighborVertex, articulationPoints, time, currentVertex);

            currentVertex->setLow(min(currentVertex->getLow(), neighborVertex->getLow()));

            if (currentVertex->getNum() <= neighborVertex->getLow() && parent != nullptr) {
                articulationPoints.insert(currentVertex);
            }
        } else if (neighborVertex != parent) {
            currentVertex->setLow(min(currentVertex->getLow(), neighborVertex->getNum()));
        }
    }

    currentVertex->setProcessing(false);

    if (parent == nullptr && children > 1) {
        articulationPoints.insert(currentVertex);
    }
}
vector<Airport> Controller::shortestPath(const Airport& source, const Airport& destination) const {
    priority_queue<pair<double, Vertex<Airport>*>, vector<pair<double, Vertex<Airport>*>>, greater<>> pq;
    unordered_map<Airport, double> distance;
    unordered_map<Airport, Vertex<Airport>*> previous;

    Vertex<Airport>* sourceVertex = g.findVertex(source);
    Vertex<Airport>* destinationVertex = g.findVertex(destination);

    if (!sourceVertex || !destinationVertex) {
        return vector<Airport>();
    }

    for (const auto& vertex : g.getVertexSet()) {
        if (vertex == sourceVertex)
            distance[vertex->getInfo()] = 0;
        else
            distance[vertex->getInfo()] = numeric_limits<double>::infinity();
        previous[vertex->getInfo()] = nullptr;
        pq.push({distance[vertex->getInfo()], vertex});
    }

    while (!pq.empty()) {
        auto currentPair = pq.top();
        pq.pop();
        auto current = currentPair.second;

        if (current->isVisited()) {
            continue;
        }

        current->setVisited(true);

        for (const auto& edge : current->getAdj()) {
            auto neighbor = edge.getDest();
            double newDistance = distance[current->getInfo()] + edge.getWeight();

            if (newDistance < distance[neighbor->getInfo()]) {
                distance[neighbor->getInfo()] = newDistance;
                previous[neighbor->getInfo()] = current;
                pq.push({newDistance, neighbor});
            }
        }
    }

    for (const auto& vertex : g.getVertexSet()) {
        vertex->setVisited(false);
    }

    vector<Airport> path;
    auto current = destinationVertex;

    while (current != nullptr) {
        path.push_back(current->getInfo());
        current = previous[current->getInfo()];
    }

    reverse(path.begin(), path.end());
    return path;
}

void Controller::findHighestStopsPairs() const {
    int maxStops = -1;
    vector<pair<Airport, Airport>> maxStopsPairs;

    for (const auto& vertex : g.getVertexSet()) {
        vertex->setVisited(false);
    }

    for (const auto& source : g.getVertexSet()) {
        for (const auto& destination : g.getVertexSet()) {
            if (source != destination) {
                vector<Airport> path = shortestPath(source->getInfo(), destination->getInfo());

                if (!path.empty() && path.size() - 1 > maxStops) {
                    maxStops = path.size() - 1;
                    maxStopsPairs.clear();
                    maxStopsPairs.emplace_back(source->getInfo(), destination->getInfo());
                } else if (!path.empty() && path.size() - 1 == maxStops) {
                    maxStopsPairs.emplace_back(source->getInfo(), destination->getInfo());
                }
            }
        }
    }

    cout << "Pairs with the highest number of stops (" << maxStops << " stops):" << endl;
    for (const auto& pair : maxStopsPairs) {
        cout << "Source: " << pair.first.getCode() << " - Destination: " << pair.second.getCode() << endl;
    }
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
    set<string> visitedDestinations;
    set<string> visitedCountries;

    for (auto u : v->getAdj()) {
        const Airport &destination = u.getDest()->getInfo();
        string destinationInfo = destination.getCity() + destination.getCountry() + destination.getCode();

        if (visitedDestinations.find(destinationInfo) == visitedDestinations.end()) {
            cout << destination.getCity() << ", " << destination.getCountry() << " (" << destination.getCode()
                      << ")\n ";
            visitedDestinations.insert(destinationInfo);
        }

        if (visitedCountries.find(destination.getCountry()) == visitedCountries.end()) {
            visitedCountries.insert(destination.getCountry());
        }
    }
    cout << "\n Unique Countries: " << visitedCountries.size();
    cout << "\n=====================================\n";
}

void Controller::showArrivals(Airport a) {
    cout << "\n============ Arriving Flights ===========\n ";
    set<string> visitedOrigins;

    for (const auto &vertex : g.getVertexSet()) {
        for (const auto &edge : vertex->getAdj()) {
            const Airport &destination = edge.getDest()->getInfo();
            if (destination == a) {
                const Airport &origin = vertex->getInfo();
                string originInfo = origin.getCity() + origin.getCountry() + origin.getCode();

                if (visitedOrigins.find(originInfo) == visitedOrigins.end()) {
                    cout << origin.getCity() << ", " << origin.getCountry() << " (" << origin.getCode() << ")\n ";
                    visitedOrigins.insert(originInfo);
                }
                break;
            }
        }
    }

    set<string> visitedCountries;

    for (const auto &origin : visitedOrigins) {
        const Airport &originAirport = airportHashTable.find(origin.substr(origin.size() - 3))->second;
        if (visitedCountries.find(originAirport.getCountry()) == visitedCountries.end()) {
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
void Controller::possibleDestinations(const Airport& chosenSource, int maxLayovers) {
    auto sourceVertex = g.findVertex(chosenSource);

    if (!sourceVertex) {
        cout << "Chosen source airport not found.\n";
        return;
    }

    set<Airport> visitedAirports;
    set<string> visitedCities;
    set<string> visitedCountries;

    queue<pair<Airport, int>> q;
    q.push({chosenSource, 0});

    while (!q.empty()) {
        auto front = q.front();
        q.pop();

        Airport currentAirport = front.first;
        int layovers = front.second;

        visitedAirports.insert(currentAirport);
        visitedCities.insert(currentAirport.getCity());
        visitedCountries.insert(currentAirport.getCountry());

        if (layovers <= maxLayovers) {
            auto currentVertex = g.findVertex(currentAirport);
            currentVertex->setVisited(true);

            for (const auto& edge : currentVertex->getAdj()) {
                auto neighborAirport = edge.getDest()->getInfo();

                if (!edge.getDest()->isVisited()) {
                    q.push({neighborAirport, layovers + 1});
                    edge.getDest()->setVisited(true);
                }
            }
        }
    }
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    cout << "\n======= Reachable Destinations ======\n ";
    cout << "Possible destinations from " << chosenSource.getCode() << " with up to " << maxLayovers << " layovers:\n ";
    cout << "Unique Airports: " << visitedAirports.size() << "\n ";
    cout << "Unique Cities: " << visitedCities.size() << "\n ";
    cout << "Unique Countries: " << visitedCountries.size();
    cout << "\n=====================================\n";
}
vector<Airport> Controller::BFSWithLayovers(const Airport& source, const Airport& destination, int maxLayovers) {
    vector<Airport> res;
    queue<pair<Airport, vector<Airport>>> q;
    vector<Airport> visited;

    q.push({source, {source}});
    visited.push_back(source);

    while (!q.empty()) {
        auto front = q.front();
        q.pop();

        Airport currentAirport = front.first;
        const vector<Airport>& currentRoute = front.second;

        if (currentAirport == destination && currentRoute.size() - 2 <= maxLayovers) {
            cout << "Found a flight with " << currentRoute.size() - 2 << " layovers to " << destination.getCode() << "\n";
            cout << "Route: ";
            for (size_t i = 0; i < currentRoute.size() - 1; ++i) {
                cout << currentRoute[i].getCode() << " -> ";
                res.push_back(currentRoute[i]);
            }
            cout << destination.getCode() << "\n";
            res.push_back(destination);
        }

        for (const auto& neighbor : g.findVertex(currentAirport)->getAdj()) {
            auto it = find(visited.begin(), visited.end(), neighbor.getDest()->getInfo());
            if (it == visited.end()) {
                vector<Airport> newRoute = currentRoute;
                newRoute.push_back(neighbor.getDest()->getInfo());
                q.push({neighbor.getDest()->getInfo(), newRoute});
                visited.push_back(neighbor.getDest()->getInfo());
            }
        }
    }

    auto it = find(visited.begin(), visited.end(), destination);
    if (it == visited.end()) {
        cout << "No flights found to " << destination.getCode() << " with " << maxLayovers << " or fewer layovers\n";
    }
    return res;
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


void Controller::topAirportsDepartures(Airline a){
    int x;
    cout << "X: ";
    cin >> x;
    vector<pair<Airport, int>> airportDegrees;

    for (const auto &vertex : g.getVertexSet()) {
        int outDegree = 0;

        for (const auto &edge : vertex->getAdj()) {
            if (edge.getAirline() == a) {
                ++outDegree;
            }
        }

        airportDegrees.emplace_back(vertex->getInfo(), outDegree);
    }

    sort(airportDegrees.begin(), airportDegrees.end(),
              [](const auto &a, const auto &b) {
                  return a.second > b.second;
              });

    cout << "\n============ Top Airports ===========\n";
    for (int i = 0; i < min(x, static_cast<int>(airportDegrees.size())); ++i) {
        const Airport &airport = airportDegrees[i].first;
        int totalDegree = airportDegrees[i].second;
        cout << " " << i + 1 << ": " << airport.getCity() << ", " << airport.getCountry()
                  << " (" << airport.getCode() << ") - Total Flights: " << totalDegree << "\n";
    }
    cout << "=====================================\n";
}

void Controller::topAirportsArrivals(Airline a){
    int x;
    cout << "X: ";
    cin >> x;
    vector<pair<Airport, int>> airportDegrees;

    for (const auto &vertex : g.getVertexSet()) {
        int inDegree = 0;

        for (const auto &v : g.getVertexSet()) {
            for (const auto &edge : v->getAdj()) {
                if (edge.getDest() == vertex && edge.getAirline() == a) {
                    ++inDegree;
                }
            }
        }

        airportDegrees.emplace_back(vertex->getInfo(), inDegree);
    }

    sort(airportDegrees.begin(), airportDegrees.end(),
              [](const auto &a, const auto &b) {
                  return a.second > b.second;
              });

    cout << "\n============ Top Airports ===========\n";
    for (int i = 0; i < min(x, static_cast<int>(airportDegrees.size())); ++i) {
        const Airport &airport = airportDegrees[i].first;
        int totalDegree = airportDegrees[i].second;
        cout << " " << i + 1 << ": " << airport.getCity() << ", " << airport.getCountry()
                  << " (" << airport.getCode() << ") - Total Flights: " << totalDegree << "\n";
    }
    cout << "=====================================\n";
}


void Controller::hasFlight(Airline a) {
    string sourceCode, destCode;

    cout << "Enter Source Airport Code: ";
    cin >> sourceCode;

    cout << "Enter Destination Airport Code: ";
    cin >> destCode;

    bool flightFound = false;
    for (const Flight& flight : flights) {
        if (flight.getSourceAirport().getCode() == sourceCode && flight.getTargetAirport().getCode() == destCode && flight.getAirline() == a) {
            flightFound = true;
            break;
        }
    }

    if (flightFound) {
        cout << "The airline has a flight from " << sourceCode << " to " << destCode << endl;
    } else {
        cout << "No matching flight found for the specified criteria." << endl;
    }
}
void Controller::showDistance(Flight f) {
    cout << "\n========== Flight Distance =========\n";
    cout << "              " << f.getDistance() << " km";
    cout << "\n=====================================\n";
}
double Controller::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;
    const double dLat = (lat2 - lat1) * (M_PI / 180.0);
    const double dLon = (lon2 - lon1) * (M_PI / 180.0);

    const double a = sin(dLat / 2) * sin(dLat / 2) +
                     cos(lat1 * (M_PI / 180.0)) * cos(lat2 * (M_PI / 180.0)) *
                     sin(dLon / 2) * sin(dLon / 2);

    const double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}
Airport Controller::findClosest(double targetLat, double targetLon) {
    Airport closest;
    double minDistance = numeric_limits<double>::max();

    for (const auto& airport : airports) {
        double distance = haversine(targetLat, targetLon, airport.getLatitude(), airport.getLongitude());
        if (distance < minDistance) {
            minDistance = distance;
            closest = airport;
        }
    }

    return closest;
}
void Controller::airlinesAvailable(const vector<Airport>& chosenRoute) {
    if (chosenRoute.size() < 2) {
        cout << "Invalid route size.\n";
        return;
    }
    cout << "\n=============== Airlines ============\n ";
    cout << "Available Airlines for the chosen route:\n";

    for (size_t i = 0; i < chosenRoute.size() - 1; ++i) {
        auto currentAirport = chosenRoute[i];
        auto nextAirport = chosenRoute[i + 1];

        auto currentVertex = g.findVertex(currentAirport);
        auto nextVertex = g.findVertex(nextAirport);

        if (currentVertex && nextVertex) {
            vector<Airline> uniqueAirlines;

            for (const auto& edge : currentVertex->getAdj()) {
                if (edge.getDest() == nextVertex) {
                    uniqueAirlines.push_back(edge.getAirline());
                }
            }

            if (!uniqueAirlines.empty()) {
                cout << " From " << currentAirport.getCode() << " to " << nextAirport.getCode() << ":\n ";
                for (const auto& airline : uniqueAirlines) {
                    cout << " - " << airline.getCode() << ": " << airline.getName() << "\n ";
                }
            } else {
                cout << " No airlines found from " << currentAirport.getCode() << " to " << nextAirport.getCode() << "\n";
            }
        }
    }
    cout << "=====================================\n";
}
void Controller::totalDistance(const vector<Airport>& chosenRoute) {
    unsigned n = 0;
    for (int i = 0; i < chosenRoute.size()-1; i++) {
        n+= haversine(chosenRoute[i].getLatitude(), chosenRoute[i].getLongitude(),chosenRoute[i+1].getLatitude(), chosenRoute[i+1].getLongitude());
    }
    cout << "\n============ Total Distance =========\n ";
    cout << "                " << n << " km";
    cout << "\n=====================================\n";
}
void Controller::displayCredits() {
    cout << "\n=============== Credits =============\n";
    cout << "This program was created by:\n  ";
    cout << "André de Sousa\n  ";
    cout << "Álvaro Pacheco\n  ";
    cout << "Rodrigo de Sousa\n ";
    cout << "Date: December 2023";
    cout << "\n=====================================\n";
}






