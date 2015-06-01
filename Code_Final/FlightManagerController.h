/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef FLIGHTMANAGERCONTROLLER_H_
#define FLIGHTMANAGERCONTROLLER_H_

#include <iostream>
#include "sqlite3.h"

class FlightManagerController{
public:
	FlightManagerController(sqlite3 *); // Constructor.

	// Aircraft funtions.
	void findAircraft();
	void createAircraft();
	void editAircraft();
	void deleteAircraft();

	// Airport funtions.
	void findAirport();
	void createAirport();
	void editAirport();
	void deleteAirport();

	// Route funtions.
	void findRoute();
	void createRoute();
	void editRoute();
	void deleteRoute();

	// Schedule funtions.
	void findSchedule();
	void createSchedule();
	void editSchedule();
	void deleteSchedule();

	void flightReport();

private:
	sqlite3 *db;
	std::string userType;
};

#endif // FLIGHTMANAGERCONTROLLER_H_
