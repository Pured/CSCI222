//
//  TravelAgent.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "TravelAgent.h"
#include <sstream>
#include "callback.h"
#include "sqlite3.h"

//constructors
TravelAgent::TravelAgent(sqlite3* d){
	db=d;
    ID = -1;
    name = "No Name";
    phone = "No Phone";
    email = "No Email";
}


//get functions
int TravelAgent::getID() const{
    return ID;
}

std::string TravelAgent::getName() const{
    return name;
}

std::string TravelAgent::getPhone() const{
    return phone;
}

std::string TravelAgent::getEmail() const{
    return email;
}

std::string TravelAgent::getPassword() const{
    return password;
}

std::string TravelAgent::getByName(std::string n){
	std::stringstream convert;
	convert << ID;
	std::string convid = convert.str();
	convert.str(std::string()); //clear ss
	
	std::string sqlCreate = "SELECT  * FROM TRAVELAGENT WHERE NAME = '" + n +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int AGTID = -1;
	const char* NAME;
	const char* PHONE;
	const char* EMAIL;
	const char* PASSWORD;
	
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AGTID = sqlite3_column_int(stmt, 0);
            NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			PHONE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); //get col 0
			EMAIL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); //get col 0
			PASSWORD = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); //get col 0
			
			std::cout<<AGTID<<" "<<NAME<<" "<<PHONE<<" "<<EMAIL<<PASSWORD<<"\n";
			
			if(NAME == NULL){
				name = "";
			}
			else{
				name = std::string(NAME);
			}
			
			if(PHONE == NULL){
				phone = "";
			}
			else{
				phone = std::string(PHONE);
			}
			
			if(EMAIL == NULL){
				email = "";
			}
			else{
				email = std::string(EMAIL);
			}
			
			if(PASSWORD == NULL){
				password = "";
			}
			else{
			 password = std::string(PASSWORD);
			}
			
			ID = AGTID;
		}
	}
	
	sqlite3_finalize(stmt);
	
	if(ID == -1){
		return "NOT FOUND";
	}
	
	return "FOUND";
}

//set functions
void TravelAgent::setID(int i){
    ID = i;
}

void TravelAgent::setName(std::string i){
    name = i;
}

void TravelAgent::setPhone(std::string i){
    phone = i;
}

std::string TravelAgent::setByEmail(std::string i){
std::stringstream convert;
	
	std::string sqlCreate = "SELECT  * FROM TRAVELAGENT WHERE EMAIL = '" + i +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int AGTID = -1;
	const char* NAME;
	const char* PHONE;
	const char* EMAIL;
	const char* PASSWORD;
	
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AGTID = sqlite3_column_int(stmt, 0);
            NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			PHONE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); //get col 0
			EMAIL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); //get col 0
			PASSWORD = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); //get col 0
			
			
			//std::cout << AGTID << " " << NAME << " " << PHONE << " " << EMAIL << " " << PASSWORD <<"\n";
			
			if(NAME == NULL){
				name = "";
			}
			else{
				name = std::string(NAME);
			}
			
			if(PHONE == NULL){
				phone = "";
			}
			else{
				phone = std::string(PHONE);
			}
			
			if(EMAIL == NULL){
				email = "";
			}
			else{
				email = std::string(EMAIL);
			}
			
			if(PASSWORD == NULL){
				password = "";
			}
			else{
			 password = std::string(PASSWORD);
			}
			
			ID = AGTID;
		}
	}
	
	sqlite3_finalize(stmt);
	
	if(ID == -1){
		return "NOT FOUND";
	}
	
	return "TRAVELAGENT";
}

int TravelAgent::update(){
		
	if(ID != -1){
		//convert any numeric attributes to string
		std::stringstream convert;
		convert << ID;
		std::string convID = convert.str();
		convert.str(std::string()); //clear s
	
		std::string createSql = "UPDATE TRAVELAGENT SET ID = '" + convID + "' WHERE NAME = '"+ name + "'; " 
							+ 	"UPDATE TRAVELAGENT SET NAME = '" + name + "' WHERE NAME = '"+ name + "'; " 
							+ 	"UPDATE TRAVELAGENT SET PHONE = '" + phone + "' WHERE NAME = '"+ name + "'; " 
							+ 	"UPDATE TRAVELAGENT SET EMAIL = '" + email + "' WHERE NAME = '"+ name + "'; "
                            +   "UPDATE TRAVELAGENT SET PASSWORD = '" + password + "'WHERE NAME = '"+ name + "'; ";

							
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
		std::cout<<"ServiceItem  not initialised in UPDATE."<<std::endl;
		return 1;
	}

   return 0;
}

//other functions
std::ostream &operator<<( std::ostream &os, const TravelAgent &T){
    os<<"Travel Agent ID: "<<T.getID()<<"\nName: "<<T.getName()<<"\nPhone: "<<T.getPhone()<<"\nEmail: "<<T.getEmail()<<"Password: "<<T.getPassword()<<"\n";
    return os;
}