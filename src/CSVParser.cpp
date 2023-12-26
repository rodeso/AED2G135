#include <sstream>
#include <fstream>
#include "../include/CSVParser.h"

vector<Airport> CSVParser::parseAirports(const string& filename) {
    vector<Airport> airports;

    ifstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        return airports;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string code, name, city, country;
        double latitude, longitude;

        if (getline(ss, code, ',') &&
            getline(ss, name, ',') &&
            getline(ss, city, ',') &&
            getline(ss, country, ',') &&
            ss >> latitude &&
            ss.ignore() &&
            ss >> longitude) {
            airports.push_back(Airport(code, name, city, country, latitude, longitude));
        } else {
            // Handle parsing error for an airport record
        }
    }

    file.close();
    return airports;
}

vector<Airline> CSVParser::parseAirlines(const string& filename) {
    vector<Airline> airlines;

    ifstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        return airlines;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string code, name, callsign, country;

        if (getline(ss, code, ',') &&
            getline(ss, name, ',') &&
            getline(ss, callsign, ',') &&
            getline(ss, country, ',')) {
            airlines.push_back(Airline(code, name, callsign, country));
        } else {
            // Handle parsing error for an airline record
        }
    }

    file.close();
    return airlines;
}

vector<Flight> CSVParser::parseFlights(const string& filename, const vector<Airport>& airports, const vector<Airline>& airlines) {
    vector<Flight> flights;

    ifstream file(filename);
    if (!file.is_open()) {
        // Handle file open error
        return flights;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string sourceCode, targetCode, airlineCode;

        if (getline(ss, sourceCode, ',') &&
            getline(ss, targetCode, ',') &&
            getline(ss, airlineCode, ',')) {
            // Find the corresponding airport and airline objects
            Airport sourceAirport, targetAirport;
            Airline airline;

            for (const auto& airport : airports) {
                if (airport.getCode() == sourceCode) {
                    sourceAirport = airport;
                }
                if (airport.getCode() == targetCode) {
                    targetAirport = airport;
                }
            }

            for (const auto& a : airlines) {
                if (a.getCode() == airlineCode) {
                    airline = a;
                }
            }

            flights.push_back(Flight(sourceAirport, targetAirport, airline));
        } else {
            // Handle parsing error for a flight record
        }
    }

    file.close();
    return flights;
}