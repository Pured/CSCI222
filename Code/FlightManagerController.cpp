/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#include "FlightManagerController.h"
#include "Aircraft.h"
#include <cstdlib>

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

}

void FlightManagerController::createAircraft(){
	Aircraft ac(db);
	std::string NAME = "",INSt,FCt,BCt,PECt,ECt;
	int INS,FC,BC,PEC,EC;

	cout<<"creating new aircraft..."<<endl;
	cin.ignore();
	cout<<"Name: ";
	getline(cin,NAME);
	ac.setName(NAME);
	
	cin.clear();
	cout << "Amount in service: ";
	cin >> INSt;
	INS = atoi(INSt.c_str());
	//cout<<INS<<endl;
	ac.setInService(INS);
	//cout<<ac.getInService()<<endl;
	
	cout << "Amount of First Class: ";
	cin >> FCt;
	FC = atoi(FCt.c_str());
	//cout<<FC<<endl;
	ac.setFClass(FC);
	
	cout << "Amount of Business Class: ";
	cin >> BCt;
	BC = atoi(BCt.c_str());
	//cout<<BC<<endl;
	ac.setBClass(BC);
	
	cout << "Amount of Premium Economy class: ";
	cin >> PECt;
	PEC = atoi(PECt.c_str());
	//cout<<PEC<<endl;
	ac.setPEClass(PEC);
	
	cout << "Amount of Economy class: ";
	cin >> ECt;
	EC = atoi(ECt.c_str());
	//cout<<EC<<endl;
	ac.setEClass(EC);
	
	ac.createAircraft();
	
	
}

void FlightManagerController::editAircraft(){

}

void FlightManagerController::deleteAircraft(){
	std::string inputTemp;
	int aID;
	cout<<"Input Aircraft ID: ";
	cin>>inputTemp;
	
	aID = atoi(inputTemp.c_str());
	
	Aircraft ac(db);
	ac.getByID(inputTemp);
	ac.deleteAircraft();
	
}

//-----Schedule--------------------------------------------------

void FlightManagerController::findSchedule(){
	string id;

        cout<<"Input the flight ID: ";
	cin >> id;

	cout << endl;

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
