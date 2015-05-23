/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "Aircraft.h"
#include "callback.h"

using namespace std;

Aircraft::Aircraft(sqlite3 *d){
	db = d;
	ID = 0;
	name = "No Name";
	inService = -1;
	fClass = -1;
	bClass = -1;
	peClass = -1;
	eClass = -1;
	totalSeats = -1;
}

// Get functions.
int Aircraft::getID() const{
	return ID;
}

string Aircraft::getName() const{
	return name;
}

int Aircraft::getInService() const{
	return inService;
}

int Aircraft::getFClass() const{
	return fClass;
}

int Aircraft::getBClass() const{
	return bClass;
}

int Aircraft::getPEClass() const{
	return peClass;
}

int Aircraft::getEClass() const{
	return eClass;
}

int Aircraft::getTotalSeats() const{
	return totalSeats;
}

string Aircraft::getByID(string e){
	string sqlCreate = "SELECT * FROM AIRCRAFT WHERE ID = '" + e + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	const char *NAME;
	int AIRID = 0, INSERV = 0, FC = 0, BC = 0, PEC = 0, EC = 0, TOT = 0;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AIRID = sqlite3_column_int(stmt, 0);
			NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			INSERV = sqlite3_column_int(stmt, 2); 
			FC = sqlite3_column_int(stmt, 3); 
			BC = sqlite3_column_int(stmt, 4); 
			PEC = sqlite3_column_int(stmt, 5); 
			EC = sqlite3_column_int(stmt, 6); 
			TOT = sqlite3_column_int(stmt, 7);
			
			if(NAME == NULL){
				name = "";
			}
			else{
				name = string(NAME);
			}
			
			ID = AIRID;
			inService = INSERV;
			fClass = FC;
			bClass = BC;
			peClass = PEC;
			eClass = EC;
			totalSeats = TOT;
		}
	}

	sqlite3_finalize(stmt);

	if(ID == 0){
		return "NOT FOUND";
	}

	return "FOUND";
}

// Set functions.
void Aircraft::setID(int i){
	ID = i;
}

void Aircraft::setName(string i){
	name = i;
}

void Aircraft::setInService(int i){
	inService = i;
}

void Aircraft::setFClass(int i){
	Class = i;
	etTotalSeats(); // Update total.
}

void Aircraft::setBClass(int i){
	bClass = i;
	setTotalSeats(); // Update total.
}

void Aircraft::setPEClass(int i){
	peClass = i;
	setTotalSeats(); // Update total.
}

void Aircraft::setEClass(int i){
eClass = i;
	setTotalSeats(); // Update total.
}

void Aircraft::setTotalSeats(){
	totalSeats = fClass + bClass + peClass + eClass;
}

int Aircraft::update(){
	// Convert any numeric attributes to string.
	stringstream convert;

	convert << ID;
	string convID = convert.str();
	convert.str(string()); // Clear ss.

	convert << inService;
	string convIS = convert.str();
	convert.str(string()); // Clear ss.

	convert << fClass;
	string convFC = convert.str();
	convert.str(string()); // Clear ss.

	convert << bClass;
	string convBC = convert.str();
	convert.str(string()); // Clear ss.

	convert << peClass;
	string convPEC = convert.str();
	convert.str(string()); // Clear ss.

	convert << eClass;
	string convEC = convert.str();
	convert.str(string()); // Clear ss.

	convert << totalSeats;
	string convTOT = convert.str();
	convert.str(string()); // Clear ss.


	string createSql = "UPDATE AIRCRAFT SET ID = '" + convID + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET NAME = '" + name + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET INSERVICE = '" + convIS + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET FCLASS = '" + convFC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET BCLASS = '" + convBC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET PECLASS = '" + convPEC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET ECLASS = '" + convEC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET TOTAL = '" + convTOT + "' WHERE ID = " + convID + ";";

	const char *sql = createSql.c_str();

	// Execute SQL statement.   
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}

int Aircraft::deleteAircraft(){

	stringstream convert;
	convert << ID;
	string convID = convert.str();

	string sqlCreate = "DELETE FROM AIRCRAFT WHERE ID = '" + convID + "';";
	const char *sql = sqlCreate.c_str();

	// Execute SQL statement.
	char* errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}

int Aircraft::createAircraft(){
	// Get next ID for new AIRPORT.
	string createSql = "SELECT COUNT(ID) FROM AIRCRAFT;";
	const char *sql = createSql.c_str();
	int NEWID;

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW){
			NEWID = sqlite3_column_int(stmt, 0); // Get data from db.
		}
	}

	sqlite3_finalize(stmt);

	NEWID++; // New unique id for airport.

	// Add object details to DB.
	stringstream convert;

	convert << NEWID;
	string convID = convert.str();
	convert.str(string()); // Clear ss.

	convert << inService;
	string convIS = convert.str();
	convert.str(string()); // Clear ss.
	cout<<convIS<<endl;

	convert << fClass;
	string convFC = convert.str();
	convert.str(string()); // Clear ss.

	convert << bClass;
	string convBC = convert.str();
	convert.str(string()); // Clear ss.

	convert << peClass;
	string convPEC = convert.str();
	convert.str(string()); // Clear ss.

	convert << eClass;
	string convEC = convert.str();
	convert.str(string()); // Clear ss.

	convert << totalSeats;
	string convTOT = convert.str();
	convert.str(string()); // Clear ss.

	createSql = "INSERT INTO AIRCRAFT VALUES(" + convID + ",'" + name + "'," + convIS + "," + convFC + "," + convBC + "," + convPEC + "," + convEC + "," + convTOT + ");";

	sql = createSql.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout<<"SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}

ostream &operator<<(ostream &os, const Aircraft &A){
    os << A.getID() << ": " << A.getName() << " " << A.getInService() << " " << A.getFClass() << " " << A.getBClass() << " " <<A.getPEClass() << " " << A.getEClass() << " " << A.getTotalSeats() << endl;

	return os;
};
