//
//  Customer.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "Customer.h"
#include "callback.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

//constructors
Customer::Customer(sqlite3* d){
	
	db = d;
    ID = 0;
    title = "";
    fName = "";
    lName = "";
    gender = "";
    dob = "";
    phone = "";
    email = "";
    address = "";
    state = "";
	city = "";
    country = "";
    cardType = "";
	cardNum = 0;
    freqFlierPts = 0;
    passport = "";
    nofly = "";
    agent = "";
	password = "";
	
}

//get functions;
int Customer::getID() const{
    return ID;
}

std::string Customer::getTitle() const{
	return title;
}

std::string Customer::getFName() const{
    return fName;
}

std::string Customer::getLName() const{
    return lName;
}

std::string Customer::getGender() const{
    return gender;
}

std::string Customer::getDOB(){
    return dob;
}

std::string Customer::getPhone() const{
    return phone;
}

std::string Customer::getEmail() const{
    return email;
}

std::string Customer::getAddress() const{
    return address;
}

std::string Customer::getState() const{
    return state;
}

std::string Customer::getCity() const{
    return city;
}

std::string Customer::getCountry() const{
    return country;
}

std::string Customer::getCardType() const{
    return cardType;
}

long long int Customer::getCardNum() const{
    return cardNum;
}

int Customer::getFreqPts() const{
    return freqFlierPts;
}

std::string Customer::getPassport() const{
    return passport;
}

std::string Customer::getNoFly() const{
    return nofly;
}

std::string Customer::getAgent() const{
    return agent;
}

std::string Customer::getPassword() const{
    return password;
}


//set functions
void Customer::setID(int i){
    ID = i;
}

void Customer::setTitle(std::string i){
    title = i;
}

void Customer::setFName(std::string i){
    fName = i;
}
void Customer::setLName(std::string i){
    lName = i;
}
void Customer::setGender(std::string i){
    gender = i;
}
void Customer::setDOB(std::string i){
    dob = i;
}
void Customer::setPhone(std::string i){
    phone = i;
}
void Customer::setEmail(std::string i){
    email = i;
}
void Customer::setAddress(std::string i){
    address = i;
}
void Customer::setState(std::string i){
    state = i;
}
void Customer::setCity(std::string i){
    city = i;
}
void Customer::setCountry(std::string i){
    country = i;
}
void Customer::setCardType(std::string i){
    cardType = i;
}
void Customer::setCardNum(long long int i){
    cardNum = i;
}

void Customer::setFreqPts(int i){
    freqFlierPts = i;
}
void Customer::setPassport(std::string i){
    passport = i;
}
void Customer::setNoFly(std::string i){
    nofly = i;
}
void Customer::setAgent(std::string i){
    agent = i;
}
void Customer::setPassword(std::string i){
    password = i;
}

