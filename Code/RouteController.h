//
//  RouteController.h
//  FlightSystem
//
//

#ifndef ___FlightSystem__RouteController__
#define ___FlightSystem__RouteController__

#include <iostream>
#include "sqlite3.h"
#include "Route.h"

class RouteController{
private:
	sqlite3* db;

    
public:
    //constructors
    RouteController(sqlite3* d);
	Route* alphabeticList(int& resSize);
	
    
};

#endif /* defined(___FlightSystem__RouteController__) */
