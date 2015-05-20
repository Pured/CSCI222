/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#ifndef FLIGHTMANAGERCONTROLLER_H
#define FLIGHTMANAGERCONTROLLER_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class FlightManagerController{
public:
	FlightManagerController(sqlite3*);

	void findAircraft();
	void createAircraft();
	void editAircraft();
	void deleteAircraft();

	void findSchedule();
	void createSchedule();
	void editSchedule();
	void deleteSchedule();

	void findAirport();
	void createAirport();
	void editAirport();
	void deleteAirport();

	void findRoute();
	void createRoute();
	void editRoute();
	void deleteRoute();

	void flightReport();
private:
	sqlite3* db;
	string userType;
};

#endif // FLIGHTMANAGERCONTROLLER_H
