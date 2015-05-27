#ifndef BOOKINGCONTROLLER_H
#define BOOKINGCONTROLLER_H

#include <string>
#include "sqlite3.h"
#include "schedule.h"
#include "Booking.h"
#include "FlightService.h"
#include "Seat.h"


class BookingController
{
public:
	BookingController(sqlite3* d);
	int makeBooking(std::string user_type, std::string username);
	void setType(std::string user_type);
	std::string getType();
	void displaySeating(std::string sClass, Schedule sch);
	bool searchSeatingArray(int row, int let, Seat* arr, int size);
	void viewCustomerBookings(std::string email);
	int searchForSchedule();
	Seat chooseSeating(Booking B, Seat& check);
	FlightService chooseServices(Booking B,FlightService& newFS);



protected:
private:
	sqlite3* db;
	std::string userType;

};

#endif // BookingController_H
