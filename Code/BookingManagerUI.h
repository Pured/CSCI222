/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Connected the UI to the Controller.
|==============================================================*/

#ifndef BOOKINGMANAGERUI_H
#define BOOKINGMANAGERUI_H

#include <string>
#include "sqlite3.h"

using namespace std;

class BookingManagerUI{
public:
	BookingManagerUI(sqlite3*);

	bool run();
	void customerAccessMenu();
private:
	sqlite3* db;
	string userType;
};

#endif // BOOKINGMANAGERUI_H
