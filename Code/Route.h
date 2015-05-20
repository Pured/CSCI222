//
//  Route.h
// FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__Route__
#define ___FlightSystem__Route__

#include <iostream>
#include "sqlite3.h"

class Route{
private:
	sqlite3* db;
    int ID;
    std::string srcAirport;
    std::string destAirport;
    std::string codeshare;
    int stops;
    
public:
    //constructors
    Route(sqlite3*);
	Route();
    
    //get functions
    int getID() const;
    std::string getSrc() const;
    std::string getDest() const;
    std::string getCodeshare() const;
    int getStops() const;
	std::string getByID(int);
	int getByAirports(std::string,std::string);
    
    //set Functions
    void setID(int);
    void setSrc(std::string);
    void setDest(std::string);
    void setCodeshare(std::string);
    void setStops(int);
	int update();
    
    //other functions
    friend std::ostream &operator<<( std::ostream &output,const Route &R);
    
};

#endif /* defined(___FlightSystem__Route__) */
