//
//  Airport.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "Airport.h"
#include "callback.h"
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

Airport::Airport(sqlite3* d){
	db = d;
    ID = 0;
    name = "No name";
    city = "No City";
    country = "No Country";
    iata = "No IATA";
    latitude = 0;
    longitude = 0;
    altitude = 0;
    timezone = -1;
    dst = "No DST";
    tz = "No TZ";
    
};

Airport::Airport(){
	db = NULL;
    ID = 0;
    name = "No name";
    city = "No City";
    country = "No Country";
    iata = "No IATA";
    latitude = 0;
    longitude = 0;
    altitude = 0;
    timezone = -1;
    dst = "No DST";
    tz = "No TZ";
}



//get functions
int Airport::getID() const{
    return ID;
}

std::string Airport::getName() const{
    return name;
}

std::string Airport::getCity() const{
    return city;
}

std::string Airport::getCountry() const{
    return country;
}

std::string Airport::getIATA() const{
    return iata;
}

float Airport::getLat() const{
    return latitude;
}

float Airport::getLong() const{
    return longitude;
}

int Airport::getAlt() const{
    return altitude;
}

int Airport::getTimezone() const{
    return timezone;
}

std::string Airport::getDST() const{
    return dst;
}

std::string Airport::getTZ() const{
    return tz;
}

std::string Airport::getByIata(std::string e){
	std::string sqlCreate = "SELECT  * FROM AIRPORT WHERE IATA = '" + e +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int AIRID;
	const char* NAME;
    const char* CITY; 
	const char* COUNTRY;
	const char* IATA;
	float LAT;
	float LONG;
	int ALT;
	int TIMEZONE;
	const char* DST;
	const char* TZ;
	
	 if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AIRID = sqlite3_column_int(stmt, 0);
            NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			CITY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // get col 1
            COUNTRY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // get col 1
            IATA= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); // get col 2
            LAT = sqlite3_column_double(stmt, 5); 
            LONG= sqlite3_column_double(stmt, 6); 
            ALT= sqlite3_column_int(stmt, 7); 		
            TIMEZONE= sqlite3_column_int(stmt, 8);
            DST= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)); // get col 1
			TZ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)); // get col 1
			
		
			
			//std::cout<<AIRID<<" "<<NAME<<" "<<CITY<<" "<<COUNTRY<<" "<<IATA<<" "<<LAT<<" "
						//<<LONG<<" "<<ALT<<" "<<TIMEZONE<<" "<<DST<<" "<<TZ<<"\n";
						
		
		
			if(IATA == NULL){
				iata = "";
			}
			else{
				iata = std::string(IATA);
			}
			
			ID = AIRID;
		
			if(NAME == NULL){
				name = "";
			}
			else{
				name = std::string(NAME); 
			}
		
			if(CITY == NULL){
				city = "";
			}
			else{
				city = std::string(CITY); 
			}
		
			if(COUNTRY == NULL){
				country = "";
			}
			else{
				country = std::string(COUNTRY); 
			}
			
			latitude = LAT;
			longitude = LONG;
			altitude = ALT;
			timezone = TIMEZONE;
			
		
			if(DST == NULL){
				dst = "";
			}
			else{
				//strcpy(dst,DST[0]);
				dst = std::string(DST);  
			}
		
			if(TZ == NULL){
				tz = "";
			}
			else{
				tz = std::string(TZ); 
			}
		
		}
		
	}
	
	sqlite3_finalize(stmt);
	
	if(iata == ""){
		return "NOT FOUND";
	}
	
	return "FOUND";
}

