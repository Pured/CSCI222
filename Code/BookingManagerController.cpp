/*=============================================================
| Modified by: as277
| Version: 1.03
| Modification: added find total bookings
|==============================================================*/

#include <iostream>
#include <sstream>
#include "BookingManagerController.h"
#include "Customer.h"

using namespace std;

BookingManagerController::BookingManagerController(sqlite3 *d){
	db = d;
	userType = "BookingManager";
}

void BookingManagerController::checkNoFly(){
	string sqlCreate = "SELECT * FROM CUSTOMER WHERE STATUS IS NOT '';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Create variables to store data.
	int ID;
	const char *TITLE, *FNAME, *LNAME, *EMAIL, *NOFLY;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from db.
			ID = sqlite3_column_int(stmt, 0); // Store column 1.

			TITLE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)); // Store column 2.
			FNAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)); // Store column 3.
			LNAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)); // Store column 4.
			EMAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)); // Store column 8.
			NOFLY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 16)); // Store column 17.

			cout << "ID: " << ID << "\nName: " << TITLE << ". " << FNAME << " " << LNAME << "\nUsername: " << EMAIL << "\nNo-Fly Status: " << NOFLY << endl << endl;
		}
	}

	sqlite3_finalize(stmt); // Deletes prepared statement.
}

void BookingManagerController::bookingReport(){
	cout << "-------- BOOKING REPORT --------" << endl;
	cout << "Monthly Booking Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Booking Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
