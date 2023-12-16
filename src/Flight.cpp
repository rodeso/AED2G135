#include "../include/Flight.h"

Flight::Flight(const Airport& source, const Airport& target, const Airline& airline)
        : sourceAirport(source), targetAirport(target), airline(airline) {}

// Add getters if needed
const Airport& Flight::getSourceAirport() const {
    return sourceAirport;
}

const Airport& Flight::getTargetAirport() const {
    return targetAirport;
}

const Airline& Flight::getAirline() const {
    return airline;
}