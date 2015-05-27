/*=============================================================
| Modified by: djm749
| Version: 1.01
| Description: Modified
|==============================================================*/


#ifndef ___FlightSystem__FlightService__
#define ___FlightSystem__FlightService__

#include "sqlite3.h"
#include <iostream>

class FlightService
{
private:
	sqlite3* db;
	int ID;
	int scheduleID;
	int serviceItemID;
	int bookingID;
	int amount;

public:
	FlightService(sqlite3* d);
	FlightService();

	//get methods
	int getID() const;
	int getScheduleID() const;
	int getServiceItemID() const;
	int getBookingID() const;
	int getAmount() const;
	std::string getByID(int ID);
	FlightService* getByBookingID(int BID,int& resSize);
	FlightService* getByScheduleID(int SID, int& resSize);


	//set methods
	void setDB(sqlite3* d);
	void setID(int id);
	void setScheduleID(int SID);
	void setServiceItemID(int SIID);
	void setBookingID(int BID);
	void setAmount(int amt);

	//other functions
	friend std::ostream &operator<<(std::ostream &output, const FlightService &F);
	FlightService operator=(const FlightService &FS);
	int create();
	int deleteFlightService();
};

#endif //___FlightSystem__FlightService__

