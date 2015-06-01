/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Implemented the create/update/delete functions.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "Schedule.h"
#include "callback.h"

using namespace std;

// Constructors.
Schedule::Schedule(sqlite3 *d){
	db = d;
	ID = -1;
	flightID = "No FlightID";
	plane = -1;
	route = -1;
	departDay = "No departure day";
	depart = "No Departure";
	departTimezone = "No depart timezone";
	arriveDay = "No arrival Day";
	arrive = "No Arrive";
	arriveTimezone = "No arrival timezone";
}

Schedule::Schedule(){
	db = NULL;
	ID = -1;
	flightID = "No FlightID";
	plane = -1;
	route = -1;
	departDay = "No departure day";
	depart = "No Departure";
	departTimezone = "no depart timezone";
	arriveDay = "no arrival Day";
	arrive = "No Arrive";
	arriveTimezone = "No arrival timezone";
}

// Get functions.
int Schedule::getID() const{
    return ID;
}

string Schedule::getFlightID() const{
    return flightID;
}

int Schedule::getPlane() const{
    return plane;
}

int Schedule::getRoute() const{
    return route;
}

string Schedule::getDepartDay() const{
    return departDay;
}

string Schedule::getDepart() const{
    return depart;
}

string Schedule::getDepartTimezone() const{
    return departTimezone;
}

string Schedule::getArriveDay() const{
    return arriveDay;
}

string Schedule::getArrive() const{
    return arrive;
}

string Schedule::getArriveTimezone() const{
    return arriveTimezone;
}

string Schedule::getByID(int n){
	stringstream convert;

	convert << n;

	string convID = convert.str();
	convert.str(string()); // Clear ss.
	
	string sqlCreate = "SELECT * FROM SCHEDULE WHERE ID = '" + convID + "';";
	const char *sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int FID = -1, PLANE = 0, ROUTE = 0;
	const char *FLIGHTID, *DEPARTDAY, *DEPART, *DEPARTTZ, *ARRIVEDAY, *ARRIVE, *ARRIVETZ;
	
	if(err != SQLITE_OK){
        cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
    }
    else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			FID = sqlite3_column_int(stmt, 0);

            FLIGHTID = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

			PLANE = sqlite3_column_int(stmt, 2);
			ROUTE = sqlite3_column_int(stmt, 3);

			DEPARTDAY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
			DEPART = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
			DEPARTTZ = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
			ARRIVEDAY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));
			ARRIVE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
			ARRIVETZ = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));

			if(FLIGHTID == NULL){
				flightID = "";
			}
			else{
				flightID = string(FLIGHTID);
			}

			if(DEPARTDAY == NULL){
				departDay = "";
			}
			else{
				departDay = string(DEPARTDAY);
			}

			if(DEPART == NULL){
				depart = "";
			}
			else{
				depart = string(DEPART);
			}

			if(DEPARTTZ == NULL){
				departTimezone = "";
			}
			else{
				departTimezone = string(DEPARTTZ);
			}

			if(ARRIVEDAY == NULL){
				arriveDay = "";
			}
			else{
				arriveDay = string(ARRIVEDAY);
			}

			if(ARRIVE == NULL){
				arrive = "";
			}
			else{
				arrive = string(ARRIVE);
			}

			if(ARRIVETZ == NULL){
				arriveTimezone = "";
			}
			else{
				arriveTimezone = string(ARRIVETZ);
			}
			
			ID = FID;
			plane = PLANE;
			route = ROUTE;
		}
	}

	sqlite3_finalize(stmt);

	if(ID == -1){
		return "NOT FOUND";
	}

	return "FOUND";
}

// Set functions.
void Schedule::setDB(sqlite3 *d){
	db = d;
}

void Schedule::setID(int i){
	ID = i;
}

void Schedule::setFlightID(string i){
	flightID = i;
}

void Schedule::setPlane(int i){
	plane = i;
}

void Schedule::setRoute(int i){
	route = i;
}

void Schedule::setDepart(string i){
	depart = i;
}

void Schedule::setDepartDay(string i){
	departDay = i;
}

void Schedule::setDepartTimezone(string i){
	departTimezone = i;
}

void Schedule::setArriveDay(string i){
	arriveDay = i;
}

void Schedule::setArrive(string i){
	arrive = i;
}

void Schedule::setArriveTimezone(string i){
	arriveTimezone = i;
}

// Other functions.
ostream &operator<<(ostream &os, const Schedule &S){
	os << "Schedule ID: " << S.getID() << "\nFlightID: " << S.getFlightID() << "\nPlane: " << S.getPlane() << "\nRoute: " << S.getRoute() << " " << "\nDeparture Day: " << S.getDepartDay() << "\nDeparture Date: " << S.getDepart() << "\nDeparture Timezone: " << S.getDepartTimezone() << "\nArrival Day: " << S.getArriveDay() << "\nArrival Date: " << S.getArrive() << "\nArrival Timezone: " << S.getArriveTimezone();

	return os;
}

void Schedule::createSchedule(){
	// Add object details to DB.
	stringstream convert;

	convert << plane;
	string convPlane = convert.str();
	convert.str(string()); // Clear ss.

	convert << route;
	string convRoute = convert.str();
	convert.str(string()); // Clear ss.

	string createSql = "INSERT INTO SCHEDULE VALUES(NULL,'" + flightID + "'," + convPlane + "," + convRoute + ",'" + departDay + "','" + depart + "','" + departTimezone + "','" + arriveDay + "','" + arrive + "','" + arriveTimezone + "');";

	const char* sql = createSql.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}

void Schedule::updateSchedule(){
	if(ID != -1){
		// Convert any numeric attributes to string.
		stringstream convert;

		convert << ID;

		string convID = convert.str();
		convert.str(string()); // Clear ss.
		
		convert << plane;
		string convPlane = convert.str();
		convert.str(string()); // Clear ss.
		
		convert << route;
		string convRoute = convert.str();
		convert.str(string()); // Clear ss.
	
        string createSql = "UPDATE SCHEDULE SET FLIGHTID = '" + flightID + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET PLANE = '" + convPlane + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET ROUTE = '" + convRoute + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET DEPARTDAY = '" + departDay + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET DEPART = '" + depart + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET DEPARTTIMEZONE = '" + departTimezone + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET ARRIVEDAY = '" + arriveDay + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET ARRIVE = '" + arrive + "' WHERE ID = '" + convID + "';" + "UPDATE SCHEDULE SET ARRIVETIMEZONE = '" + arriveTimezone + "' WHERE ID = '" + convID + "';" ;

		const char *sql = createSql.c_str();

		// Execute SQL statement.
		char *errMsg = 0;
		int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

		if(err != SQLITE_OK){
			cout << "SQL error: " << errMsg << endl;
		}
	}
	else{
		cout << "Schedule was not initialised in update.\n";
	}
}

void Schedule::deleteSchedule(){
	stringstream convert;

	convert << ID;
	string convID = convert.str();

	string sqlCreate = "DELETE FROM SCHEDULE WHERE ID = '" + convID + "';";
	const char *sql = sqlCreate.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}
