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
	std::string departDay; //day of week of departure
	std::string depart; //date of departure
	std::string departTimezone; //timezone of departing airport
	std::string arriveDay; //day of week of arrival
	std::string arrive; //date of arrival
	std::string arriveTimezone; //timezone of departing airport
    
public:
    //constructors
    Schedule(sqlite3* d);
	Schedule();
    
    //get functions
    int getID() const;
    std::string getFlightID() const;
    int getPlane() const;
    int getRoute() const;
	std::string getDepartDay() const;
	std::string getDepart() const;
	std::string getDepartTimezone() const;
	std::string getArriveDay() const;
	std::string getArrive() const;
	std::string getArriveTimezone() const;
	std::string getByID(int);

    //set functions
	void setDB(sqlite3*);
    void setID(int);
    void setFlightID(std::string);
    void setPlane(int);
    void setRoute(int);
	void setDepartDay(std::string);
	void setDepart(std::string);
	void setDepartTimezone(std::string);
	void setArriveDay(std::string);
	void setArrive(std::string);
	void setArriveTimezone(std::string);
	int update();

    //other functions
    friend std::ostream &operator<<( std::ostream &output, const Schedule &T);

};

#endif /* defined(___FlightSystem__Schedule__) */
