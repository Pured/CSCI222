//
//  Route.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "Route.h"
#include "sqlite3.h"
#include "callback.h"
#include <sstream>

//Constructors

Route::Route(sqlite3* d){
	db = d;
    ID = -1;
    srcAirport = "No Source Airport";
    destAirport = "No Destination Airport";
    codeshare = "No Codeshare";
    stops = 999;
}



//get functions
int Route::getID() const{
    return ID;
}

std::string Route::getSrc() const{
    return srcAirport;
}

std::string Route::getDest() const{
    return destAirport;
}

std::string Route::getCodeshare() const{
    return codeshare;
}

int Route::getStops() const{
    return stops;
}

std::string Route::getByID(int id){
	std::stringstream convert;
	convert << id;
	std::string convid = convert.str();
	convert.str(std::string()); //clear ss
	
	std::string sqlCreate = "SELECT  * FROM ROUTE WHERE ID = '" + convid +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int ROUTEID = -1 ,STOPS;
	const char* SRC;
	const char* DEST;
	const char* CODE;
	
		 if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			ROUTEID = sqlite3_column_int(stmt, 0);
            SRC = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			DEST= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // get col 1
            CODE= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // get col 1
			STOPS = sqlite3_column_int(stmt, 4);
			
			//std::cout<<ROUTEID<<" "<<SRC<<" "<<DEST<<" "<<CODE<<" "<<STOPS<<"\n";
			
			if(SRC == NULL){
				srcAirport = "";
			}
			else{
				srcAirport = std::string(SRC);
			}
			
			if(DEST == NULL){
				destAirport = "";
			}
			else{
				destAirport = std::string(DEST);
			}
			
			if(CODE == NULL){
				codeshare = "";
			}
			else{
				codeshare = std::string(CODE);
			}
			
			ID = ROUTEID;
			stops = STOPS;
		}
	}
	
	sqlite3_finalize(stmt);
	
	if(ID == -1){
		return "NOT FOUND";
	}
	
	return "FOUND";
}


//set Functions
void Route::setID(int i){
    ID = i;
}

void Route::setSrc(std::string i){
    srcAirport = i;
}

void Route::setDest(std::string i){
    destAirport = i;
}

void Route::setCodeshare(std::string i){
    codeshare = i;
}

void Route::setStops(int i){
    stops = i;
}

int Route::update(){
	
	if(ID != -1){
		//convert any numeric attributes to string
		std::stringstream convert;
		convert << ID;
		std::string convID = convert.str();
		convert.str(std::string()); //clear ss
	
		convert << stops;
		std::string convStops = convert.str();
		convert.str(std::string()); //clear ss
	
	
		std::string createSql = "UPDATE ROUTE SET ID = '" + convID + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE ROUTE SET SRC = '" + srcAirport + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE ROUTE SET DEST = '" + destAirport + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE ROUTE SET CODESHARE = '" + codeshare + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE ROUTE SET STOPS = '" + convStops + "' WHERE ID = "+ convID + "; ";

							
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
		std::cout<<"ROUTE  not initialised in UPDATE."<<std::endl;
		return 1;
	}

   return 0;
}

std::ostream &operator<<( std::ostream &output,const Route &R){
    output<<R.getID()<<" "<<R.getSrc()<<" "<<R.getDest()<<" "<<R.getCodeshare()<<" "<<R.getStops()<<std::endl;
    return output;
}