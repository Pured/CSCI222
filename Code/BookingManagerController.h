/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef BOOKINGMANAGERCONTROLLER_H_
#define BOOKINGMANAGERCONTROLLER_H_

#include <string>
#include "sqlite3.h"

class BookingManagerController{
public:
	BookingManagerController(sqlite3 *);

	void checkNoFly();
	void bookingReport();
private:
	sqlite3 *db;
	std::string userType;
};

#endif // BOOKINGMANAGERCONTROLLER_H_
