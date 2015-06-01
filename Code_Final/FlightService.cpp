/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Fixed auto increment for the create function.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "FlightService.h"
#include "callback.h"

using namespace std;

// Constructors.
FlightService::FlightService(sqlite3 *d)
{
	db = d;
	ID = -1;
	scheduleID = -1;
	serviceItemID = -1;
	bookingID = -1;
	amount = -1;
}

FlightService::FlightService()
{
	db = NULL;
	ID = -1;
	scheduleID = -1;
	serviceItemID = -1;
	bookingID = -1;
	amount = -1;
}

// Get functions.
int FlightService::getID() const{
	return ID;
}

int FlightService::getScheduleID() const{
	return scheduleID;
}

int FlightService::getServiceItemID() const{
	return serviceItemID;
}

int FlightService::getBookingID() const{
	return bookingID;
}

int FlightService::getAmount() const{
	return amount;
}

string FlightService::getByID(int id){
	stringstream convert;
	convert << id;
	string convid = convert.str();
	convert.str(string()); //clear ss

	string sqlCreate = "SELECT * FROM FLIGHTSERVICE WHERE ID = '" + convid + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int SVCID = -1;
	int SID = -1;
	int SIID = -1;
	int BID = -1;
	int AMT = -1;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			SVCID = sqlite3_column_int(stmt, 0);
			SID = sqlite3_column_int(stmt, 1);
			SIID = sqlite3_column_int(stmt, 2);
			BID = sqlite3_column_int(stmt, 3);
			AMT = sqlite3_column_int(stmt, 4);

			cout << SVCID << " " << SID << " " << SIID << " " << BID << " "<< AMT <<"\n";

			ID = SVCID;
			scheduleID = SID;
			serviceItemID = SIID;
			bookingID = BID;
			amount = AMT;
		}
	}

	sqlite3_finalize(stmt);

	if(ID == -1){
		return "NOT FOUND";
	}

	return "FOUND";
}

FlightService *FlightService::getByBookingID(int bid, int &resSize){
	FlightService *temp;

	stringstream convert;
	convert << bid;
	string convID = convert.str();
	convert.str(string()); // Clear ss.

	// Count amount of results from date query to be used to create dynamic array.
	string sqlCreate = "SELECT COUNT(*) FROM FLIGHTSERVICE WHERE BOOKINGID = " + convID + ";";

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

	resSize = querySize;
	temp = new FlightService[querySize];

	sqlite3_finalize(stmt);

	sqlCreate = "SELECT * FROM FLIGHTSERVICE WHERE BOOKINGID=" + convID + ";";
	sql = sqlCreate.c_str();
	err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int SVCID = -1;
	int SID = -1;
	int SIID = -1;
	int BID = -1;
	int AMT = -1;

	int i = 0;

	// Execute query.
	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			SVCID = sqlite3_column_int(stmt, 0);
			SID = sqlite3_column_int(stmt, 1);
			SIID = sqlite3_column_int(stmt, 2);
			BID = sqlite3_column_int(stmt, 3);
			AMT = sqlite3_column_int(stmt, 4);

			temp[i].setID(SVCID);
			temp[i].setScheduleID(SID);
			temp[i].setServiceItemID(SIID);
			temp[i].setBookingID(BID);
			temp[i].setAmount(AMT);

			i++;
		}
	}

	return temp;
}

// Set functions.
void FlightService::setID(int i){
	ID = i;
}

void FlightService::setDB(sqlite3* d){
	db = d;
}

void FlightService::setScheduleID(int SID){
	scheduleID = SID;
}

void FlightService::setServiceItemID(int SIID){
	serviceItemID = SIID;
}

void FlightService::setBookingID(int BID){
	bookingID = BID;
}

void FlightService::setAmount(int amt){
	amount = amt;
}

FlightService *FlightService::getByScheduleID(int SID, int &resSize){
	return NULL;
}

// Other functions.
ostream &operator<<(ostream &os, const FlightService &F){
	os << "ID: " << F.getID() << "\nSchedule ID: " << F.getScheduleID() << "\nService Item: " << F.getServiceItemID()
		<< "\nBooking ID: " << F.getBookingID() << "\nAmount: " << F.getAmount() << "\n";

	return os;
}

FlightService FlightService::operator=(const FlightService &FS){
	FlightService newFS(db);
	newFS.setID(FS.ID); 
	newFS.setScheduleID(FS.scheduleID);
	newFS.setBookingID(FS.bookingID);
	newFS.setServiceItemID(FS.serviceItemID);
	newFS.setAmount(FS.amount);

	return newFS;
}

int FlightService::createFlightService(){
	stringstream convert;

	convert << scheduleID;
	string convSID = convert.str();
	convert.str(string()); // Clear ss.

	convert << serviceItemID;
	string convSIID = convert.str();
	convert.str(string()); // Clear ss.

	convert << bookingID;
	string convBID = convert.str();
	convert.str(string()); // Clear ss.

	convert << amount;
	string convAmount = convert.str();
	convert.str(string()); // Clear ss.

	string createSql = "INSERT INTO FLIGHTSERVICE VALUES (NULL," + convSID + "," + convSIID + "," + convBID + "," + convAmount + ");";

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

int FlightService::deleteFlightService(){
	stringstream convert;
	convert << ID;
	string convID = convert.str();

	string sqlCreate = "DELETE FROM FLIGHTSERVICE WHERE ID = '" + convID + "';";
	cout << sqlCreate << endl;
	const char *sql = sqlCreate.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}
