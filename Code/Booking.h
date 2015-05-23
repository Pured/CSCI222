/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef BOOKING_H_
#define BOOKING_H_

#include "sqlite3.h"

class Booking{
private:
	sqlite3 *db;

	int ID, scheduleID;
	std::string custEmail, seatClass, travelAgent;

public:
	// Constructors.
	Booking(sqlite3 *d);
	Booking();

	// Get functions.
	int getID();
	std::string getCustEmail();
	int getScheduleID();
	std::string getSeatClass();
	std::string getTravelAgent();
	Booking *getByEmail(std::string, int &);

	// Set functions.
	void setDB(sqlite3 *);
	void setID(int);
	void setCustEmail(std::string);
	void setScheduleID(int);
	void setSeatClass(std::string);
	void setTravelAgent(std::string);
	int update();

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const Booking &T);
};

#endif //BOOKING_H_
