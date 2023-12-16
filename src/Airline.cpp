#include "../include/Airline.h"


// Default constructor
Airline::Airline() {}

// Parameterized constructor
Airline::Airline(const string& code, const string& name, const string& callsign, const string& country)
        : code(code), name(name), callsign(callsign), country(country) {}

// Getter functions

string Airline::getCode() const {
    return code;
}

string Airline::getName() const {
    return name;
}

string Airline::getCallsign() const {
    return callsign;
}

string Airline::getCountry() const {
    return country;
}