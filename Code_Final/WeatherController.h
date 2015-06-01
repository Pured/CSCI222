/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef WEATHERCONTROLLER_H_
#define WEATHERCONTROLLER_H_

#include <iostream>
#include "sqlite3.h"
#include "Airport.h"

class WeatherController
{
private:
	sqlite3* db;
	std::string weatherQuery;
	float lat;
	float lon;
	int numDays;

public:
	WeatherController(sqlite3* d);

	void setWQuery();
	void setLat(float l);
	void setLon(float l);
	void setNumDays(int i);

	int executeQuery();
	void displayResults();
	std::string* getAllAirportIATA(int& resSize);
	int getAirportWeather(Airport a);
	int searchDanger(); //dont use, too slow.
	int checkDanger(); //dont use, too slow.

};

#endif // WEATHERCONTROLLER_H_

