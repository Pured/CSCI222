/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#include "BookingManagerController.h"
#include <iostream>
#include <sstream>

using namespace std;

BookingManagerController::BookingManagerController(sqlite3* d){
	db = d;
    userType = "BookingManager";
}

void BookingManagerController::findCustomer(){
	string e;

        cout<<"Input the customer's email: ";
	cin>>e;

	cout << endl;

	string sqlCreate = "SELECT * FROM CUSTOMER WHERE EMAIL = '" + e + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, CARDNUM, FREQFLIERPTS;
	const char* TITLE;
	const char* FNAME;
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
	cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			TITLE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			FNAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
			LNAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
			GENDER = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
			DOB = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
			PHONE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
			EMAIL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
			ADDRESS = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
			STATE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
			CITY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
			COUNTRY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
			CARDTYPE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 12));

			CARDNUM = sqlite3_column_double(stmt, 13);	
			FREQFLIERPTS = sqlite3_column_int(stmt, 14);

			PASSPORT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 15));
			NOFLY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16));
			AGENT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 17));
			PASSWORD = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 18));
  
			cout<<"ID: "<<ID<<"\nName: "<<TITLE<<". "<<FNAME<<" "<<LNAME<<"\nSex: "<<GENDER<<"\nD.O.B.: "<<DOB<<"\nPhone Number: "<<PHONE<<"\nEmail: "<<EMAIL<<"\nAddress: "<<ADDRESS<<", "<<CITY<<", "<<STATE<<", "<<COUNTRY<<"\nCard Type: "<<CARDTYPE<<"\nCard Number: "<<CARDNUM<<"\nFrequent Flier Points: "<<FREQFLIERPTS<<"\nPassport: "<<PASSPORT<<"\nNo-Fly Status: "<<NOFLY<<"\nAgent: "<<AGENT<<"\nPassword: "<<PASSWORD<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void BookingManagerController::createCustomer(){
	//create variables to store data.
	int lastID, ID, CARDNUM, FREQFLIERPTS;
	string TITLE, FNAME, LNAME, GENDER, DOB, PHONE, EMAIL, ADDRESS, STATE, COUNTRY, CITY, CARDTYPE, PASSPORT, NOFLY, AGENT, PASSWORD;

	//lastID = sqlstuff ... "SELECT LAST(ID) FROM CUSTOMER;";

	ID = lastID + 1;

	cout << "Creating a new Customer..." << endl;
	cout << "Customer ID: " << ID << endl;

	cout << "Title: ";
	getline(cin, TITLE);

	cout << "Given Name: ";
	getline(cin, FNAME);

	cout << "Surname: ";
	getline(cin, LNAME);

	cout << "Sex: ";
	getline(cin, GENDER);

	cout << "D.O.B.: ";
	getline(cin, DOB);

	cout << "Phone: ";
	getline(cin, PHONE);

	cout << "Email: ";
	getline(cin, EMAIL);

	cout << "Address: ";
	getline(cin, ADDRESS);

	cout << "City: ";
	getline(cin, CITY);

	cout << "State: ";
	getline(cin, STATE);

	cout << "Country: ";
	getline(cin, COUNTRY);

	cout << "Card Type: ";
	getline(cin, CARDTYPE);

	cout << "Card Number: ";
	cin >> CARDNUM;

	cout << "Frequent Flier Points: ";
	cin >> FREQFLIERPTS;

	cin.ignore();

	cout << "Passport: ";
	getline(cin, PASSPORT);

	cout << "No-Fly Status: ";
	getline(cin, NOFLY);

	cout << "Agent: ";
	getline(cin, AGENT);

	cout << "Password: ";
	getline(cin, PASSWORD);

	stringstream convert;

	convert << ID;
	string convID = convert.str();
	
	convert << CARDNUM;
	string convCARDNUM = convert.str();
	
	convert << FREQFLIERPTS;
	string convFlierPts = convert.str();

	string createSql = "INSERT INTO CUSTOMER VALUES('" + convID + "', '" + TITLE + "', '" + FNAME + "', '" + LNAME + "', '" + GENDER + "', '" + DOB + "', '" + PHONE + "', '" + EMAIL + "', '" + ADDRESS + "', '" + STATE + "', '" + CITY + "', '" + COUNTRY + "', '" + CARDTYPE + "', '" + convCARDNUM + "', '" + convFlierPts + "', '" + PASSPORT + "', '" + NOFLY + "', '" + AGENT + "', '" + PASSWORD + "');";

	const char* sql = createSql.c_str();

	/* Execute SQL statement */
/*
	char* errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);
	if(err != SQLITE_OK){
		cout<<"SQL error: "<<errMsg<<endl;
		return 1;
	}
*/
}

void BookingManagerController::editCustomer(){

}

void BookingManagerController::deleteCustomer(){
	string e;

	cout << "Input the email of the account you wish to delete: ";
	cin>>e;

	cout << endl;

	string sqlCreate = "DELETE FROM CUSTOMER WHERE EMAIL = '" + e + "';";
	const char* sql = sqlCreate.c_str();

	//execute sql delete here ... somehow
}

void BookingManagerController::checkNoFly(){
	std::string sqlCreate = "SELECT * FROM CUSTOMER WHERE STATUS IS NOT '';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID;
	const char* TITLE;
	const char* FNAME;
	const char* LNAME;
	const char* EMAIL;
	const char* NOFLY;

	if (err != SQLITE_OK) {
	std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
			ID = sqlite3_column_int(stmt, 0);

			TITLE = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			FNAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // get col 1
			LNAME = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // get col 1
			EMAIL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)); // get col 2
			NOFLY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16)); // get col 2
  
			cout<<"ID: "<<ID<<"\nName: "<<TITLE<<". "<<FNAME<<" "<<LNAME<<"\nUsername: "<<EMAIL<<"\nNo-Fly Status: "<<NOFLY<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void BookingManagerController::bookingReport(){
	cout << "-------- BOOKING REPORT --------" << endl;
	cout << "Monthly Booking Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Booking Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
