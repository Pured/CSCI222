/*=============================================================
| Modified by: djm749
| Version: 1.04
| Modification: Added weather mechanic
|==============================================================*/

#include <iostream>
#include "FlightManagerUI.h"
#include "FlightManagerController.h"
//#include "WeatherController.h"
#include <string>

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
		cout << "Please choose an option:\n\n";
		cout << "1) Access aircrafts.\n";
		cout << "2) Access schedules.\n";
		cout << "3) Access airports.\n";
		cout << "4) Access routes.\n";
		cout << "5) Access flight reports.\n";
		cout << "0) Log out.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			accessAircraftsMenu();
		}
		else if(input == "2"){
			accessSchedulesMenu();
		}
		else if(input == "3"){
			accessAirportsMenu();
		}
		else if(input == "4"){
			accessRoutesMenu();
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

void FlightManagerUI::airportWeatherMenu(){
	/*
	WeatherController WC(db);

	string input = "-1";

	cout << "\n";
	cin.ignore();

	Airport A(db);
	while (input != "0"){
		cout << "Enter an airport name (Enter 'list' for airport list): ";
		getline(cin, input);

		if (input == "list"){
			A.alphabeticList();
		}
		else{
			std::string check = A.getByName(input);
			if (check == "FOUND"){
				//all good
				cout << "\t" + A.getName() + " Airport Weather\n";
				WC.getAirportWeather(A);
				cout << "\n";
				input = "0";
			}
			else{
				cout << input << endl;
				cout << "Invalid Airport name. try again.\n" << endl;
			}

		}
	}
	*/
	
}
