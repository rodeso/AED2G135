#ifndef AED2G135_AIRLINE_H
#define AED2G135_AIRLINE_H

#include <string>
#include <vector>

using namespace std;

class Airline {
private:
    /// 3 Character Code
    string code;
    /// Full Name
    string name;
    /// Short Name
    string callsign;
    /// Origin
    string country;

public:

    /// Default Constructor
    Airline();
    /// Real Constructor
    Airline(const string& code, const string& name, const string& callsign, const string& country);

    /// Code-based Equality Operator
    bool operator==(const Airline& other) const {
        return (code == other.code);
    }


    /// Returns 3 Character Code
    string getCode() const;
    /// Returns Full Name
    string getName() const;
    /// Returns Short Name
    string getCallsign() const;
    /// Returns Origin
    string getCountry() const;
};


#endif //AED2G135_AIRLINE_H
