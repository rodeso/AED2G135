#ifndef AED2G135_FLIGHT_H
#define AED2G135_FLIGHT_H

#include <string>
#include "Airport.h"
#include "Airline.h"
using namespace std;

class Flight {
private:
    int id;
    static int nextId;
    Airport sourceAirport;
    Airport targetAirport;
    Airline airline;

public:
    //Constructor
    Flight();
    Flight(Airport  source, Airport  target, Airline  airline);

    //Getters
    const Airport& getSourceAirport() const;
    const Airport& getTargetAirport() const;
    const Airline& getAirline() const;
    double getDistance() const;
    int getid() const;
    string ticket() const;

    long getid();
};


#endif //AED2G135_FLIGHT_H
