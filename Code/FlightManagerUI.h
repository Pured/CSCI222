/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Modified the code order.
|==============================================================*/

#ifndef FLIGHTMANAGERUI_H_
#define FLIGHTMANAGERUI_H_

#include "sqlite3.h"

class FlightManagerUI{
public:
	FlightManagerUI(sqlite3 *); // Constructor.

	bool run();
	void accessAircraftsMenu();
	void accessAirportsMenu();
	void accessRoutesMenu();
	void accessSchedulesMenu();
	void airportWeatherMenu();

private:
	sqlite3 *db;
	std::string userType;
};

#endif // FLIGHTMANAGERUI_H_
