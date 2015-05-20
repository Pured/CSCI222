/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#include "ProfileManagerController.h"
#include "sqlite3.h"

ProfileManagerController::ProfileManagerController(sqlite3* d){
	db = d;
    userType = "ProfileManager";
}

void ProfileManagerController::findCustomer(){
	string e;

        cout<<"Input the customer's email: ";
	cin>>e;

	cout << endl;

	string sqlCreate = "SELECT * FROM CUSTOMER WHERE EMAIL = '" + e + "';";
	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	//create variables to store data.
	int ID, cardNum, freqFlierPts;
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

			cardNum = sqlite3_column_double(stmt, 13);	
			freqFlierPts = sqlite3_column_int(stmt, 14);

			PASSPORT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 15));
			NOFLY = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 16));
			AGENT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 17));
			PASSWORD = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 18));
  
			cout<<"ID: "<<ID<<"\nName: "<<TITLE<<". "<<FNAME<<" "<<LNAME<<"\nSex: "<<GENDER<<"\nD.O.B.: "<<DOB<<"\nPhone Number: "<<PHONE<<"\nEmail: "<<EMAIL<<"\nAddress: "<<ADDRESS<<", "<<CITY<<", "<<STATE<<", "<<COUNTRY<<"\nCard Type: "<<CARDTYPE<<"\nCard Number: "<<cardNum<<"\nFrequent Flier Points: "<<freqFlierPts<<"\nPassport: "<<PASSPORT<<"\nNo-Fly Status: "<<NOFLY<<"\nAgent: "<<AGENT<<"\nPassword: "<<PASSWORD<<endl<<endl;
		}
	}

	sqlite3_finalize(stmt);
}

void ProfileManagerController::profileReport(){
	cout << "-------- PROFILE REPORT --------" << endl;
	cout << "Monthly Profile Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";

	cout << "Daily Profile Summary:" << endl;
	cout << "Will implement after date class is ready.\n\n";
}
