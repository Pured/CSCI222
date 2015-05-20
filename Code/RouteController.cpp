//
//  RouteController.cpp
//  222test
//
//

#include "Route.h"
#include "RouteController.h"
#include <sstream>
#include "sqlite3.h"
#include <iostream>

using namespace std;

//constructors
RouteController::RouteController(sqlite3* d){
	db=d;
}

