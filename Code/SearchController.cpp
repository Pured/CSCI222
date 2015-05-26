/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include <string>
#include "SearchController.h"
#include "BookingController.h"
#include "ScheduleController.h"
#include "Route.h"
#include "Airport.h"

using namespace std;

SearchController::SearchController(sqlite3 *d){
	db = d;
	userType = "USERTYPE NOT SET";
}

void SearchController::setType(string user_type){
	userType = user_type;

	return;
}

string SearchController::getType(){
	return userType;
}

int SearchController::search(string user_type, string username){
	if(user_type == "Guest" || user_type == "Customer" || user_type == "none"){
		userType = user_type;
	}
	else{
		cout << "Error in search: invalid usertype.\n";

		return 1; // Invalid userType.
	}

	cout << "\n\t\t\tBOOK A FLIGHT\n\n";

	string fromDate = "", toDate = "", fromName = "", toName = "";

	Airport fromAirport(db);
	Airport toAirport(db);

	cin.ignore();
	bool correct = false;

	// Get input from user about departing airport.
	while(correct == false){
		cout << "Enter name of airport to leave from (type 'list' for airport list): ";
		getline(cin, fromName);

		if(fromName == "list"){
			fromAirport.alphabeticList();
		}
		else{
			string check = fromAirport.getByName(fromName);

			if(check == "FOUND"){
				correct = true;
			}
			else{
				cout << "Invalid airport selection. Try again." << endl;
			}
		}

	}

	//cin.ignore();
	//cout<<"here"<<endl;

	correct = false;
	while(correct == false){
		cout << "Enter name of airport to arrive at (type 'list' for airport list): ";
		getline(cin, toName);

		if(toName == "list"){
			toAirport.alphabeticList();
		}
		else{
			string check = toAirport.getByName(toName);

			if(check == "FOUND"){
				correct = true;
			}
			else{
				cout << "Invalid airport selection. Try again." << endl;
			}
		}
	}

	Route route(db);
	int routeCheck = route.getByAirports(fromAirport.getIATA(), toAirport.getIATA());

	if (routeCheck == -1){
		cout << "No route between " + fromAirport.getName() + " and " + toAirport.getName() + "available.\n";

		return 0;
	}

	cout << "Enter a date to search from (YYYY-MM-DD): ";
	cin >> fromDate;

	cout << "Enter a date to search to (YYYY-MM-DD): ";
	cin >> toDate;

	ScheduleController SC(db);
	int amtResults = 0;
	Schedule *results = SC.search(fromDate, toDate, amtResults, route.getID());

	cout << "Search found " << amtResults << " results.\n\n";

	if(amtResults > 0){
		if(userType == "Guest"){
			for(int i = 0; i < amtResults; i++){
				cout << "Flight " << results[i].getFlightID() << ": ";
				cout << results[i].getDepartDay() << " ";
				cout << results[i].getDepart() << " ";
				cout << results[i].getDepartTimezone() << endl;
			}
		}
		else if(userType == "Customer"){
			string userInput = "";

			for(int i = 0; i<amtResults; i++){
				cout << "ID: " << results[i].getID() << " ";
				cout << "Flight " << results[i].getFlightID() << ": ";
				cout << results[i].getDepartDay() << " ";
				cout << results[i].getDepart() << " ";
				cout << results[i].getDepartTimezone() << endl;
			}

			bool valid = false;
			int userChoiceIndex = -1; // Stores array index of users choice.

			while(valid == false){
				cout << "Please choose a flight to book (Enter ID): ";
				cin >> userInput;

				for(int i = 0; i < amtResults; i++){
					if(atoi(userInput.c_str()) == results[i].getID()){
						userChoiceIndex = i;
						valid = true;
						i = amtResults;
					}
				}

				if(valid == false){
					cout << "Invalid input. Please enter an ID from the list.\n";
				}
			}

			// Start booking.
			BookingController BC(db);
			BC.makeBooking(userType, username, atoi(userInput.c_str()));
		}

		delete[] results;
		results = NULL;
	}

	return 0;
}
