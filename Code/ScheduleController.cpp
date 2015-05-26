/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "ScheduleController.h"
#include "sqlite3.h"

using namespace std;

// Constructors.
ScheduleController::ScheduleController(sqlite3 *d){
	db = d;
}

Schedule *ScheduleController::search(string from, string to, int &resSize, int route){
	Schedule *temp; // Temporary pointer for Schedule array.
	stringstream convert;

	convert << route;

	string convRoute = convert.str();
	convert.str(string()); // Clear ss.

	string sqlCreate = "SELECT COUNT(ID) FROM SCHEDULE WHERE DEPARTDATE >= Datetime('" + from + "') AND DEPARTDATE <= Datetime('" + to + "')" + " AND ROUTE=" + convRoute + ";"; // Count amount of results from date query to be used to create dynamic array.

	const char *sql = sqlCreate.c_str();
	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	int querySize = 0; // Temp int to store amt results.
	
	// Execute count query.
	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			querySize = sqlite3_column_int(stmt, 0);
		}
	}

	resSize = querySize; // Assign referenced variable the size of dynamic array.
	sqlite3_finalize(stmt);

	temp = new Schedule[querySize]; // Create dynamic array for query results.

	sqlCreate = "SELECT * FROM SCHEDULE WHERE DEPARTDATE >= Datetime('" + from + "') AND DEPARTDATE <= Datetime('" + to + "')" + " AND ROUTE=" + convRoute + " ORDER BY DEPARTDATE ASC;";
	sql = sqlCreate.c_str();
	err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Temporary variables for database retreival.
	int FID = -1, PLANE = 0, ROUTE = 0;
	const char *FLIGHTID, *DEPARTDAY, *DEPART, *DEPARTTZ, *ARRIVEDAY, *ARRIVE, *ARRIVETZ;
	
	int i = 0;

	// Execute date query.
	if(err != SQLITE_OK){
	cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get attributes from database.
			FID = sqlite3_column_int(stmt, 0);

            FLIGHTID = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_int(stmt, 2);
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPARTDAY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
			DEPART = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
			DEPARTTZ = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
			ARRIVEDAY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
			ARRIVE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
			ARRIVETZ = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));

			// Set attributes to Schedule objects in array.
			temp[i].setDB(db);
			temp[i].setID(FID);
			temp[i].setFlightID(string(FLIGHTID));
			temp[i].setPlane(PLANE);
			temp[i].setRoute(ROUTE);
			temp[i].setDepartDay(string(DEPARTDAY));
			temp[i].setDepart(string(DEPART));
			temp[i].setDepartTimezone(string(DEPARTTZ));
			temp[i].setArriveDay(string(ARRIVEDAY));
			temp[i].setArrive(string(ARRIVE));
			temp[i].setArriveTimezone(string(ARRIVE));

			i++;
		}
	}

	return temp; // Return reference to Schedule array.
}
