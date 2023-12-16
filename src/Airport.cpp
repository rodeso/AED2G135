#include "../include/Airport.h"


// Default constructor
Airport::Airport() : latitude(0.0), longitude(0.0) {}

// Parameterized constructor
Airport::Airport(const string& code, const string& name, const string& city, const string& country, double latitude, double longitude)
        : code(code), name(name), city(city), country(country), latitude(latitude), longitude(longitude) {}

// Getter functions

string Airport::getCode() const {
    return code;
}

string Airport::getName() const {
    return name;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCountry() const {
    return country;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}