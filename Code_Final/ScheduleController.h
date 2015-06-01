/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef SCHEDULECONTROLLER_H_
#define SCHEDULECONTROLLER_H_

#include "Schedule.h"
#include "sqlite3.h"

class ScheduleController{
public:
	// Constructors.
	ScheduleController(sqlite3 *d);
	Schedule *search(std::string from, std::string to, int &resSize, int route); // 2 dates as strings (YYYY-MM-DD), int to store amt results.

private:
	sqlite3 *db;
};

#endif // SCHEDULECONTROLLER_H_
