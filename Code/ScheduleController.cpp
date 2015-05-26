//
//  ScheduleController.cpp
//  222test
//
//

#include "Schedule.h"
#include "ScheduleController.h"
#include <sstream>
#include "sqlite3.h"
#include <vector>
#include <iostream>


using namespace std;

//constructors
ScheduleController::ScheduleController(sqlite3* d){
	db=d;
}

Schedule* ScheduleController::search(std::string from, std::string to,int& resSize,int route){
	
	Schedule* temp; //temporary pointer for Schedule array
	
	std::stringstream convert;
	convert << route;
	std::string convRoute = convert.str();
	convert.str(std::string());// clear ss
	
	//count amount of results from date query to be used to create dynamic array.
	std::string sqlCreate = "SELECT COUNT(ID) FROM SCHEDULE WHERE DEPARTDATE >= Datetime('" + from + "') AND DEPARTDATE <= Datetime('" + to + "')"
												+ " AND ROUTE=" +convRoute + ";" ;
	//cout<<sqlCreate<<endl;
	const char* sql = sqlCreate.c_str();
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int querySize = 0; //temp int to store amt results
	
	//exec count query
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			querySize = sqlite3_column_int(stmt, 0);
		}
	}
	
	
	resSize = querySize;//assign referenced variable the size of dynamic array.
	sqlite3_finalize(stmt);
	
	//create dynamic array for query results
	temp = new Schedule[querySize];
	
	sqlCreate =  "SELECT * FROM SCHEDULE WHERE DEPARTDATE >= Datetime('" + from + "') AND DEPARTDATE <= Datetime('" + to + "')"
												+ " AND ROUTE=" +convRoute + " ORDER BY DEPARTDATE ASC;" ;
	sql = sqlCreate.c_str();
    err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	//temporary variables for database retreival
	int FID = -1;
	const char* FLIGHTID;
	int PLANE;
	int ROUTE;
	const char * DEPARTDAY;
	const char* DEPART;
	const char * DEPARTTZ;
	const char * ARRIVEDAY;
	const char* ARRIVE;
	const char * ARRIVETZ;
	
	//exec date query
	int i = 0;
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			
			//get attributes from database.
			FID = sqlite3_column_int(stmt, 0);
            FLIGHTID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			PLANE = sqlite3_column_int(stmt, 2);
			ROUTE = sqlite3_column_int(stmt, 3);
			DEPARTDAY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); //get col 0
			DEPART = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)); //get col 0
			DEPARTTZ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)); //get col 0
			ARRIVEDAY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)); //get col 0
			ARRIVE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)); //get col 0
			ARRIVETZ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)); //get col 0
			
			//set attributes to Schedule objects in array
			temp[i].setDB(db);
			temp[i].setID(FID);
			temp[i].setFlightID(std::string(FLIGHTID));
			temp[i].setPlane(PLANE);
			temp[i].setRoute(ROUTE);
			temp[i].setDepartDay(std::string(DEPARTDAY));
			temp[i].setDepart(std::string(DEPART));
			temp[i].setDepartTimezone(std::string(DEPARTTZ));
			temp[i].setArriveDay(std::string(ARRIVEDAY));
			temp[i].setArrive(std::string(ARRIVE));
			temp[i].setArriveTimezone(std::string(ARRIVE));
			
			i++;
		}
	}
	
	//return reference to Schedule array.
	return temp;
}





