/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef BOOKINGCONTROLLER_H_
#define BOOKINGCONTROLLER_H_

#include <string>
#include "Schedule.h"
#include "Booking.h"
#include "FlightService.h"
#include "Seat.h"
#include "sqlite3.h"

class BookingController{
public:
	BookingController(sqlite3 *d);

	int makeBooking(std::string user_type, std::string username);
	void setType(std::string user_type);
	std::string getType();
	void displaySeating(std::string sClass, Schedule sch);
	bool searchSeatingArray(int row, int let, Seat *arr, int size);
	void viewCustomerBookings(std::string email);
	int searchForSchedule();
	Seat chooseSeating(Booking B, Seat &check);
	FlightService chooseServices(Booking B, FlightService &newFS);

private:
	sqlite3 *db;
	std::string userType;
};

#endif // BookingController_H_
