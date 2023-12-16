#ifndef AED2G135_FLIGHT_H
#define AED2G135_FLIGHT_H

#include <string>
#include "Airport.h"
#include "Airline.h"
using namespace std;

class Flight {
private:
    Airport sourceAirport;
    Airport targetAirport;
    Airline airline;

public:
    //Constructor
    Flight(const Airport& source, const Airport& target, const Airline& airline);

    //Getters
    const Airport& getSourceAirport() const;
    const Airport& getTargetAirport() const;
    const Airline& getAirline() const;

};


#endif //AED2G135_FLIGHT_H
