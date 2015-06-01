/*=============================================================
| Modified by: as277
| Version: 1.03
| Modification: added function
|==============================================================*/

#ifndef BOOKINGMANAGERCONTROLLER_H_
#define BOOKINGMANAGERCONTROLLER_H_

#include <string>
#include "sqlite3.h"

class BookingManagerController{
public:
	BookingManagerController(sqlite3 *); // Constructor.

	void checkNoFly();
	void bookingReport();
    void findTotalBookings();   //finds total number of bookings made so far
private:
	sqlite3 *db;

	std::string userType;
};

#endif // BOOKINGMANAGERCONTROLLER_H_
