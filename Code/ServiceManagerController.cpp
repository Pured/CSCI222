/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Implemented the create/update/delete functions.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "ServiceManagerController.h"
#include "ServiceItem.h"

using namespace std;

ServiceManagerController::ServiceManagerController(sqlite3 *d){
	db = d;
    userType = "ServiceManager";
}

void ServiceManagerController::findFlight(){
	string fc;

	cout << "Input the flight code: ";
	cin >> fc;

	cout << endl;

	string sqlCreate = "SELECT * FROM SCHEDULE WHERE FLIGHTID = '" + fc + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Create variables to store data.
	int ID, PLANE, ROUTE;
	const char *FLIGHTID, *DEPART, *ARRIVE;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from db.
			ID = sqlite3_column_int(stmt, 0);

			FLIGHTID = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_double(stmt, 2);	
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPART = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
			ARRIVE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
  
			cout << "ID: " << ID << "\nFlight Code: " << FLIGHTID << "\nPlane: " << PLANE << "\nRoute: " << ROUTE << "\nDeparture: " << DEPART << "\nArrival: " << ARRIVE << endl << endl;
		}
	}

	sqlite3_finalize(stmt);
}

void ServiceManagerController::findService(){
	string fc;

	cout << "Input the flight code: ";
	cin >> fc;

	cout << endl;

	string sqlCreate = "SELECT * FROM SCHEDULE WHERE FLIGHTID = '" + fc + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Create variables to store data.
	int ID, PLANE, ROUTE;
	const char *FLIGHTID, *DEPART, *ARRIVE;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from db.
			ID = sqlite3_column_int(stmt, 0);

			FLIGHTID = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_double(stmt, 2);	
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPART = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
			ARRIVE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));

			cout << "ID: " << ID << "\nFlight Code: " << FLIGHTID << "\nPlane: " << PLANE << "\nRoute: " << ROUTE << "\nDeparture: " << DEPART << "\nArrival: " << ARRIVE << endl << endl;
		}
	}

	sqlite3_finalize(stmt);
}

void ServiceManagerController::createService(){
	ServiceItem si(db);
	string ITEM = "", AVAIL = "", COSTt = "";
	float COST = 0;

	cin.ignore();

	cout << "Creating new service item...\n";

	cout << "Item: ";
	getline(cin, ITEM);
	si.setItem(ITEM);

	cin.clear();

	cout << "Cost: ";
	cin >> COSTt;
	COST = atoi(COSTt.c_str());
	si.setCost(COST);

	cout << "Availability: ";
	getline(cin, AVAIL);
	si.setAvail(AVAIL);

	si.createServiceItem();
}

void ServiceManagerController::editService(){
	ServiceItem si(db);
	string id;

	cout << "Input the ID of the service item you wish to change: ";
	cin >> id;

	si.getByID(id);

	string input = "-1";
	string change = "";
	float cost = 0;

	while(input != "0"){
		cout << "Service Item Edit Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Edit item name.\n";
		cout << "2) Edit cost.\n";
		cout << "3) Edit availability.\n";
		cout << "0) Return to previous menu.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cin.ignore();
			cout << "New item name: ";
			getline(cin, change);
			si.setItem(change);
		}
		else if(input == "2"){
			cin.ignore();
			cout << "New cost: ";
			cin >> cost;
			si.setCost(cost);
		}
		else if(input == "3"){
			cin.ignore();
			cout << "New availability: ";
			getline(cin, change);
			si.setAvail(change);
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid Input.\n\n";
		}
	}

	si.updateServiceItem();
}

void ServiceManagerController::deleteService(){
	string id;
	ServiceItem si(db);

	cout << "Input the ID of the service item you wish to delete: ";
	cin >> id;

	si.getByID(id);
	si.deleteServiceItem();
}

void ServiceManagerController::serviceReport(){
	cout << "-------- SERVICE REPORT --------\n";
	cout << "Monthly Service Summary:\n";
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Service Summary:\n";
	cout << "Will implement after date class is ready.\n\n";
}
