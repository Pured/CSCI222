/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/



#include <iostream>
#include <fstream>
#include <sstream>
#include "GuestUI.h"
#include "Booking.h"
#include "Customer.h"
#include "CustomerProfileController.h"
#include "Seat.h"
#include "Aircraft.h"
#include "BookingController.h"
#include "sqlite3.h"
#include "clearscreen.h"

using namespace std;
ClearScreen cl; //For the clear screen function.

int main(int argc, char const *argv[])
{
    
    cl.clearScreen();
	// Open FlightDB database.
	sqlite3 *db;
	char *errMsg = 0;
	int err = sqlite3_open("FlightDB.db", &db);

	if (err != SQLITE_OK){
		cout << "Cannot access database.\n";
	}
	else{
		cout << "Connected to database.\n";
	}

	GuestUI gUI(db);
	bool end = false;

	//main loop
	while (end == false){
		end = gUI.run();
	}


	sqlite3_close(db); // Close FlightDB database.
    cl.clearScreen();
	return 0;
}
