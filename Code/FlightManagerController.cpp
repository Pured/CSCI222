/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include "FlightManagerController.h"
#include "Aircraft.h"
#include <string>

using namespace std;

FlightManagerController::FlightManagerController(sqlite3 *d){
	db = d;
    userType = "FlightManager";
}

//-----Aircraft--------------------------------------------------

void FlightManagerController::findAircraft(){
	string id;

	cout << "Input the aircraft's ID: ";
	cin >> id;

	cout << endl;

	// DO FINDING...
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::createAircraft(){
	Aircraft ac(db);
	string NAME = "", INSt = "", FCt = "", BCt = "", PECt = "", ECt = "";
	int INS = 0, FC = 0, BC = 0, PEC = 0, EC = 0;

	cin.ignore();

	cout << "Creating new aircraft..." << endl;
	cout << "Name: ";
	getline(cin, NAME);
	ac.setName(NAME);

	cin.clear();
	cout << "Amount in service: ";
	cin >> INSt;
	INS = atoi(INSt.c_str());
	ac.setInService(INS);

	cout << "Amount of First Class: ";
	cin >> FCt;
	FC = atoi(FCt.c_str());
	ac.setFClass(FC);

	cout << "Amount of Business Class: ";
	cin >> BCt;
	BC = atoi(BCt.c_str());
	ac.setBClass(BC);

	cout << "Amount of Premium Economy class: ";
	cin >> PECt;
	PEC = atoi(PECt.c_str());
	ac.setPEClass(PEC);

	cout << "Amount of Economy class: ";
	cin >> ECt;
	EC = atoi(ECt.c_str());
	ac.setEClass(EC);

	ac.createAircraft();
}

void FlightManagerController::editAircraft(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::deleteAircraft(){
	string inputTemp;
	int aID;

	cout << "Input Aircraft ID: ";
	cin >> inputTemp;

	aID = atoi(inputTemp.c_str());

	Aircraft ac(db);
	ac.getByID(inputTemp);
	ac.deleteAircraft();
}

//-----Schedule--------------------------------------------------

void FlightManagerController::findSchedule(){
	string id;

	cout << "Input the flight ID: ";
	cin >> id;

	cout << endl;

	// DO FINDING...
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::createSchedule(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::editSchedule(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::deleteSchedule(){
	cout << "NOT IMPLEMENTED!\n\n";
}

//-----Airport---------------------------------------------------

void FlightManagerController::findAirport(){
	string id;

	cout << "Input the airport's ID: ";
	cin >> id;

	cout << endl;
}

void FlightManagerController::createAirport(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::editAirport(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::deleteAirport(){
	cout << "NOT IMPLEMENTED!\n\n";
}

//-----Route-----------------------------------------------------

void FlightManagerController::findRoute(){
	string src, dest;

	cout << "Input the source location: ";
	cin >> src;

	cout << "Input the destination location: ";
	cin >> dest;

	cout << endl;

	string sqlCreate = "SELECT * FROM ROUTE WHERE SRC = '" + src + "' AND DEST = '" + dest + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Create variables to store data.
	int ID, STOPS;
	const char *SRC, *DEST, *CODESHARE;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from DB.
			ID = sqlite3_column_int(stmt, 0);

			SRC = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			DEST = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			CODESHARE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

			STOPS = sqlite3_column_int(stmt, 4);

			//CHECK IF CODESHARE == "NULL"
				//CODESHARE = "n"

			cout << "ID: " << ID << "\nSource: " << SRC << "\nDestination: " << DEST << "\nShared Code: " << CODESHARE << "\nStops: " << STOPS << endl << endl;
		}
	}

	sqlite3_finalize(stmt);
}

void FlightManagerController::createRoute(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::editRoute(){
	cout << "NOT IMPLEMENTED!\n\n";
}

void FlightManagerController::deleteRoute(){
	cout << "NOT IMPLEMENTED!\n\n";
}

//---------------------------------------------------------------

void FlightManagerController::flightReport(){
	cout << "-------- FLIGHT REPORT --------" << endl;
	cout << "Monthly Flight Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Flight Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
