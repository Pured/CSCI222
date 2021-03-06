/*=============================================================
| Modified by: kb100
| Version: 1.08
| Modification: Cleaned up the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "Aircraft.h"
#include "callback.h"

using namespace std;

Aircraft::Aircraft(sqlite3 *d){
	db = d;
	ID = -1;
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
		while(sqlite3_step(stmt) == SQLITE_ROW){
			AIRID = sqlite3_column_int(stmt, 0); // Store column 1.

			NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)); // Store column 2.

			INSERV = sqlite3_column_int(stmt, 2); // Store column 3.
			FC = sqlite3_column_int(stmt, 3); // Store column 4.
			BC = sqlite3_column_int(stmt, 4); // Store column 5.
			PEC = sqlite3_column_int(stmt, 5); // Store column 6.
			EC = sqlite3_column_int(stmt, 6); // Store column 7.
			TOT = sqlite3_column_int(stmt, 7); // Store column 8.
			
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

	sqlite3_finalize(stmt); // Deletes prepared statement.

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
	fClass = i;
	setTotalSeats(); // Update total.
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

ostream &operator<<(ostream &os, const Aircraft &A){
    os << A.getID() << ": " << A.getName() << " " << A.getInService() << " " << A.getFClass() << " " << A.getBClass() << " " << A.getPEClass() << " " << A.getEClass() << " " << A.getTotalSeats() << endl;

	return os;
}

void Aircraft::createAircraft(){
	// Add object details to DB.
	stringstream convert;

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

	string createSql = "INSERT INTO AIRCRAFT VALUES(NULL,'" + name + "'," + convIS + "," + convFC + "," + convBC + "," + convPEC + "," + convEC + "," + convTOT + ");";

	const char* sql = createSql.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}

void Aircraft::updateAircraft(){
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

	string createSql = "UPDATE AIRCRAFT SET NAME = '" + name + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET INSERVICE = '" + convIS + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET FCLASS = '" + convFC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET BCLASS = '" + convBC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET PECLASS = '" + convPEC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET ECLASS = '" + convEC + "' WHERE ID = " + convID + ";" + "UPDATE AIRCRAFT SET TOTAL = '" + convTOT + "' WHERE ID = " + convID + ";";

	const char *sql = createSql.c_str();

	// Execute SQL statement.   
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}

void Aircraft::deleteAircraft(){
	stringstream convert;

	convert << ID;
	string convID = convert.str();

	string sqlCreate = "DELETE FROM AIRCRAFT WHERE ID = '" + convID + "';";
	const char *sql = sqlCreate.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}

int Aircraft::round(float num){
	int whole = num;

	return whole + 1;
}

int Aircraft::getSClassStartPoint(string sClass, int &rowStart){
	int counter = 0;
	float rowC;
	rowStart = 1;

	// First class always starts at 0.
	if(sClass == "First"){
		return counter;
	}

	// Find at what seat business class starts.
	if(sClass == "Business"){
		// If count is divisable by 6, all is good.
		if((fClass % 6) == 0){
			rowStart = (fClass / 6) + 1;
		}
		else{
			// Round up for indivisable.
			rowC = static_cast<float>(fClass) / 6;
			rowStart = round(rowC);
		}

		counter = fClass % 6;

		return counter;
	}
	
	// Find at what seat premium econ class starts.
	if(sClass == "Premium Economy"){
		// If count is divisable by 6, all is good.
		if(((fClass + bClass) % 6) == 0){
			rowStart = ((fClass+bClass) / 6) + 1;
		}
		else{
			// Round up for indivisable.
			rowC = static_cast<float>((fClass+bClass) / 6);
			rowStart = round(rowC);
		}

		counter = (fClass + bClass) % 6;

		return counter;
	}

	// Find at what seat econ class starts.
	if(sClass == "Economy"){
		// If count is divisable by 6, all is good.
		if(((fClass + bClass + peClass) % 6) == 0){
			rowStart = ((fClass + bClass + peClass) / 6) + 1;
		}
		else{
			// Round up for indivisable.
			rowC = static_cast<float>((fClass + bClass + peClass) / 6);
			rowStart = round(rowC);
		}

		counter = (fClass + bClass + peClass) % 6;

		return counter;
	}

	return -1;
}
