/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "Seat.h"
#include "Booking.h"
#include "callback.h"
#include "sqlite3.h"

using namespace std;

// Constructors.
Seat::Seat(){
	db = NULL;
	ID = -1;
	scheduleID = -1;
	bookingID = -1;
	seatClass = "No Seat Class";
	seatNum = "No Seat Number";
}

Seat::Seat(sqlite3 *d){
	db = d;
	ID = -1;
	scheduleID = -1;
	bookingID = -1;
	seatClass = "No Seat Class";
	seatNum = "No Seat Number";
}

// Get functions.
int Seat::getID() const{
	return ID;
}

int Seat::getScheduleID() const{
	return scheduleID;
}

int Seat::getBookingID() const{
	return bookingID;
}

std::string Seat::getSeatClass()const{
	return seatClass;
}

std::string Seat::getSeatNum() const{
	return seatNum;
}


// Set functions.
void Seat::setDB(sqlite3 *d){
	db = d;
}

void Seat::setID(int i){
	ID = i;
}

void Seat::setScheduleID(int SID){
	scheduleID = SID;
}

void Seat::setBookingID(int BID){
	bookingID = BID;
}

void Seat::setSeatClass(std::string sClass){
	seatClass = sClass;
}

void Seat::setSeatNum(std::string sNum){
	seatNum = sNum;
}

int Seat::update(){
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

int Seat::create(){
	
	std::stringstream convert;

	convert << scheduleID;
	string convSID = convert.str();
	convert.str(string()); // Clear ss.

	convert << bookingID;
	string convBID = convert.str();
	convert.str(string()); // Clear ss.
	
	std::string createSql = "INSERT INTO SEAT VALUES (NULL," + convSID + ",'" + convBID + "','" + seatClass + "','" + seatNum + "');";

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

std::string Seat::convertSeatNum(int row, int letter){
	std::stringstream convert;
	convert << row;
	std::string rowString = convert.str();
	convert.str(std::string());// clear ss

	std::string ret = rowString;

	std::string letterString = "";
	switch (letter){
		case 0:	 letterString = "A";
			break;
		case 1:	letterString = "B";
			break;
		case 2:	letterString = "C";
			break;
		case 3:	letterString = "D";
			break;
		case 4:	letterString = "E";
			break;
		case 5:	letterString = "F";
			break;
	}

	ret = ret + letterString;
	//cout << "#ret:" <<ret;
	return ret;
}

Seat* Seat::getByScheduleID(int sch_ID,std::string sClass,int& resSize){
	Seat *temp;

	std::stringstream convert;
	convert << sch_ID;
	std::string convID = convert.str();
	convert.str(std::string());// clear ss

	//count amount of results from date query to be used to create dynamic array.
	std::string sqlCreate = "SELECT COUNT(*) FROM SEAT WHERE SCHEDULEID = " + convID + " AND SEATCLASS = '"+ sClass +"';";
	//cout << sqlCreate << endl;
	const char* sql = sqlCreate.c_str();
	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int querySize = 0; //temp int to store amt results
	

	//exec count query
	if (err != SQLITE_OK) {
		std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			querySize = sqlite3_column_int(stmt, 0);
		}
	}

	cout << querySize << endl;
	resSize = querySize;
	temp = new Seat[querySize];

	sqlite3_finalize(stmt);

	sqlCreate = "SELECT SEATNUM FROM SEAT WHERE SCHEDULEID=" + convID + " AND SEATCLASS ='"+ sClass + "';";
	sql = sqlCreate.c_str();
	err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	const char* SEATNUM;

	//exec query
	int i = 0;
	if (err != SQLITE_OK) {
		std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {

			//get attributes from database.
			SEATNUM = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); //get col 0

			//set attributes to Schedule objects in array
			temp[i].setDB(db);

			if (SEATNUM != NULL){
				temp[i].setSeatNum(SEATNUM);
			}
		
			i++;
		}
	}

	return temp;
}


bool Seat::checkExists(){

	if (scheduleID == -1){
		cout << "Seat object not initialised." << endl;
		return false;
	}


	std::stringstream convert;
	convert << ID;
	std::string convID = convert.str();
	convert.str(std::string());// clear ss

	//count amount of results from date query to be used to create dynamic array.
	std::string sqlCreate = "SELECT * FROM SEAT WHERE SCHEDULEID = " + convID + " AND SEATCLASS = '" + seatClass + "' AND SEATNUM = '"+ seatNum+"';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	const char *NAME;
	int SEATID = 0, SCHID = 0, BID = 0;
	const char *SCLASS;
	const char *SNUM;

	if (err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			SEATID = sqlite3_column_int(stmt, 0);
			SCHID = sqlite3_column_int(stmt, 1);
			BID = sqlite3_column_int(stmt, 2);
			SCLASS = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
			SNUM = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));


			if (SCLASS == NULL){
				seatClass = "";
			}
			else{
				seatClass = string(SCLASS);
			}

			if (SNUM == NULL){
				seatNum = "";
			}
			else{
				seatNum = string(SNUM);
			}

			ID = SEATID;
			scheduleID = SCHID;
			bookingID = BID;

		}
	}
	sqlite3_finalize(stmt);

	if (ID != -1){
		return true;
	}
	else{
		return false;
	}
}


// Other functions.
ostream &operator<<(ostream &os, const Seat &S){
	os << "ID: " << S.getID() << "\nScheduleID: " << S.getScheduleID() << "\nBooking ID: " << S.getBookingID() << "\nSeat Class: " << S.getSeatClass()
		<< "\nSeat Number: " << S.getSeatNum() << "\n\n";
	return os;
}
