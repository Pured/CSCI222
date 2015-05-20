//
//  Booking.h
//  FlightSystem
//
//

#ifndef ___FlightSystem__Booking__
#define ___FlightSystem__Booking__

#include <iostream>
#include "sqlite3.h"

class Booking{
private:
	sqlite3* db;
	int ID;
	std::string custEmail;
	int scheduleID;
	std::string seatClass;
	std::string travelAgent;

    
public:
    //constructors
    Booking(sqlite3* d);
	Booking();
    
    //get functions
	int getID();
	std::string getCustEmail();
	int getScheduleID();
	std::string getSeatClass();
	std::string getTravelAgent();
	Booking* getByEmail(std::string,int&);

    //set functions
	void setDB(sqlite3*);
	void setID(int);
	void setCustEmail(std::string);
	void setScheduleID(int);
	void setSeatClass(std::string);
	void setTravelAgent(std::string);
	int update();

    //other functions
    friend std::ostream &operator<<( std::ostream &output, const Booking &T);

};

#endif /* defined(___FlightSystem__Booking__) */
