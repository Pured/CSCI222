/*=============================================================
| Modified by: kb100
| Version: 1.02
| Description: Restyled the code.
|==============================================================*/

#ifndef FLIGHTSERVICE_H_
#define FLIGHTSERVICE_H_

#include "sqlite3.h"

class FlightService{
public:
	// Constructors.
	FlightService(sqlite3 *d);
	FlightService();

	// Get functions.
	int getID() const;
	int getScheduleID() const;
	int getServiceItemID() const;
	int getBookingID() const;
	int getAmount() const;
	std::string getByID(int ID);
	FlightService *getByBookingID(int BID, int &resSize);
	FlightService *getByScheduleID(int SID, int &resSize);


	// Set functions.
	void setDB(sqlite3 *d);
	void setID(int id);
	void setScheduleID(int SID);
	void setServiceItemID(int SIID);
	void setBookingID(int BID);
	void setAmount(int amt);

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const FlightService &F);
	FlightService operator=(const FlightService &FS);
	int createFlightService();
	int deleteFlightService();

private:
	sqlite3 *db;
	int ID;
	int scheduleID;
	int serviceItemID;
	int bookingID;
	int amount;
};

#endif // FLIGHTSERVICE_H_

