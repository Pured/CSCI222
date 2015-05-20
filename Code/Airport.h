//
//  Airport.h
//  FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__Airport__
#define ___FlightSystem__Airport__

#include <iostream>
#include "sqlite3.h"

class Airport{
private:
	sqlite3* db;
    int ID;
    std::string name;
    std::string city;
    std::string country;
    std::string iata;
    float latitude;
    float longitude;
    int altitude;
    int timezone;
    std::string dst;
    std::string tz;
    
public:
    //constructors
    Airport(sqlite3*);
	Airport();
    
    //get functions
    int getID() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    std::string getIATA() const;
    float getLat() const;
    float getLong() const;
    int getAlt() const;
    int getTimezone() const;
    std::string getDST() const;
    std::string getTZ() const;
	std::string getByIata(std::string i);
	std::string getByName(std::string);
    
    //set functions
	void setDB(sqlite3*);
    void setID(int);
    void setName(std::string);
    void setCity(std::string);
    void setIATA(std::string);
    void setLat(float);
    void setLong(float);
    void setAlt(int);
    void setTimezone(int);
    void setDST(std::string);
    void setTZ(std::string);
	int update();
    
    //other functions
    friend std::ostream &operator<<( std::ostream &os,const Airport &A);
	Airport* alphabeticList();
    
};

#endif /* defined(___FlightSystem__Airport__) */
