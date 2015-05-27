/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Removed customerAccessMenu().
|==============================================================*/

#ifndef BOOKINGMANAGERUI_H_
#define BOOKINGMANAGERUI_H_

#include <string>
#include "sqlite3.h"

class BookingManagerUI{
public:
	BookingManagerUI(sqlite3 *);

	bool run();

private:
	sqlite3 *db;
	std::string userType;
};

#endif // BOOKINGMANAGERUI_H_
