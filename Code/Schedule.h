//
//  Schedule.h
//  FlightSystem
//
//

#ifndef ___FlightSystem__Schedule__
#define ___FlightSystem__Schedule__

#include <iostream>
#include "sqlite3.h"

class Schedule{
private:
	sqlite3* db;
    int ID;
    std::string flightID;
    int plane;
    int route;
	std::string depart;
	std::string arrive;
    
public:
    //constructors
    Schedule(sqlite3* d);
    
    //get functions
    int getID() const;
    std::string getFlightID() const;
    int getPlane() const;
    int getRoute() const;
	std::string getDepart() const;
	std::string getArrive() const;
	std::string getByID(int);

    //set functions
    void setID(int);
    void setFlightID(std::string);
    void setPlane(int);
    void setRoute(int);
	void setDepart(std::string);
	void setArrive(std::string);
	int update();

    //other functions
    friend std::ostream &operator<<( std::ostream &output, const Schedule &T);

};

#endif /* defined(___FlightSystem__Schedule__) */
