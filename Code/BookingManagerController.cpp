/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
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

	//create variables to store data.
	int ID;
	const char *TITLE, *FNAME, *LNAME, *EMAIL, *NOFLY;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from db.
			ID = sqlite3_column_int(stmt, 0);

			TITLE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			FNAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			LNAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
			EMAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
			NOFLY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 16));

			cout << "ID: " << ID << "\nName: " << TITLE << ". " << FNAME << " " << LNAME << "\nUsername: " << EMAIL << "\nNo-Fly Status: " << NOFLY << endl << endl;
		}
	}

	sqlite3_finalize(stmt);
}

void BookingManagerController::bookingReport(){
	cout << "-------- BOOKING REPORT --------" << endl;
	cout << "Monthly Booking Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Booking Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
