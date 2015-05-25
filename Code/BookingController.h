#ifndef BOOKINGCONTROLLER_H
#define BOOKINGCONTROLLER_H

#include <string>
#include "sqlite3.h"
#include "schedule.h"
#include "Seat.h"


class BookingController
{
public:
	BookingController(sqlite3* d);
	int makeBooking(std::string user_type, std::string username,int schID);
	void setType(std::string user_type);
	std::string getType();
	void displaySeating(std::string sClass, Schedule sch);
	bool searchSeatingArray(int row, int let, Seat* arr, int size);



protected:
private:
	sqlite3* db;
	std::string userType;

};

#endif // BookingController_H
