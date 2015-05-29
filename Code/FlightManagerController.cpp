/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Implemented all of the create/update/delete functions.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include <string>
#include "FlightManagerController.h"
#include "Aircraft.h"
#include "Airport.h"
#include "Route.h"
#include "Schedule.h"

using namespace std;

FlightManagerController::FlightManagerController(sqlite3 *d){
	db = d;
    userType = "FlightManager";
}

//-----Aircraft--------------------------------------------------

void FlightManagerController::findAircraft(){
	Aircraft ac(db);
	string id;

	cout << "Input the aircraft's ID: ";
	cin >> id;

	ac.getByID(id);

	cout << ac << endl << endl;
}

void FlightManagerController::createAircraft(){
	Aircraft ac(db);
	string NAME = "", INSt = "", FCt = "", BCt = "", PECt = "", ECt = "";
	int INS = 0, FC = 0, BC = 0, PEC = 0, EC = 0;

	cin.ignore();

	cout << "Creating new aircraft...\n";

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
	Aircraft ac(db);
	string id;

	cout << "Input the ID of the plane you wish to change: ";
	cin >> id;

	ac.getByID(id);

	string input = "-1";
	string change = "";
	int inService = 0, fClass = 0, bClass = 0, peClass = 0, eClass = 0, total;

	while(input != "0"){
		cout << "Aircraft Edit Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Edit name.\n";
		cout << "2) Edit how many seats are in service.\n";
		cout << "3) Edit how many seats are in first class.\n";
		cout << "4) Edit how many seats are in business class.\n";
		cout << "5) Edit how many seats are in premium economy class.\n";
		cout << "6) Edit how many seats are in economy class.\n";
		cout << "0) Return to previous menu.\n\n";
		cout << "Your Choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cin.ignore();
			cout << "New name: ";
			getline(cin, change);
			ac.setName(change);
		}
		else if(input == "2"){
			cin.ignore();
			cout << "New in service amount: ";
			cin >> inService;
			ac.setInService(inService);
		}
		else if(input == "3"){
			cin.ignore();
			cout << "New first class amount: ";
			cin >> fClass;
			ac.setFClass(fClass);
			ac.setTotalSeats(); // Needs to update the total seats after changing one class.
		}
		else if(input == "4"){
			cin.ignore();
			cout << "New business class amount: ";
			cin >> bClass;
			ac.setBClass(bClass);
			ac.setTotalSeats(); // Needs to update the total seats after changing one class.
		}
		else if(input == "5"){
			cin.ignore();
			cout << "New premium economy class amount: ";
			cin >> peClass;
			ac.setPEClass(peClass);
			ac.setTotalSeats(); // Needs to update the total seats after changing one class.
		}
		else if(input == "6"){
			cin.ignore();
			cout << "New economy class amount: ";
			cin >> eClass;
			ac.setEClass(eClass);
			ac.setTotalSeats(); // Needs to update the total seats after changing one class.
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid Input\n\n";
		}
	}

	ac.updateAircraft();
}

void FlightManagerController::deleteAircraft(){
	string id;
	Aircraft ac(db);

	cout << "Input the ID of the aircraft you wish to delete: ";
	cin >> id;

	ac.getByID(id);
	ac.deleteAircraft();
}

//-----Airport---------------------------------------------------

void FlightManagerController::findAirport(){
	Airport ap(db);
	string iata;

	cout << "Input the airport's Iata: ";
	cin >> iata;

	ap.getByIata(iata);

	cout << ap << endl << endl;
}

void FlightManagerController::createAirport(){
	Airport ap(db);

	string NAME = "", CITY = "", COUNTRY = "", IATA = "", TZ = "", ALTITUDEt = "", TIMEZONEt = "", LATITUDEt = "", LONGITUDEt = "";
	int ALTITUDE = 0, TIMEZONE = 0;
	float LATITUDE = 0, LONGITUDE = 0;
	char DST = NULL;

	cin.ignore();

	cout << "Creating new airport...\n";

	cout << "Name: ";
	getline(cin, NAME);
	ap.setName(NAME);

	cout << "City: ";
	getline(cin, CITY);
	ap.setCity(CITY);

	cout << "Country: ";
	getline(cin, COUNTRY);
	ap.setCountry(COUNTRY);

	cout << "Iata: ";
	getline(cin, IATA);
	ap.setIATA(IATA);

	cin.clear();

	cout << "Latitude: ";
	cin >> LATITUDEt;
	LATITUDE = atof(LATITUDEt.c_str());
	ap.setLat(LATITUDE);

	cout << "Longitude: ";
	cin >> LONGITUDEt;
	LONGITUDE = atof(LONGITUDEt.c_str());
	ap.setLong(LONGITUDE);

	cout << "Altitude: ";
	cin >> ALTITUDEt;
	ALTITUDE = atof(ALTITUDEt.c_str());
	ap.setAlt(ALTITUDE);

	cout << "Timezone: ";
	cin >> TIMEZONEt;
	TIMEZONE = atof(TIMEZONEt.c_str());
	ap.setTimezone(TIMEZONE);

	cout << "Daylight savings time: ";
	cin >> DST;
	ap.setDST(DST);

	cin.ignore();

	cout << "TZ: ";
	getline(cin, TZ);
	ap.setTZ(TZ);

	cout << endl;

	ap.createAirport();
}

