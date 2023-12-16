#ifndef AED2G135_AIRLINE_H
#define AED2G135_AIRLINE_H

#include <string>
#include <vector>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callsign;
    string country;

public:
    // Constructors
    Airline();  // Default constructor
    Airline(const string& code, const string& name, const string& callsign, const string& country);

    // Getters
    string getCode() const;
    string getName() const;
    string getCallsign() const;
    string getCountry() const;
};


#endif //AED2G135_AIRLINE_H
