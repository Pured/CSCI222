/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifdef __linux__
void clearScreen(){
    system("clear");
}
#endif
#ifdef _WIN32
void clearScreen(){
    system("cls");
}
#endif

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

using namespace std;

int main(int argc, char const *argv[])
{
#ifdef __linux__
    clearScreen();
#endif
#ifdef _WIN32
    clearScreen();
#endif
    
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

	return 0;
}
