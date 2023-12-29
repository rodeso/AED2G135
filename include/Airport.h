#ifndef AED2G135_AIRPORT_H
#define AED2G135_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    /// 3 Character Code
    string code;
    /// Full Name
    string name;
    /// English Name for the Airport's City
    string city;
    /// English Name for the Airport's Country
    string country;
    /// 6 Decimal Places Latitude
    double latitude;
    /// 6 Decimal Places Longitude
    double longitude;

public:
    /// Default constructor
    Airport();
    /// Real Constructor
    Airport(const string& code, const string& name, const string& city, const string& country, double latitude, double longitude);

    /// Code-based Equality Operator
    bool operator==(const Airport& other) const {
        return (code == other.code);
    }
    /// Code-based Operator for Sets
    bool operator<(const Airport& other) const {
        return code < other.code;
    }

    /// Returns 3 Character Code
    string getCode() const;
    /// Returns Full Name
    string getName() const;
    /// Returns English Name for the Airport's City
    string getCity() const;
    /// Returns English Name for the Airport's Country
    string getCountry() const;
    /// Returns 6 Decimal Places Latitude
    double getLatitude() const;
    /// Returns 6 Decimal Places Longitude
    double getLongitude() const;

};

class AirportHash {
public:
    /// Hashing System for the City Hashtable
    size_t operator()(const tuple<string, string>& key) const {
        hash<string> hasher;
        return hasher(get<0>(key)) ^ (hasher(get<1>(key)) << 1);
    }
};

#endif //AED2G135_AIRPORT_H
