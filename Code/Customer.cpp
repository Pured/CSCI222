/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Modified the Other functions.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Customer.h"
#include "callback.h"

using namespace std;

// Constructors.
Customer::Customer(sqlite3 *d){
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

// Get functions.
int Customer::getID() const{
	return ID;
}

string Customer::getTitle() const{
	return title;
}

string Customer::getFName() const{
	return fName;
}

string Customer::getLName() const{
	return lName;
}

string Customer::getGender() const{
	return gender;
}

string Customer::getDOB(){
	return dob;
}

string Customer::getPhone() const{
	return phone;
}

string Customer::getEmail() const{
	return email;
}

string Customer::getAddress() const{
	return address;
}

string Customer::getState() const{
	return state;
}

string Customer::getCity() const{
	return city;
}

string Customer::getCountry() const{
	return country;
}

string Customer::getCardType() const{
	return cardType;
}

long long int Customer::getCardNum() const{
	return cardNum;
}

long long int Customer::getFreqPts() const{
	return freqFlierPts;
}

string Customer::getPassport() const{
	return passport;
}

string Customer::getNoFly() const{
	return nofly;
}

string Customer::getAgent() const{
	return agent;
}

string Customer::getPassword() const{
	return password;
}

// Set functions.
void Customer::setID(int i){
	ID = i;
}

void Customer::setTitle(string i){
	title = i;
}

void Customer::setFName(string i){
	fName = i;
}

void Customer::setLName(string i){
	lName = i;
}

void Customer::setGender(string i){
	gender = i;
}

void Customer::setDOB(string i){
	dob = i;
}

void Customer::setPhone(string i){
	phone = i;
}

void Customer::setEmail(string i){
	email = i;
}

void Customer::setAddress(string i){
	address = i;
}

void Customer::setState(string i){
	state = i;
}

void Customer::setCity(string i){
	city = i;
}

void Customer::setCountry(string i){
	country = i;
}

void Customer::setCardType(string i){
	cardType = i;
}

void Customer::setCardNum(long long int i){
	cardNum = i;
}

void Customer::setFreqPts(long long int i){
	freqFlierPts = i;
}

void Customer::setPassport(string i){
	passport = i;
}

void Customer::setNoFly(string i){
	nofly = i;
}

void Customer::setAgent(string i){
	agent = i;
}

void Customer::setPassword(string i){
	password = i;
}

string Customer::getByEmail(string e){
	string sqlCreate = "SELECT   *FROM CUSTOMER WHERE EMAIL = '" + e +"';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Create variables to store data.
	const char *TITLE, *FNAME, *LNAME, *GENDER, *DOB, *PHONE, *EMAIL, *ADDRESS, *STATE, *COUNTRY, *CITY, *CARDTYPE, *PASSPORT, *NOFLY, *AGENT, *PASSWORD;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from db.
			ID = sqlite3_column_int(stmt, 0);

			TITLE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			FNAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			LNAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
			GENDER = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
			DOB = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 5));
			PHONE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6));
			EMAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7));		
			ADDRESS = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8));
			STATE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
			CITY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 10));
			COUNTRY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 11));
			CARDTYPE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 12));

			cardNum = sqlite3_column_double(stmt, 13);	
			freqFlierPts = sqlite3_column_int(stmt, 14);

			PASSPORT = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 15));
			NOFLY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 16));
			AGENT = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 17));
			PASSWORD = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 18));

			// Cast to string and ensure no attribute is cast with NULL.
			if(TITLE == NULL){ 
				title = "";
			}
			else{
				title = string(TITLE); 
			}

			if(FNAME == NULL){
				fName = "";
			}
			else{
				fName = string(FNAME); 
			}

			if(LNAME == NULL){
				lName = "";
			}
			else{
				lName = string(LNAME); 
			}

			if(GENDER == NULL){
				gender = ' ';
			}
			else{
				gender = string(GENDER); 
			}

			if(DOB == NULL){
				dob = "";
			}
			else{
				dob = string(DOB); 
			}

			if(PHONE == NULL){
				phone= "";
			}
			else{
				phone = string(PHONE); 
			}

			if(EMAIL == NULL){
				email= "";
			}
			else{
				email = string(EMAIL); 
			}

			if(ADDRESS == NULL){
				address= "";
			}
			else{
				address = string(ADDRESS); 
			}

			if(STATE == NULL){
				state= "";
			}
			else{
				state = string(STATE); 
			}

			if(CITY == NULL){
				city= "";
			}
			else{
				city = string(CITY); 
			}

			if(COUNTRY == NULL){
				country= "";
			}
			else{
				country = string(COUNTRY); 
			}

			if(CARDTYPE == NULL){
				cardType= "none";
			}
			else{
				cardType = string(CARDTYPE); 
			}

			if(PASSPORT == NULL){
				passport= "FALSE";
			}
			else{
				passport = string(PASSPORT); 
			}

			if(NOFLY == NULL){
				nofly= "";
			}
			else{
				nofly = string(NOFLY); 
			}

			if(AGENT == NULL){
				agent= "";
			}
			else{
				agent = string(AGENT); 
			}

			if(PASSWORD== NULL){
				password= "";
			}
			else{
				password = string(PASSWORD); 
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

// Other functions.
ostream &operator<<(ostream &os, Customer &C){
	// Non const function, be careful. Note: fix DOB class to enable const.
    os << "Customer ID: " << C.getID() << "\nTitle: " << C.getTitle() << "\nName: " << C.getFName() << " " << C.getLName() << " \nGender: " << C.getGender() << "\nDOB: " << C.getDOB() << "\nPhone: " << C.getPhone() << "\nEmail: " << C.getEmail() << "\nAddress: " << C.getAddress() << "\nState: " << C.getState() << "\nCity: " << C.getCity() << "\nCountry: " << C.getCountry() << "\nCredit Card Type: " << C.getCardType() << "\nCard Num: " << C.getCardNum() << "\nFreqFly: " << C.getFreqPts() << "\nPassport" << C.getPassport() << "\nNo Fly Status: " << C.getNoFly() << "\nTravel Agent: " << C.getAgent() << "\n";

	return os;
}

int Customer::createCustomer(){
	// Get next ID for new customer.
	string createSql = "SELECT COUNT(ID) FROM CUSTOMER;";
	const char *sql = createSql.c_str();
	int NEWID;

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			NEWID = sqlite3_column_int(stmt, 0); // Get data from db.
		}
	}

	sqlite3_finalize(stmt);

	NEWID++; // New unique id for customer.

	// Add object details to DB.
	stringstream convert;

	convert << NEWID;
	string convID = convert.str();

	convert << cardNum;
	string convCardNum = convert.str();

	convert << freqFlierPts;
	string convFlierPts = convert.str();

	createSql = "INSERT INTO CUSTOMER VALUES(NULL, '" + title + "', '" + fName + "', '" + lName + "', '" + gender + "', '" + dob + "', '" + phone + "', '" + email + "', '" + address + "', '" + state + "', '" + city + "', '" + country + "', '" + cardType + "', '" + convCardNum + "', '" + convFlierPts + "', '" + passport + "', '" + nofly + "', '" + agent + "', '" + password + "');";

	sql = createSql.c_str();

	// Execute SQL statement 
	char *errMsg = 0;
	err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}