void FlightManagerController::editAirport(){
	Airport ap(db);
	string tempIata;

	cout << "Input the Iata of the airport you wish to edit: ";
	cin >> tempIata;

	ap.getByIata(tempIata);

	string input = "-1";
	string change = "";
	int tempAltitude = 0, tempTimezone = 0;
	float tempLatitude = 0, tempLongitude = 0;
	char tempDst = NULL;

	while(input != "0"){
		cout << "Airport Edit Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Edit name.\n";
		cout << "2) Edit city.\n";
		cout << "3) Edit country.\n";
		cout << "4) Edit iata.\n";
		cout << "5) Edit latitude.\n";
		cout << "6) Edit longitude.\n";
		cout << "7) Edit altitude.\n";
		cout << "8) Edit timezone.\n";
		cout << "9) Edit Daylight savings time.\n";
		cout << "10) Edit tz.\n";
		cout << "0) Return to previous menu.\n\n";
		cout << "Your Choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cin.ignore();
			cout << "New name: ";
			getline(cin, change);
			ap.setName(change);
		}
		else if(input == "2"){
			cin.ignore();
			cout << "New city: ";
			getline(cin, change);
			ap.setCity(change);
		}
		else if(input == "3"){
			cin.ignore();
			cout << "New country: ";
			getline(cin, change);
			ap.setCountry(change);
		}
		else if(input == "4"){
			cin.ignore();
			cout << "New iata: ";
			getline(cin, change);
			ap.setIATA(change);
		}
		else if(input == "5"){
			cin.ignore();
			cout << "New latitude: ";
			cin >> tempLatitude;
			ap.setLat(tempLatitude);
		}
		else if(input == "6"){
			cin.ignore();
			cout << "New longitude: ";
			cin >> tempLongitude;
			ap.setLong(tempLongitude);
		}
		else if(input == "7"){
			cin.ignore();
			cout << "New altitude: ";
			cin >> tempAltitude;
			ap.setAlt(tempAltitude);
		}
		else if(input == "8"){
			cin.ignore();
			cout << "New timezone: ";
			cin >> tempTimezone;
			ap.setTimezone(tempTimezone);
		}
		else if(input == "9"){
			cin.ignore();
			cout << "New DST: ";
			cin >> tempDst;
			ap.setDST(tempDst);
		}
		else if(input == "10"){
			cin.ignore();
			cout << "New tz: ";
			getline(cin, change);
			ap.setTZ(change);
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid Input\n\n";
		}
	}

	ap.updateAirport();
}

void FlightManagerController::deleteAirport(){
	string inputTemp;
	Airport ap(db);

	cout << "Input the iata of the airport you wish to delete: ";
	cin >> inputTemp;

	ap.getByIata(inputTemp);
	ap.deleteAirport();
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

			cout << "ID: " << ID << "\nSource: " << SRC << "\nDestination: " << DEST << "\nShared Code: " << CODESHARE << "\nStops: " << STOPS << endl << endl;
		}
	}

	sqlite3_finalize(stmt);
}

void FlightManagerController::createRoute(){
	Route r(db);

	string SRC = "", DEST = "", STOPSt = "";
	int STOPS = 0;
	char CODESHARE = NULL;

	cin.ignore();

	cout << "Creating new route...\n";

	cout << "Source: ";
	getline(cin, SRC);
	r.setSrc(SRC);

	cout << "Destination: ";
	getline(cin, DEST);
	r.setDest(DEST);

	cin.clear();

	cout << "Codeshare: ";
	cin >> CODESHARE;
	r.setCodeshare(CODESHARE);

	cin.clear();

	cout << "Number of stops: ";
	cin >> STOPSt;
	STOPS = atoi(STOPSt.c_str());
	r.setStops(STOPS);

	cout << endl;

	r.createRoute();
}

