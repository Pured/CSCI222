/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef BOOKING_H_
#define BOOKING_H_

#include "sqlite3.h"

class Booking{
public:
	// Constructors.
	Booking(sqlite3 *d);
	Booking();

	// Get functions.
	int getID();
	std::string getCustEmail();
	int getScheduleID();
	int getMRE(); //get most recent entry ID
	std::string getTravelAgent();
	Booking *getByEmail(std::string, int &);
    Booking *getTravelByEmail(std::string, int &);

	// Set functions.
	void setDB(sqlite3 *);
	void setID(int);
	void setCustEmail(std::string);
	void setScheduleID(int);
	void setTravelAgent(std::string);
	int update();
	int create();

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const Booking &T);

private:
	sqlite3 *db;

	int ID, scheduleID;
	std::string custEmail, travelAgent;
};

#endif //BOOKING_H_
