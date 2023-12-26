#include <cmath>
#include <sstream>
#include <utility>
#include "../include/Flight.h"

int Flight::nextId = 0;

Flight::Flight() {
    id = 0;
    sourceAirport = Airport();
    targetAirport = Airport();
    airline = Airline();
}
Flight::Flight(Airport  source, Airport  target, Airline  airline)
        : sourceAirport(std::move(source)), targetAirport(std::move(target)), airline(std::move(airline)), id(nextId++) {}


const Airport& Flight::getSourceAirport() const {
    return sourceAirport;
}

const Airport& Flight::getTargetAirport() const {
    return targetAirport;
}

const Airline& Flight::getAirline() const {
    return airline;
}
int Flight::getid() const {
    return id;
}
string Flight::ticket() const {
    stringstream ticketInfo;
    ticketInfo << " Flight Ticket for Flight: " << id << endl;
    ticketInfo << " Source Airport: " << sourceAirport.getCode() << " - " << sourceAirport.getName() << "\n";
    ticketInfo << " Destination Airport: " << targetAirport.getCode() << " - " << targetAirport.getName() << "\n";
    ticketInfo << " Airline: " << airline.getCode() << " - " << airline.getName();
    return ticketInfo.str();
}
//Haversine formula
double Flight::getDistance() const {
    double sourceLat = sourceAirport.getLatitude();
    double sourceLon = sourceAirport.getLongitude();
    double destLat = targetAirport.getLatitude();
    double destLon = targetAirport.getLongitude();

    // Use the Haversine formula to calculate distance
    const double R = 6371.0;  // Earth radius in kilometers

    double dLat = (destLat - sourceLat) * (M_PI / 180.0);
    double dLon = (destLon - sourceLon) * (M_PI / 180.0);

    double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
               cos(sourceLat * (M_PI / 180.0)) * cos(destLat * (M_PI / 180.0)) *
               sin(dLon / 2.0) * sin(dLon / 2.0);

    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    double distance = R * c;
    return distance;
}




