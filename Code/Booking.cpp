/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Cleaned up the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "Booking.h"
#include "callback.h"
#include "sqlite3.h"

using namespace std;

// Constructors.
Booking::Booking(){
	db = NULL;
	ID = -1;
	custEmail = "No Email";
	scheduleID = -1;
	travelAgent = "NULL";
}

Booking::Booking(sqlite3 *d){
	db = d;
	ID = -1;
	custEmail = "No Email";
	scheduleID = -1;
	travelAgent = "";
}

// Get functions.
int Booking::getID(){
	return ID;
}

string Booking::getCustEmail(){
	return custEmail;
}

int Booking::getScheduleID(){
	return scheduleID;
}


string Booking::getTravelAgent(){
	return travelAgent;
}

Booking *Booking::getByEmail(string n, int &resSize){
	Booking *temp; // Temporary pointer for Booking array.

	// Count amount of results from date query to be used to create dynamic array.
	string sqlCreate = "SELECT COUNT(ID) FROM BOOKING WHERE CUSTEMAIL = '" + n + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int querySize = 0; // Temp int to store amt results.

	// Execute count query.
	if(err != SQLITE_OK){
        cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
    }
    else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			querySize = sqlite3_column_int(stmt, 0);
		}
	}

	resSize = querySize; // Assign referenced variable the size of dynamic array.
	sqlite3_finalize(stmt);

	temp = new Booking[querySize]; // Create dynamic array for query results.

	sqlCreate = "SELECT * FROM BOOKING WHERE CUSTEMAIL = '" + n + "';";
	sql = sqlCreate.c_str();
	err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Temporary variables for database retreival.
	int BID = -1, SID = 0;
	const char *CUSTEMAIL, *TRAVELAGENT;

	int i = 0;

	// Execute date query.
	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get attributes from database.
			BID = sqlite3_column_int(stmt, 0); // Store column 1.
			CUSTEMAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)); // Store column 2.
			SID = sqlite3_column_int(stmt, 2); // Store column 3.
			TRAVELAGENT = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)); // Store column 4.

			// Set attributes to Schedule objects in array.
			temp[i].setDB(db);
			temp[i].setID(BID);
			temp[i].setScheduleID(SID);

			if(CUSTEMAIL == NULL){
				temp[i].setCustEmail(string(""));
			}
			else{
				temp[i].setCustEmail(string(CUSTEMAIL));
			}	

			if(TRAVELAGENT == NULL){
				temp[i].setTravelAgent(string(""));
			}
			else{
				temp[i].setTravelAgent(string(TRAVELAGENT));
			}

			i++;
		}
	}

	return temp; // Return reference to Schedule array.
}

// Set functions.
void Booking::setDB(sqlite3 *d){
	db = d;
}

void Booking::setID(int i){
	ID = i;
}

void Booking::setCustEmail(string i){
	custEmail = i;
}

void Booking::setScheduleID(int i){
	scheduleID = i;
}

void Booking::setTravelAgent(string i){
	travelAgent = i;
}

int Booking::update(){
	/*
		
	if(ID != -1){
		//convert any numeric attributes to string
		stringstream convert;
		convert << ID;
		string convID = convert.str();
		convert.str(string()); //clear s
		
		convert << plane;
		string convPlane = convert.str();
		convert.str(string()); //clear s
		
		convert << route;
		string convRoute = convert.str();
		convert.str(string()); //clear s
	
		string createSql = "UPDATE SCHEDULE SET ID = '" + convID + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET FLIGHTID = '" + flightID + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET PLANE = '" + convPlane + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET ROUTE = '" + convRoute + "' WHERE ID = '"+ convID + "'; "
							+ 	"UPDATE SCHEDULE SET DEPART = '" + depart + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET ARRIVE = '" + arrive + "' WHERE ID = '"+ convID + "'; " ;

							
							//cout<<createSql<<endl;
		const char* sql = createSql.c_str();
	
		// Execute SQL statement 
   
		char* errMsg = 0;
		int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
		if( err != SQLITE_OK ){
			cout<<"SQL error: "<<errMsg<<endl;
			return 1;
		}
	}
	else{
		cout<<"Booking  not initialised in UPDATE."<<endl;
		return 1;
	}
*/
	return 0;
}

int Booking::create(){

	std::stringstream convert;

	convert << scheduleID;
	string convSID = convert.str();
	convert.str(string()); // Clear ss.

	std::string createSql = "";
	if (travelAgent != "NULL"){
		//travel agent is signing up customer, add travel agent name to booking.
		createSql = "INSERT INTO BOOKING VALUES (NULL,'" + custEmail + "'," + convSID + ",'" + travelAgent + "');";
	}
	else{
		//customer is booking themselves or staff member is booking customer. no travel agent info.
		createSql = "INSERT INTO BOOKING VALUES (NULL,'" + custEmail + "'," + convSID + ", NULL);";
	}

	const char *sql = createSql.c_str();

	// Execute SQL statement 
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if (err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
	
}

int Booking::getMRE(){
	// Get next most recent entry ID
	string createSql = "SELECT MAX(BID) FROM ( SELECT ID AS BID FROM BOOKING GROUP BY ID);";
	
	const char *sql = createSql.c_str();
	int MRE = -1;

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if (err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW){
			MRE = sqlite3_column_int(stmt, 0); // Get data from db.
		}
	}

	sqlite3_finalize(stmt);

	if (MRE != -1){
		return MRE;
	}

	return -1;
}

// Other functions.
ostream &operator<<(ostream &os, const Booking &B){
	return os;
}
