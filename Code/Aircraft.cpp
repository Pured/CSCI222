//
//  Aircraft.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "Aircraft.h"
#include "callback.h"
#include <sstream>

Aircraft::Aircraft(sqlite3* d){
	db = d;
    ID = 0;
    name = "No Name";
    inService = -1;
    fClass = -1;
    bClass = -1;
    peClass = -1;
    eClass = -1;
    totalSeats = -1;
}

//get functions
int Aircraft::getID() const{
    return ID;
}

std::string Aircraft::getName() const{
    return name;
}

int Aircraft::getInService() const{
    return inService;
}

int Aircraft::getFClass() const{
    return fClass;
}

int Aircraft::getBClass() const{
    return bClass;
}

int Aircraft::getPEClass() const{
    return peClass;
}

int Aircraft::getEClass() const{
    return eClass;
}

int Aircraft::getTotalSeats() const{
    return totalSeats;
}

std::string Aircraft::getByID(std::string e){
	std::string sqlCreate = "SELECT  * FROM AIRCRAFT WHERE ID = '" + e +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	const char* NAME;
	int AIRID = 0,INSERV,FC,BC,PEC,EC,TOT;
	
	
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AIRID = sqlite3_column_int(stmt, 0);
            NAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			INSERV= sqlite3_column_int(stmt, 2); 
			FC= sqlite3_column_int(stmt, 3); 
			BC= sqlite3_column_int(stmt, 4); 
			PEC= sqlite3_column_int(stmt, 5); 
			EC= sqlite3_column_int(stmt, 6); 
			TOT= sqlite3_column_int(stmt, 7);
			
			if(NAME == NULL){
				name = "";
			}
			else{
				name = std::string(NAME);
			}
			
			ID = AIRID;
			inService = INSERV;
			fClass = FC;
			bClass = BC;
			peClass = PEC;
			eClass = EC;
			totalSeats = TOT;
		}
	}
	
	sqlite3_finalize(stmt);
	
		if(ID == 0){
			return "NOT FOUND";
		}
	
		return "FOUND";
}

//set functions
void Aircraft::setID(int i){
    ID = i;
}

void Aircraft::setName(std::string i){
    name = i;
}

void Aircraft::setInService(int i){
    inService = i;
}

void Aircraft::setFClass(int i){
    fClass = i;
    setTotalSeats(); //update total
}

void Aircraft::setBClass(int i){
    bClass = i;
    setTotalSeats(); //update total
}

void Aircraft::setPEClass(int i){
    peClass = i;
    setTotalSeats(); //update total
}

void Aircraft::setEClass(int i){
    eClass = i;
    setTotalSeats(); //update total
}

void Aircraft::setTotalSeats(){
     totalSeats = fClass + bClass + peClass + eClass;
}

int Aircraft::update(){
		//convert any numeric attributes to string
	std::stringstream convert;
	convert << ID;
	std::string convID = convert.str();
	convert.str(std::string()); //clear ss
	
	convert << inService;
	std::string convIS = convert.str();
	convert.str(std::string()); //clear ss
	
	convert << fClass;
	std::string convFC = convert.str();
	convert.str(std::string());//clear ss
	
	convert << bClass;
	std::string convBC = convert.str();
	convert.str(std::string());// clear ss
	
	convert << peClass;
	std::string convPEC = convert.str();
	convert.str(std::string()); //clear ss
	
	convert << eClass;
	std::string convEC = convert.str();
	convert.str(std::string()); //clear ss
	
	convert << totalSeats;
	std::string convTOT = convert.str();
	convert.str(std::string()); //clear ss
	
	
   std::string createSql = "UPDATE AIRCRAFT SET ID = '" + convID + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET NAME = '" + name + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET INSERVICE = '" + convIS + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET FCLASS = '" + convFC + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET BCLASS = '" + convBC + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET PECLASS = '" + convPEC + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET ECLASS = '" + convEC + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE AIRCRAFT SET TOTAL = '" + convTOT + "' WHERE ID = "+ convID + "; " ;

							
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

std::ostream &operator<<( std::ostream &os,const Aircraft &A){
    os<<A.getID()<<": "<<A.getName()<<" "<<A.getInService()<< " "<<A.getFClass()<<" "<<A.getBClass()<<" "
        <<A.getPEClass()<<" "<<A.getEClass()<<" "<<A.getTotalSeats()<<"\n";
    return os;
};