int Customer::updateCustomer(){
	stringstream convert;

	convert << ID;
	string convID = convert.str();
	convert.str(string()); // Clear ss.

	convert << cardNum;
	string convCardNum = convert.str();
	convert.str(string()); // Clear ss.

	convert << freqFlierPts;
	string convFlierPts = convert.str();
	convert.str(string()); // Clear ss.

	string createSql = "UPDATE CUSTOMER SET TITLE = '" + title + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET FNAME = '" + fName + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET LNAME = '" + lName + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET GENDER = '" + gender + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET DOB = '" + dob + "' WHERE ID = "+ convID + ";" + "UPDATE CUSTOMER SET PHONE = '" + phone + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET EMAIL = '" + email + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET ADDRESS = '" + address + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET STATE = '" + state + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET CITY = '" + city + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET COUNTRY = '" + country + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET CREDCARD = '" + cardType + "' WHERE ID = "+ convID + ";" + "UPDATE CUSTOMER SET  CARDNUM = " + convCardNum + " WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET FREQFLY = " + convFlierPts + " WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET PASSPORT = '" + passport + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET STATUS = '" + nofly + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET TRAVELAGENT = '" + agent + "' WHERE ID = " + convID + ";" + "UPDATE CUSTOMER SET PASSWORD = '" + password + "' WHERE ID = " + convID + ";";

	const char *sql = createSql.c_str();
	
	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}

int Customer::deleteCustomer(){
	string sqlCreate = "DELETE FROM CUSTOMER WHERE EMAIL = '" + email + "';";
	const char *sql = sqlCreate.c_str();
	
	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}
