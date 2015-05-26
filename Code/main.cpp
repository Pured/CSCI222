/*=============================================================
| Modified by: kb100
| Version: 1.00
| Description: The main file.
|==============================================================*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "sqlite3.h"
#include "GuestUI.h"

#include "Booking.h"
#include "Customer.h"
#include "CustomerProfileController.h"



#include "Seat.h"
#include "Aircraft.h"
#include "BookingController.h"
#include "WeatherController.h"
#include "Airport.h"

using namespace std;

int main(int argc, char const *argv[])
{
    system("clear");
	
	//Open FlightDB database
	sqlite3 *db;
	char *errMsg = 0;
	int err = sqlite3_open("FlightDB.db", &db);
	//int err = sqlite3_open_v2("FlightDB.db", &db, SQLITE_OPEN_READWRITE, "");

	if(err != SQLITE_OK){
		cout<<"Cannot access database"<<endl;
	}
	else{
		cout<<"Connected to database."<<endl;	
	}



	
	
	GuestUI gUI(db);
	bool end = false;
	
	//main loop
	while (end == false){
		end = gUI.run();
	}
	




	//close FlightDB database.
	sqlite3_close(db);
	return 0;
}
