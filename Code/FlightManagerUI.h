/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Connected the UI to the Controller.
|==============================================================*/

#ifndef FLIGHTMANAGERUI_H
#define FLIGHTMANAGERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class FlightManagerUI{
public:
	FlightManagerUI(sqlite3*);

	bool run();
	void accessAircraftsMenu();
	void accessSchedulesMenu();
	void accessAirportsMenu();
	void accessRoutesMenu();
private:
	sqlite3* db;
	string userType;
};

#endif // FLIGHTMANAGERUI_H