std::string Airport::getByName(std::string e){
	std::string sqlCreate = "SELECT * FROM AIRPORT WHERE NAME = '" + e +"';";
	//std::cout<<sqlCreate<<std::endl;
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int AIRID = -1;
	const char* NAME;
    const char* CITY; 
	const char* COUNTRY;
	const char* IATA;
	float LAT;
	float LONG;
	int ALT;
	int TIMEZONE;
	const char* DST;
	const char* TZ;
	
	 if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AIRID = sqlite3_column_int(stmt, 0);
            NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			CITY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // get col 1
            COUNTRY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // get col 1
            IATA= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); // get col 2
            LAT = sqlite3_column_double(stmt, 5); 
            LONG= sqlite3_column_double(stmt, 6); 
            ALT= sqlite3_column_int(stmt, 7); 		
            TIMEZONE= sqlite3_column_int(stmt, 8);
            DST= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)); // get col 1
			TZ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)); // get col 1
			
		
			
			//std::cout<<AIRID<<" "<<NAME<<" "<<CITY<<" "<<COUNTRY<<" "<<IATA<<" "<<LAT<<" "
						//<<LONG<<" "<<ALT<<" "<<TIMEZONE<<" "<<DST<<" "<<TZ<<"\n";
						
		
		
			if(IATA == NULL){
				iata = "";
			}
			else{
				iata = std::string(IATA);
			}
			
			ID = AIRID;
		
			if(NAME == NULL){
				name = "";
			}
			else{
				name = std::string(NAME); 
			}
		
			if(CITY == NULL){
				city = "";
			}
			else{
				city = std::string(CITY); 
			}
		
			if(COUNTRY == NULL){
				country = "";
			}
			else{
				country = std::string(COUNTRY); 
			}
			
			latitude = LAT;
			longitude = LONG;
			altitude = ALT;
			timezone = TIMEZONE;
			
		
			if(DST == NULL){
				dst = "";
			}
			else{
				//strcpy(dst,DST[0]);
				dst = std::string(DST);  
			}
		
			if(TZ == NULL){
				tz = "";
			}
			else{
				tz = std::string(TZ); 
			}
		
		}
		
	}
	
	sqlite3_finalize(stmt);
	
	if(AIRID == -1){
		return "NOT FOUND";
	}
	
	return "FOUND";
}


//set functions
void Airport::setDB(sqlite3* d){
    db=d;
}

void Airport::setID(int i){
    ID = i;
}
void Airport::setName(std::string i){
    name = i;
}

void Airport::setCity(std::string i){
    city = i;
}

void Airport::setIATA(std::string i){
    iata = i;
}

void Airport::setLat(float i){
    latitude = i;
}

void Airport::setLong(float i){
    longitude = i;
}

void Airport::setAlt(int i){
    altitude = i;
}

void Airport::setTimezone(int i){
    timezone = i;
}

void Airport::setDST(std::string i){
    dst = i;
}

void Airport::setTZ(std::string i){
    tz = i;
}

int Airport::update(){
	
	//convert any numeric attributes to string
	std::stringstream convert;
	convert << ID;
	std::string convID = convert.str();
	convert.str(std::string()); //clear ss
	
	convert << latitude;
	std::string convLat = convert.str();
	convert.str(std::string()); //clear ss
	
	convert << longitude;
	std::string convLong = convert.str();
	convert.str(std::string());//clear ss
	
	convert << altitude;
	std::string convAlt = convert.str();
	convert.str(std::string());// clear ss
	
	convert << timezone;
	std::string convTimezone = convert.str();
	convert.str(std::string()); //clear ss
	
	
   std::string createSql = "UPDATE AIRPORT SET ID = '" + convID + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET NAME = '" + name + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET CITY = '" + city + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET COUNTRY = '" + country + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET IATA = '" + iata + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET LATITUDE = '" + convLat + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET LONGITUDE = '" + convLong + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET ALTITUDE = '" + convAlt + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET TIMEZONE = '" + convTimezone + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET DST = '" + dst + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRPORT SET TZ = '" + tz + "' WHERE ID = "+ convID + "; ";
							
							//std::cout<<createSql<<std::endl;
	const char* sql = createSql.c_str();
	
   /* Execute SQL statement */
   
   char* errMsg = 0;
   int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if( err != SQLITE_OK ){
        std::cout<<"SQL error: "<<errMsg<<std::endl;
		return 1;
   }
   
   return 0;
}



std::ostream &operator<<( std::ostream &os,const Airport &A){
    os<<A.getID()<<": "<<A.getCity()<<" "<<A.getCountry()<< " "<<A.getIATA()<<" "<<A.getLat()<<" "
        <<A.getLong()<<" "<<A.getAlt()<<" "<<A.getTimezone()<<" "<<A.getDST()<<" "<<A.getTZ()<<std::endl;
    return os;
};




Airport* Airport::alphabeticList(){
	
	std::string sqlCreate =  "SELECT NAME,IATA FROM AIRPORT ORDER BY NAME ASC;" ;
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	//temporary variables for database retreival
	const char * NAME;
	const char* IATA;
	char filter = '-';
	
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			
			//get attributes from database.
			NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); //get col 0
			IATA = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			
			if(filter != NAME[0] && NAME != NULL){
				filter = NAME[0];
				cout<<"\t"<<filter<<endl<<endl;
			}
			
			cout<<"\t\t"<<NAME<<endl;
			
		}
	}
	
	return NULL;
}










