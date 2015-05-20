//
//  ScheduleController.h
//  FlightSystem
//
//

#ifndef ___FlightSystem__ScheduleController__
#define ___FlightSystem__ScheduleController__

#include <iostream>
#include <vector>
#include "sqlite3.h"
#include "Schedule.h"

class ScheduleController{
private:
	sqlite3* db;

    
public:
    //constructors
    ScheduleController(sqlite3* d);
	Schedule* search(std::string from,std::string to ,int& resSize,int route); //2 dates as strings(YYYY--MM-DD), int to store amt results 
    
};

#endif /* defined(___FlightSystem__ScheduleController__) */