std::string Customer::getByEmail(std::string e){
		std::string sqlCreate = "SELECT  * FROM CUSTOMER WHERE EMAIL = '" + e +"';";
	const char* sql = sqlCreate.c_str();
	
	//std::cout<<sql<<std::endl;

	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    //create variables to store data.
    const char* TITLE; //temp storage for userName;
    const char* FNAME; //temp storage for password
	const char* LNAME;
	const char* GENDER;
	const char* DOB;
	const char* PHONE;
	const char* EMAIL;
	const char* ADDRESS;
	const char* STATE;
	const char* COUNTRY;
	const char* CITY;
	const char* CARDTYPE;
	const char* PASSPORT;
	const char* NOFLY;
	const char* AGENT;
	const char* PASSWORD;

    if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
			ID = sqlite3_column_int(stmt, 0);
            TITLE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			FNAME= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // get col 1
            LNAME= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // get col 1
            GENDER= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)); // get col 2
            DOB = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)); //get col 0
            PHONE= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)); // get col 1
            EMAIL= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)); // get col 2			
            ADDRESS = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)); //get col 0
            STATE= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9)); // get col 1
			CITY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)); // get col 1
            COUNTRY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11)); // get col 2
            CARDTYPE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12)); //get col 0
			cardNum = sqlite3_column_double(stmt, 13); //get col 0		
			freqFlierPts = sqlite3_column_int(stmt, 14);
            PASSPORT= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 15)); // get col 1
            NOFLY= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16)); // get col 2
            AGENT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 17)); //get col 0
            PASSWORD= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 18)); // get col 1
  
			//std::cout<<ID<<" \n"<<TITLE<<" \n"<<FNAME<<"\n "<<LNAME<<" \n"<<GENDER<<" \n"<<DOB<<"\n "<<PHONE	
						//<<"\n "<<EMAIL<<"\n "<<ADDRESS<<"\n "<<STATE<<" \n"<<CITY<<" \n"<<COUNTRY<<" \n"<<CARDTYPE
						//<<" \n"<<cardNum<<"\n"<<freqFlierPts<<" \n"<<PASSPORT<<" \n"<<NOFLY<<" \n"<<AGENT<<"\n "<<PASSWORD;
			
			//cast to string and ensure no attribute is cast with NULL
			if(TITLE == NULL) { 
				title = "";
			}
			else{
				title = std::string(TITLE); 
			}
			
			if(FNAME == NULL){
				fName = "";
			}
			else{
				fName = std::string(FNAME); 
			}
			
			if(LNAME == NULL){
				lName = "";
			}
			else{
				lName = std::string(LNAME); 
			}
			
			if(GENDER == NULL){
				gender = ' ';
			}
			else{
				gender = std::string(GENDER); 
			}
		
			if(DOB == NULL){
				dob = "";
			}
			else{
				dob = std::string(DOB); 
			}
			
			if(PHONE == NULL){
				phone= "";
			}
			else{
				phone = std::string(PHONE); 
			}
			
			if(EMAIL == NULL){
				email= "";
			}
			else{
				email = std::string(EMAIL); 
			}
			
			if(ADDRESS == NULL){
				address= "";
			}
			else{
				address = std::string(ADDRESS); 
			}
			
			if(STATE == NULL){
				state= "";
			}
			else{
				state = std::string(STATE); 
			}
			
			if(CITY == NULL){
				city= "";
			}
			else{
				city = std::string(CITY); 
			}
			
			if(COUNTRY == NULL){
				country= "";
			}
			else{
				country = std::string(COUNTRY); 
			}
			
			if(CARDTYPE == NULL){
				cardType= "none";
			}
			else{
				cardType = std::string(CARDTYPE); 
			}
			
			if(PASSPORT == NULL){
				passport= "FALSE";
			}
			else{
				passport = std::string(PASSPORT); 
			}
			
			if(NOFLY == NULL){
				nofly= "";
			}
			else{
				nofly = std::string(NOFLY); 
			}
			
			if(AGENT == NULL){
				agent= "";
			}
			else{
				agent = std::string(AGENT); 
			}
			
			
			if(PASSWORD== NULL){
				password= "";
			}
			else{
				password = std::string(PASSWORD); 
			}
			
        }
    }

    sqlite3_finalize(stmt);
	
	
	if(e == email && password != "" ){
		return "CUSTOMER";
	}
	else if(e == email && password == ""){
		return "NOT REGISTERED";
	}
	
	return "NOT FOUND";
}


