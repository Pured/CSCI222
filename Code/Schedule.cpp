//
//  Schedule.cpp
//  222test
//
//

#include "Schedule.h"
#include <sstream>
#include "callback.h"
#include "sqlite3.h"

//constructors
Schedule::Schedule(sqlite3* d){
	db=d;
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

//get functions
int Schedule::getID() const{
    return ID;
}

std::string Schedule::getFlightID() const{
    return flightID;
}

int Schedule::getPlane() const{
    return plane;
}

int Schedule::getRoute() const{
    return route;
}

std::string Schedule::getDepartDay() const{
    return departDay;
}

std::string Schedule::getDepart() const{
    return depart;
}

std::string Schedule::getDepartTimezone() const{
    return departTimezone;
}

std::string Schedule::getArriveDay() const{
    return arriveDay;
}

std::string Schedule::getArrive() const{
    return arrive;
}

std::string Schedule::getArriveTimezone() const{
    return arriveTimezone;
}

std::string Schedule::getByID(int n){
	std::stringstream convert;
	convert << n;
	std::string convID = convert.str();
	convert.str(std::string()); //clear ss
	
	std::string sqlCreate = "SELECT  * FROM SCHEDULE WHERE ID = '" + convID +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
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
	
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
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
			
			//std::cout<<FID<<" "<<FLIGHTID<<" "<<PLANE<<" "<<ROUTE<<" "<<DEPARTDAY<<DEPART<<DEPARTTZ
			//<<" "<<ARRIVEDAY<<ARRIVE<<ARRIVETZ<< "\n";
			
			if(FLIGHTID == NULL){
				flightID = "";
			}
			else{
				flightID= std::string(FLIGHTID);
			}
			
			if(DEPARTDAY == NULL){
				departDay = "";
			}
			else{
				departDay = std::string(DEPARTDAY);
			}
			
			if(DEPART == NULL){
				depart = "";
			}
			else{
				depart = std::string(DEPART);
			}
			
			if(DEPARTTZ == NULL){
				departTimezone= "";
			}
			else{
				departTimezone = std::string(DEPARTTZ);
			}
			
			if(ARRIVEDAY == NULL){
				arriveDay = "";
			}
			else{
				arriveDay = std::string(ARRIVEDAY);
			}
			
			if(ARRIVE == NULL){
				arrive = "";
			}
			else{
				arrive = std::string(ARRIVE);
			}
			
			if(ARRIVETZ == NULL){
				arriveTimezone = "";
			}
			else{
				arriveTimezone = std::string(ARRIVETZ);
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

//set functions
void Schedule::setDB(sqlite3* d){
    db=d;
}

void Schedule::setID(int i){
    ID = i;
}

void Schedule::setFlightID(std::string i){
    flightID = i;
}

void Schedule::setPlane(int i){
    plane = i;
}

void Schedule::setRoute(int i){
    route = i;
}

void Schedule::setDepart(std::string i){
    depart = i;
}

void Schedule::setDepartDay(std::string i){
    departDay = i;
}

void Schedule::setDepartTimezone(std::string i){
    departTimezone = i;
}

void Schedule::setArriveDay(std::string i){
    arriveDay = i;
}

void Schedule::setArrive(std::string i){
    arrive = i;
}

void Schedule::setArriveTimezone(std::string i){
    arriveTimezone = i;
}


int Schedule::update(){
		
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
	
		/* Execute SQL statement */
   
		char* errMsg = 0;
		int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
		if( err != SQLITE_OK ){
			std::cout<<"SQL error: "<<errMsg<<std::endl;
			return 1;
		}
	}
	else{
		std::cout<<"Schedule  not initialised in UPDATE."<<std::endl;
		return 1;
	}

   return 0;
}

//other functions
std::ostream &operator<<( std::ostream &os, const Schedule &S){
    os<<"Schedule ID: "<<S.getID()<<"\nFlightID: "<<S.getFlightID()<<"\nPlane: "<<S.getPlane()<<"\nRoute: "<<S.getRoute()<<" "
	<<"\nDeparture Day: "<<S.getDepartDay()<<"\nDeparture Date: "<<S.getDepart()<<"\nDeparture Timezone: "<<S.getDepartTimezone()
	<<"\nArrival Day: "<<S.getArriveDay()<<"\nArrival Date: "<<S.getArrive()<<"\nArrival Timezone: "<<S.getArriveTimezone();
    return os;
}