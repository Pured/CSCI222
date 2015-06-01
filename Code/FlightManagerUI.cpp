/*=============================================================
| Modified by: kb100
| Version: 1.05
| Modification: Modified the code order. 
|==============================================================*/

#include <iostream>
#include <string>
#include "FlightManagerUI.h"
#include "FlightManagerController.h"
//#include "WeatherController.h"

using namespace std;

FlightManagerUI::FlightManagerUI(sqlite3 *d){
	db = d;
    userType = "FlightManager";
}

bool FlightManagerUI::run(){
	FlightManagerController fmc(db);
	string input = "-1";

	cout << endl;

	while(input != "0"){
		cout << "\t\t\tFLIGHT MANAGER HOME\n\n";
        getNotification();  //check for notifications, output them
		cout << "Please choose an option:\n\n";
		cout << "1) Access aircrafts.\n";
		cout << "2) Access airports.\n";
		cout << "3) Access routes.\n";
		cout << "4) Access schedules.\n";
		cout << "5) Access flight reports.\n";
		cout << "0) Log out.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			accessAircraftsMenu();
		}
		else if(input == "2"){
			accessAirportsMenu();
		}
		else if(input == "3"){
			accessRoutesMenu();
		}
		else if(input == "4"){
			accessSchedulesMenu();
		}
		else if(input == "5"){
			fmc.flightReport();
		}
		else if(input == "0"){
			return 1;
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}

    return 0;
}

void FlightManagerUI::accessAircraftsMenu(){
	FlightManagerController fmc(db);
	string input = "-1";

	cout << endl;

	while(input != "0"){
		cout << "Customer Access Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Search for an aircraft.\n";
		cout << "2) Add a new aircraft.\n";
		cout << "3) Edit an aircraft.\n";
		cout << "4) Remove an aircraft.\n";
		cout << "0) Return to main menu.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			fmc.findAircraft();
		}
		else if(input == "2"){
			fmc.createAircraft();
		}
		else if(input == "3"){
			fmc.editAircraft();
		}
		else if(input == "4"){
			fmc.deleteAircraft();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid input\n\n";
		}
	}
}

void FlightManagerUI::accessAirportsMenu(){
	FlightManagerController fmc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout << "Customer Access Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Search for an airport.\n";
		cout << "2) Add a new airport.\n";
		cout << "3) Edit an airport.\n";
		cout << "4) Remove an airport.\n";
		cout << "5) Check airport weather.\n";
		cout << "0) Return to main menu.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			fmc.findAirport();
		}
		else if(input == "2"){
			fmc.createAirport();
		}
		else if(input == "3"){
			fmc.editAirport();
		}
		else if(input == "4"){
			fmc.deleteAirport();
		}
		else if (input == "5"){
			airportWeatherMenu();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}
}

void FlightManagerUI::accessRoutesMenu(){
	FlightManagerController fmc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout << "Customer Access Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Search for a route.\n";
		cout << "2) Add a new route.\n";
		cout << "3) Edit a route.\n";
		cout << "4) Remove a route.\n";
		cout << "0) Return to main menu.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			fmc.findRoute();
		}
		else if(input == "2"){
			fmc.createRoute();
		}
		else if(input == "3"){
			fmc.editRoute();
		}
		else if(input == "4"){
			fmc.deleteRoute();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}
}

void FlightManagerUI::accessSchedulesMenu(){
	FlightManagerController fmc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout << "Customer Access Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Search for a schedule.\n";
		cout << "2) Add a new schedule.\n";
		cout << "3) Edit a schedule.\n";
		cout << "4) Remove a schedule.\n";
		cout << "0) Return to main menu.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			fmc.findSchedule();
		}
		else if(input == "2"){
			fmc.createSchedule();
		}
		else if(input == "3"){
			fmc.editSchedule();
		}
		else if(input == "4"){
			fmc.deleteSchedule();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}
}

void FlightManagerUI::airportWeatherMenu(){
/*
	WeatherController WC(db);

	string input = "-1";

	cout << endl;
	cin.ignore();

	Airport A(db);
	while(input != "0"){
		cout << "Enter an airport name (Enter 'list' for airport list): ";
		getline(cin, input);

		if(input == "list"){
			A.alphabeticList();
		}
		else{
			std::string check = A.getByName(input);
			if(check == "FOUND"){
				//all good
				cout << "\t" + A.getName() + " Airport Weather\n";
				WC.getAirportWeather(A);

				cout << endl;

				input = "0";
			}
			else{
				cout << input << endl;
				cout << "Invalid Airport name. try again.\n\n";
			}
		}
	}
*/
}

void FlightManagerUI::getNotification(){
    
    string user = "FLIGHTMANAGER";  //assign user type
    
	string sqlCreate = "SELECT MESSAGE FROM NOTIFICATION WHERE USERTYPE = '+user+'";
	const char *sql = sqlCreate.c_str();
    
	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
	//create variables to store data.
	const char *USERTYPE, *MESSAGE;
    
	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from DB.
            
			USERTYPE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			MESSAGE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            
            if(MESSAGE == "")
            {
                cout << "You have no messages to be displayed." << endl;
            }else
                cout << MESSAGE << endl;
		}
	}
    
	sqlite3_finalize(stmt);
}