//
//  Booking.cpp
//  222test
//
//

#include "Booking.h"
#include <sstream>
#include "callback.h"
#include "sqlite3.h"

//constructors
Booking::Booking(){
	db = NULL;
	ID = -1;
	custEmail = "No Email";
	scheduleID = -1;
	seatClass = "No seat class";
	travelAgent = "";
};

Booking::Booking(sqlite3* d){
	db = d;
	ID = -1;
	custEmail = "No Email";
	scheduleID = -1;
	seatClass = "No seat class";
	travelAgent = "";
}

//get functions
int Booking::getID(){
	return ID;
}

std::string Booking::getCustEmail(){
	return custEmail;
}

int Booking::getScheduleID(){
	return scheduleID;
}

std::string Booking::getSeatClass(){
	return seatClass;
}

std::string Booking::getTravelAgent(){
	return travelAgent;
}


Booking* Booking::getByEmail(std::string n,int& resSize){
		
	Booking* temp; //temporary pointer for Booking array
	
	//count amount of results from date query to be used to create dynamic array.
	std::string sqlCreate = "SELECT COUNT(ID) FROM BOOKING WHERE CUSTEMAIL = '" + n + "';" ;
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
	temp = new Booking[querySize];
	
	sqlCreate =  "SELECT * FROM BOOKING WHERE CUSTEMAIL = '" + n + "';" ;
	sql = sqlCreate.c_str();
    err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	//temporary variables for database retreival
	int BID = -1;
	const char* CUSTEMAIL;
	int SID;
	const char * SEATCLASS;
	const char* TRAVELAGENT;
	
	//exec date query
	int i = 0;
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			
			//get attributes from database.
			BID = sqlite3_column_int(stmt, 0);
            CUSTEMAIL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			SID = sqlite3_column_int(stmt, 2);
			SEATCLASS = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); //get col 0
			TRAVELAGENT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); //get col 0
			
			//set attributes to Schedule objects in array
			temp[i].setDB(db);
			temp[i].setID(BID);
			temp[i].setScheduleID(SID);
			
			if(CUSTEMAIL == NULL){
				temp[i].setCustEmail(std::string(""));
			}
			else{
				temp[i].setCustEmail(std::string(CUSTEMAIL));
			}
			
			if(SEATCLASS == NULL){
				temp[i].setSeatClass(std::string(""));
			}
			else{
				temp[i].setSeatClass(std::string(SEATCLASS));
			}			
			
			if(TRAVELAGENT == NULL){
				temp[i].setTravelAgent(std::string(""));
			}
			else{
				temp[i].setTravelAgent(std::string(TRAVELAGENT));
			}
			
			i++;
		}
	}
	
	//return reference to Schedule array.
	return temp;
}


//set functions
void Booking::setDB(sqlite3* d){
	db=d;
}

void Booking::setID(int i){
	ID = i;
}

void Booking::setCustEmail(std::string i){
	custEmail = i;
}

void Booking::setScheduleID(int i){
	scheduleID = i;
}

void Booking::setSeatClass(std::string i){
	seatClass = i;
}

void Booking::setTravelAgent(std::string i){
	travelAgent = i;
}


int Booking::update(){
	/*
		
	if(ID != -1){
		//convert any numeric attributes to string
		std::stringstream convert;
		convert << ID;
		std::string convID = convert.str();
		convert.str(std::string()); //clear s
		
		convert << plane;
		std::string convPlane = convert.str();
		convert.str(std::string()); //clear s
		
		convert << route;
		std::string convRoute = convert.str();
		convert.str(std::string()); //clear s
	
		std::string createSql = "UPDATE SCHEDULE SET ID = '" + convID + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET FLIGHTID = '" + flightID + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET PLANE = '" + convPlane + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET ROUTE = '" + convRoute + "' WHERE ID = '"+ convID + "'; "
							+ 	"UPDATE SCHEDULE SET DEPART = '" + depart + "' WHERE ID = '"+ convID + "'; " 
							+ 	"UPDATE SCHEDULE SET ARRIVE = '" + arrive + "' WHERE ID = '"+ convID + "'; " ;

							
							//std::cout<<createSql<<std::endl;
		const char* sql = createSql.c_str();
	
		// Execute SQL statement 
   
		char* errMsg = 0;
		int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
		if( err != SQLITE_OK ){
			std::cout<<"SQL error: "<<errMsg<<std::endl;
			return 1;
		}
	}
	else{
		std::cout<<"Booking  not initialised in UPDATE."<<std::endl;
		return 1;
	}
*/
   return 0;
   
}

//other functions
std::ostream &operator<<( std::ostream &os, const Booking &B){
  
    return os;
}