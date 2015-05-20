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



//#include "classes.h"
//#include "database.h"
//#include "flights.h"
//#include "permissions.h"
//#include "userInterface.h"

using namespace std;

int main(int argc, char const *argv[])
{
	
	//Open FlightDB database
	sqlite3 *db;
	char *errMsg = 0;
	int err = sqlite3_open("FlightDB.db", &db); 

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
	
	
	/*
	Booking b(db);
	int resultAmount = -1;
	Booking* results = b.getByEmail("a",resultAmount);
	for(int i = 0; i<resultAmount; i++){
		cout<<results[0].getCustEmail()<<endl;
	}
	//cout<<results[0].getCustEmail()<<endl;
	*/
	
	
	//close FlightDB database.
	sqlite3_close(db);
	return 0;
}
