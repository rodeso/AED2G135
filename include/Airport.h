#ifndef AED2G135_AIRPORT_H
#define AED2G135_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;

public:
    // Constructors
    Airport();  // Default constructor
    Airport(const string& code, const string& name, const string& city, const string& country, double latitude, double longitude);

    bool operator==(const Airport& other) const {
        return (code == other.code);
    }
    bool operator<(const Airport& other) const {
        return code < other.code;
    }
    // Getters
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

};


#endif //AED2G135_AIRPORT_H