//other functions
int Customer::update(){
	
	std::stringstream convert;
	convert << ID;
	std::string convID = convert.str();
	
	convert << cardNum;
	//std::cout<<cardNum<<"\n";
	std::string convCardNum = convert.str();
	//std::cout<<convCardNum<<"\n";
	
	convert << freqFlierPts;
	std::string convFlierPts = convert.str();
	//std::cout<<convFlierPts<<"\n";
	
	
   std::string createSql = "UPDATE CUSTOMER SET TITLE = '" + title + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET FNAME = '" + fName + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET LNAME = '" + lName + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET GENDER = '" + gender + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET DOB = '" + dob + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET PHONE = '" + phone + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET EMAIL = '" + email + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET ADDRESS = '" + address + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET STATE = '" + state + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET CITY = '" + city + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET COUNTRY = '" + country + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET CREDCARD = '" + cardType + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET  CARDNUM = " + convCardNum + " WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET FREQFLY = " + convFlierPts + " WHERE ID = "+ convID + ";"
							+ 	"UPDATE CUSTOMER SET PASSPORT = '" + passport + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET STATUS = '" + nofly + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET TRAVELAGENT = '" + agent + "' WHERE ID = "+ convID + "; " 
							+ 	"UPDATE CUSTOMER SET PASSWORD = '" + password + "' WHERE ID = "+ convID + "; " ;
							
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

int Customer::deleteCust(){
	
	string sqlCreate = "DELETE FROM CUSTOMER WHERE EMAIL = '" + email + "';";
	const char* sql = sqlCreate.c_str();
	
	// Execute SQL statement 

	char* errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
	if(err != SQLITE_OK){
		cout<<"SQL error: "<<errMsg<<endl;
		return 1;
	}
	
	return 0;
}

int Customer::createCust(){
	
	//get next ID for new customer
	std::string createSql = "SELECT COUNT(ID) FROM CUSTOMER;";
	const char* sql = createSql.c_str();
	int NEWID;
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
    if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
			NEWID = sqlite3_column_int(stmt, 0);
	
        }
    }
    sqlite3_finalize(stmt);
	
	NEWID++; // new unique id for customer.
	
	//add object details to DB
	
	std::stringstream convert;
	convert << NEWID;
	std::string convID = convert.str();
	
	convert << cardNum;
	//std::cout<<cardNum<<"\n";
	std::string convCardNum = convert.str();
	//std::cout<<convCardNum<<"\n";
	
	convert << freqFlierPts;
	std::string convFlierPts = convert.str();
	//std::cout<<convFlierPts<<"\n";
	
	createSql = "INSERT INTO CUSTOMER VALUES('" + convID + "', '" + title + "', '" + fName + "', '" + lName + "', '" + gender + "', '" + dob + "', '" + phone + "', '" 
			+ email + "', '" + address + "', '" + state + "', '" + city + "', '" + country + "', '" + cardType + "', '" + convCardNum + "', '" + convFlierPts + "', '" + passport 
			+ "', '" + nofly + "', '" + agent + "', '" + password + "');";

	sql = createSql.c_str();

	// Execute SQL statement 

	char* errMsg = 0;
	err = sqlite3_exec(db, sql, callback, 0, &errMsg);
	if(err != SQLITE_OK){
		cout<<"SQL error: "<<errMsg<<endl;
		return 1;
	}

	return 0;
}


std::ostream &operator<<(std::ostream &os, Customer &C){
    //non const function, be careful. note: fix DOB class to enable const
    os<<"Customer ID: "<<C.getID()<<"\nTitle: "<<C.getTitle()<<"\nName: "<<C.getFName()<<" "<<C.getLName()<<" \nGender: "<<C.getGender()<<"\nDOB: "
            <<C.getDOB()<<"\nPhone: "<<C.getPhone()<<"\nEmail: "<<C.getEmail()<<"\nAddress: "<<C.getAddress()
            <<"\nState: "<<C.getState()<<"\nCity: "<<C.getCity()<<"\nCountry: "<<C.getCountry()<<"\nCredit Card Type: "<<C.getCardType()
            <<"\nCard Num: " << C.getCardNum()<<"\nFreqFly: "<<C.getFreqPts()<<"\nPassport"<<C.getPassport()<<"\nNo Fly Status: "<<C.getNoFly()<<"\nTravel Agent: "<<C.getAgent()<<"\n";
    return os;
}