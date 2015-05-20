/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#include "FlightManagerController.h"

FlightManagerController::FlightManagerController(sqlite3* d){
	db = d;
    userType = "FlightManager";
}

//-----Aircraft--------------------------------------------------

void FlightManagerController::findAircraft(){
	string id;

        cout<<"Input the aircraft's ID: ";
	cin >> id;

	cout << endl;

	string sqlCreate = "SELECT * FROM AIRCRAFT WHERE ID = '" + id + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, INSERVICE, FCLASS, BCLASS, PECLASS, ECLASS, TOTAL;
	const char *NAME;

	if (err != SQLITE_OK){
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

			INSERVICE = sqlite3_column_int(stmt, 2);
			FCLASS = sqlite3_column_int(stmt, 3);
			BCLASS = sqlite3_column_int(stmt, 4);
			PECLASS = sqlite3_column_int(stmt, 5);
			ECLASS = sqlite3_column_int(stmt, 6);
			TOTAL = sqlite3_column_int(stmt, 7);
  
			cout<<"ID: "<<ID<<"\nName: "<<NAME<<"\nIn Service: "<<INSERVICE<<"\nFirst Class: "<<FCLASS<<"\nBusiness Class: "<<BCLASS<<"\nWHAT IS PE CLASS!?!?: "<<PECLASS<<"\nEconomy Class: "<<ECLASS<<"\nTotal: "<<TOTAL<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void FlightManagerController::createAircraft(){

}

void FlightManagerController::editAircraft(){

}

void FlightManagerController::deleteAircraft(){

}

//-----Schedule--------------------------------------------------

void FlightManagerController::findSchedule(){
	string id;

        cout<<"Input the flight ID: ";
	cin >> id;

	cout << endl;

	string sqlCreate = "SELECT * FROM SCHEDULE WHERE FLIGHTID = '" + id + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, PLANE, ROUTE;
	const char *FLIGHTID;
	const char *DEPART;
	const char *ARRIVE;

	if (err != SQLITE_OK){
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			FLIGHTID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_int(stmt, 2);
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPART = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
			ARRIVE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
  
			cout<<"ID: "<<ID<<"\nFlight ID: "<<FLIGHTID<<"\nPlane: "<<PLANE<<"\nRoute: "<<ROUTE<<"\nDeparture: "<<DEPART<<"\nArrival: "<<ARRIVE<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void FlightManagerController::createSchedule(){

}

void FlightManagerController::editSchedule(){

}

void FlightManagerController::deleteSchedule(){

}

//-----Airport---------------------------------------------------

void FlightManagerController::findAirport(){
	string id;

        cout<<"Input the airport's ID: ";
	cin >> id;

	cout << endl;

	string sqlCreate = "SELECT * FROM AIRPORT WHERE ID = '" + id + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, ALTITUDE, TIMEZONE;
	float LATITUDE, LONGITUDE;
	const char *NAME;
	const char *CITY;
	const char *COUNTRY;
	const char *IATA;
	const char *DST;
	const char *TZ;

	if (err != SQLITE_OK){
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			CITY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			COUNTRY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			IATA = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

			LATITUDE = sqlite3_column_int(stmt, 5);
			LONGITUDE = sqlite3_column_int(stmt, 6);
			ALTITUDE = sqlite3_column_int(stmt, 7);
			TIMEZONE = sqlite3_column_int(stmt, 8);

			DST = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
			TZ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
  
			cout<<"ID: "<<ID<<"\nName: "<<NAME<<"\nCity: "<<CITY<<"\nCountry: "<<COUNTRY<<"\nWHAT IS IATA?!?!?: "<<IATA<<"\nLatitude: "<<LATITUDE<<"\nLongitude: "<<LONGITUDE<<"\nAltitude: "<<ALTITUDE<<"\nTimezone: "<<TIMEZONE<<"\nDaylight Saving Time: "<<DST<<"\nWHAT IS TZ?!?!?: "<<TZ<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void FlightManagerController::createAirport(){

}

void FlightManagerController::editAirport(){

}

void FlightManagerController::deleteAirport(){

}

//-----Route-----------------------------------------------------

void FlightManagerController::findRoute(){
	string src, dest;

        cout<<"Input the source location: ";
	cin >> src;

        cout<<"Input the destination location: ";
	cin >> dest;

	cout << endl;

	string sqlCreate = "SELECT * FROM ROUTE WHERE SRC = '" + src + "' AND DEST = '" + dest + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, STOPS;
	const char *SRC;
	const char *DEST;
	const char *CODESHARE;

	if (err != SQLITE_OK){
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			SRC = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			DEST = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			CODESHARE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

			STOPS = sqlite3_column_int(stmt, 4);

			//CHECK IF CODESHARE == "NULL"
				//CODESHARE = "n"
  
			cout<<"ID: "<<ID<<"\nSource: "<<SRC<<"\nDestination: "<<DEST<<"\nShared Code: "<<CODESHARE<<"\nStops: "<<STOPS<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void FlightManagerController::createRoute(){

}

void FlightManagerController::editRoute(){

}

void FlightManagerController::deleteRoute(){

}

//---------------------------------------------------------------

void FlightManagerController::flightReport(){
	cout << "-------- FLIGHT REPORT --------" << endl;
	cout << "Monthly Flight Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Flight Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
