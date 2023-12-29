#ifndef AED2G135_CSVPARSER_H
#define AED2G135_CSVPARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"

using namespace std;

class CSVParser {
private:

public:
    static vector<Airport> parseAirports(const string& filename);
    static vector<Airline> parseAirlines(const string& filename);
    static vector<Flight> parseFlights(const string& filename, const vector<Airport>& airports, const vector<Airline>& airlines);
};


#endif //AED2G135_CSVPARSER_H
