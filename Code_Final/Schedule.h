/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Added the create/update/delete functions.
|==============================================================*/

#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "sqlite3.h"

class Schedule{
public:
	// Constructors.
	Schedule(sqlite3 *d);
	Schedule();

	// Get functions.
	int getID() const;
	std::string getFlightID() const;
	int getPlane() const;
	int getRoute() const;
	std::string getDepartDay() const;
	std::string getDepart() const;
	std::string getDepartTimezone() const;
	std::string getArriveDay() const;
	std::string getArrive() const;
	std::string getArriveTimezone() const;
	std::string getByID(int);

	// Set functions.
	void setDB(sqlite3 *);
	void setID(int);
	void setFlightID(std::string);
	void setPlane(int);
	void setRoute(int);
	void setDepartDay(std::string);
	void setDepart(std::string);
	void setDepartTimezone(std::string);
	void setArriveDay(std::string);
	void setArrive(std::string);
	void setArriveTimezone(std::string);

    // Other functions.
    friend std::ostream &operator<<(std::ostream &output, const Schedule &T);
	void createSchedule();
	void updateSchedule();
	void deleteSchedule();

private:
	sqlite3 *db;
	int ID;
	std::string flightID;
	int plane;
	int route;
	std::string departDay; // Day of week of departure.
	std::string depart; // Date of departure.
	std::string departTimezone; // Timezone of departing airport.
	std::string arriveDay; // Day of week of arrival.
	std::string arrive; // Date of arrival.
	std::string arriveTimezone; // Timezone of arriving airport.
};

#endif // SCHEDULE_H_
