/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#ifndef BOOKINGMANAGERCONTROLLER_H
#define BOOKINGMANAGERCONTROLLER_H

#include <string>
#include "sqlite3.h"

using namespace std;

class BookingManagerController{
public:
	BookingManagerController(sqlite3*);
	void findCustomer();
	void createCustomer();
	void editCustomer();
	void deleteCustomer();
	void checkNoFly();
	void bookingReport();
private:
	sqlite3* db;
	string userType;
};

#endif // BOOKINGMANAGERCONTROLLER_H
