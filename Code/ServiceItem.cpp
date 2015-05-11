//
//  ServiceItem.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "ServiceItem.h"
#include <sstream>
#include "callback.h"
#include "sqlite3.h"

//constructors
ServiceItem::ServiceItem(sqlite3* d){
	db=d;
    ID = -1;
    item = "No Item";
    cost = 0;
    avail = "No Availability";
}


//get functions
int ServiceItem::getID() const{
    return ID;
}

std::string ServiceItem::getItem() const{
    return item;
}

float ServiceItem::getCost() const{
    return cost;
    
}
std::string ServiceItem::getAvail() const{
    return avail;
}

std::string ServiceItem::getByID(int id){
	std::stringstream convert;
	convert << id;
	std::string convid = convert.str();
	convert.str(std::string()); //clear ss
	
	std::string sqlCreate = "SELECT  * FROM SERVICEITEM WHERE ID = '" + convid +"';";
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int SVCID = -1;
	const char* ITEM;
	const char* AVAIL;
	float COST;
	
	if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			SVCID = sqlite3_column_int(stmt, 0);
            ITEM = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			COST = sqlite3_column_double(stmt, 2); 
            AVAIL= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // get col 1
			
			std::cout<<SVCID<<" "<<ITEM<<" "<<COST<<" "<<AVAIL<<"\n";
			
			if(ITEM == NULL){
				item = "";
			}
			else{
				item = std::string(ITEM);
			}
			
			if(AVAIL == NULL){
				avail = "";
			}
			else{
				avail = std::string(AVAIL);
			}
			
			ID = SVCID;
			cost = COST;
		}
	}
	
	sqlite3_finalize(stmt);
	
	if(ID == -1){
		return "NOT FOUND";
	}
	
	return "FOUND";
}

//set functions
void ServiceItem::setID(int i){
    ID = i;
}
void ServiceItem::setItem(std::string i){
    item = i;
}
void ServiceItem::setCost(float i){
    cost = i;
}
void ServiceItem::setAvail(std::string i){
    avail = i;
}

int ServiceItem::update(){
	
	
	if(ID != -1){
		//convert any numeric attributes to string
		std::stringstream convert;
		convert << ID;
		std::string convID = convert.str();
		convert.str(std::string()); //clear ss
	
		convert << cost;
		std::string convCost = convert.str();
		convert.str(std::string()); //clear ss
	
	
		std::string createSql = "UPDATE SERVICEITEM SET ID = '" + convID + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE SERVICEITEM SET ITEM = '" + item + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE SERVICEITEM SET COST = '" + convCost + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE SERVICEITEM SET AVAILABILITY = '" + avail + "' WHERE ID = "+ convID + "; ";

							
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
std::ostream &operator<<( std::ostream &os,const ServiceItem &S){
    os<<"Service Item ID: "<<S.getID()<<"\nItem: "<<S.getItem()<<"\nCost: "<<S.getCost()
        <<"\nAvailability: "<<S.getAvail()<<"\n";
    return os;
}