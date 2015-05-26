/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#include "ServiceManagerController.h"
#include "sqlite3.h"
#include <sstream>
#include <string>

ServiceManagerController::ServiceManagerController(sqlite3* d){
	db = d;
    userType = "ServiceManager";
}

void ServiceManagerController::findFlight(){
	string fc;

        cout<<"Input the flight code: ";
	cin>>fc;

	cout << endl;

	string sqlCreate = "SELECT * FROM SCHEDULE WHERE FLIGHTID = '" + fc + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, PLANE, ROUTE;
	const char* FLIGHTID;
	const char* DEPART;
	const char* ARRIVE;

	if (err != SQLITE_OK) {
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			FLIGHTID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_double(stmt, 2);	
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPART = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
			ARRIVE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
  
			cout<<"ID: "<<ID<<"\nFlight Code: "<<FLIGHTID<<"\nPlane: "<<PLANE<<"\nRoute: "<<ROUTE<<"\nDeparture: "<<DEPART<<"\nArrival: "<<ARRIVE<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void ServiceManagerController::findService(){
	string fc;

	cout<<"Input the flight code: ";
	cin>>fc;

	cout << endl;

	string sqlCreate = "SELECT * FROM SCHEDULE WHERE FLIGHTID = '" + fc + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, PLANE, ROUTE;
	const char* FLIGHTID;
	const char* DEPART;
	const char* ARRIVE;

	if (err != SQLITE_OK) {
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			FLIGHTID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_double(stmt, 2);	
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPART = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
			ARRIVE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
  
			cout<<"ID: "<<ID<<"\nFlight Code: "<<FLIGHTID<<"\nPlane: "<<PLANE<<"\nRoute: "<<ROUTE<<"\nDeparture: "<<DEPART<<"\nArrival: "<<ARRIVE<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void ServiceManagerController::createService(){
	//create variables to store data.
	int lastID=0, ID = 0;
	float COST;
	string ITEM, AVAILABILITY;

	//lastID = sqlstuff ... "SELECT LAST(ID) FROM SERVICEITEM;";

	ID = lastID + 1;

	cout << "Adding a new item..." << endl;
	cout << "Item ID: " << ID << endl;

	cout << "Item: ";
	getline(cin, ITEM);

	cout << "Cost: ";
	cin >> COST;

	cout << "Availability: ";
	getline(cin, AVAILABILITY);

	stringstream convert;

	convert << ID;
	string convID = convert.str();
	
	convert << COST;
	string convCOST = convert.str();

	string createSql = "INSERT INTO SERVICEITEM VALUES('" + convID + "', '" + ITEM + "', '" + convCOST + "', '" + AVAILABILITY + "');";

	const char* sql = createSql.c_str();

	/* Execute SQL statement */
/*
	char* errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
	if(err != SQLITE_OK){
		cout<<"SQL error: "<<errMsg<<endl;
		return 1;
	}
*/
}

void ServiceManagerController::editService(){

}

void ServiceManagerController::deleteService(){
	string si;

	cout << "Input the item you wish to delete: ";
	cin>>si;

	cout << endl;

	string sqlCreate = "DELETE FROM SERVICEITEM WHERE ITEM = '" + si + "';";
	const char* sql = sqlCreate.c_str();

	//execute sql delete here ... somehow
}

void ServiceManagerController::serviceReport(){
	cout << "-------- SERVICE REPORT --------" << endl;
	cout << "Monthly Service Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Service Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
