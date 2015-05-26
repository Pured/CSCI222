/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef FLIGHTMANAGERUI_H_
#define FLIGHTMANAGERUI_H_

#include "sqlite3.h"

class FlightManagerUI{
public:
	FlightManagerUI(sqlite3 *); // Constructor.

	bool run();
	void accessAircraftsMenu();
	void accessSchedulesMenu();
	void accessAirportsMenu();
	void accessRoutesMenu();
	void airportWeatherMenu();

private:
	sqlite3 *db;
	std::string userType;
};

#endif // FLIGHTMANAGERUI_H_