void FlightManagerController::editRoute(){
	Route r(db);
	int id;

	cout << "Input the ID of the route you wish to change: ";
	cin >> id;

	r.getByID(id);

	string input = "-1";
	string change = "";
	int tempStops = 0;
	char tempCodeshare = NULL;

	while(input != "0"){
		cout << "Route Edit Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Edit source location.\n";
		cout << "2) Edit destination location.\n";
		cout << "3) Edit shared code.\n";
		cout << "4) Edit number of stops.\n";
		cout << "0) Return to previous menu.\n\n";
		cout << "Your Choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cin.ignore();
			cout << "New source location: ";
			getline(cin, change);
			r.setSrc(change);
		}
		else if(input == "2"){
			cin.ignore();
			cout << "New destination location: ";
			getline(cin, change);
			r.setDest(change);
		}
		else if(input == "3"){
			cin.ignore();
			cout << "New shared code: ";
			cin >> tempCodeshare;
			r.setCodeshare(tempCodeshare);
		}
		else if(input == "4"){
			cin.ignore();
			cout << "New number of stops: ";
			cin >> tempStops;
			r.setStops(tempStops);
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid Input\n\n";
		}
	}

	r.updateRoute();
}

void FlightManagerController::deleteRoute(){
	int id;
	Route r(db);

	cout << "Input the ID of the route you wish to delete: ";
	cin >> id;

	r.getByID(id);
	r.deleteRoute();
}

//-----Schedule--------------------------------------------------

void FlightManagerController::findSchedule(){
	Schedule s(db);
	int id;

	cout << "Input the schedule's ID: ";
	cin >> id;

	s.getByID(id);

	cout << s << endl << endl;
}

void FlightManagerController::createSchedule(){
	Schedule s(db);
	string FLIGHTID = "", DEPARTDAY = "", DEPART = "", DEPARTTIMEZONE = "", ARRIVEDAY = "", ARRIVE = "", ARRIVETIMEZONE = "", PLANEt = "", ROUTEt = "";
	int PLANE = 0, ROUTE = 0;

	cin.ignore();

	cout << "Creating new flight...\n";

	cout << "Flight ID: ";
	getline(cin, FLIGHTID);
	s.setFlightID(FLIGHTID);

	cin.clear();

	cout << "Plane ID: ";
	cin >> PLANEt;
	PLANE = atoi(PLANEt.c_str());
	s.setPlane(PLANE);

	cout << "Route ID: ";
	cin >> ROUTEt;
	ROUTE = atoi(ROUTEt.c_str());
	s.setRoute(ROUTE);

	cin.ignore();

	cout << "Day of departure: ";
	getline(cin, DEPARTDAY);
	s.setDepartDay(DEPARTDAY);

	cout << "Date of departure: ";
	getline(cin, DEPART);
	s.setDepart(DEPART);

	cout << "Timezone of departing airport: ";
	getline(cin, DEPARTTIMEZONE);
	s.setDepartTimezone(DEPARTTIMEZONE);

	cout << "Day of arrival: ";
	getline(cin, ARRIVEDAY);
	s.setArriveDay(ARRIVEDAY);

	cout << "Date of arrival: ";
	getline(cin, ARRIVE);
	s.setArrive(ARRIVE);

	cout << "Timezone of arriving airport: ";
	getline(cin, ARRIVETIMEZONE);
	s.setArriveTimezone(ARRIVETIMEZONE);

	s.createSchedule();
}

void FlightManagerController::editSchedule(){
	Schedule s(db);
	int id;

	cout << "Input the ID of the schedule you wish to change: ";
	cin >> id;

	s.getByID(id);

	string input = "-1";
	string change = "";
	int plane = 0, route = 0;

	while(input != "0"){
		cout << "Schedule Edit Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Edit flight ID.\n";
		cout << "2) Change plane.\n";
		cout << "3) Change route.\n";
		cout << "4) Edit departure date.\n";
		cout << "5) Edit arrival date.\n";
		cout << "0) Return to previous menu.\n\n";
		cout << "Your Choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cin.ignore();
			cout << "New flight ID: ";
			getline(cin, change);
			s.setFlightID(change);
		}
		else if(input == "2"){
			cin.ignore();
			cout << "New plane ID: ";
			cin >> plane;
			s.setPlane(plane);
		}
		else if(input == "3"){
			cin.ignore();
			cout << "New route ID: ";
			cin >> route;
			s.setRoute(route);
		}
		else if(input == "4"){
			cin.ignore();
			cout << "New departure date: ";
			getline(cin, change);
			s.setDepart(change);
		}
		else if(input == "5"){
			cin.ignore();
			cout << "New arrival date: ";
			getline(cin, change);
			s.setArrive(change);
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid Input\n\n";
		}
	}

	s.updateSchedule();
}

void FlightManagerController::deleteSchedule(){
	int id;
	Schedule s(db);

	cout << "Input the ID of the schedule you wish to delete: ";
	cin >> id;

	s.getByID(id);
	s.deleteSchedule();
}

//---------------------------------------------------------------

void FlightManagerController::flightReport(){
	cout << "-------- FLIGHT REPORT --------" << endl;
	cout << "Monthly Flight Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Flight Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
