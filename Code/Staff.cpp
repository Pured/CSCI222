/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include "Staff.h"

using namespace std;

// Constructors.
Staff::Staff(sqlite3 *d){
	db = d;
	userType = "None";
	userName = "No Username";
	password = "No Password";
}

Staff::Staff(sqlite3 *d, string uType, string uName, string pw){
	db = d;
	userType = uType;
	userName = uName;
	password = pw;
}

// Set functions.
void Staff::setUsername(string i){
	userName = i;
}

void Staff::setPassword(string i){
	password = i;
}

void Staff::setType(string i){
	userType = i;
}

// Sets all staff member attributes by finding their email address from the database.
string Staff::setByEmail(string e){
	string sqlCreate = "SELECT USERTYPE, EMAIL, PASSWORD FROM STAFF WHERE EMAIL = '" + e + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Create variables to store data.
	const char* UT; // Temp storage for userType.
	const char* UN; // Temp storage for userNAme.
	const char* PWD; // Temp storage for password.

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			// Get data from db.
			UT = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)); // Get column 0.
			UN = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)); // Get column 1.
			PWD = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)); // Get column 2.

			// Cast to string.
			if(UT == NULL || UN == NULL || PWD == NULL){ // Make sure UT/UN/PWD is not null, otherwise the return behaviour is undefined.
				userType = "";
				userName = "";
				password = "";
			}
			else{
				userType = string(UT);
				userName = string(UN);
				password = string(PWD);
			}
		}
	}

	sqlite3_finalize(stmt);

	return userType;
};

// Get functions.
string Staff::getPassword() const{
	return password;
}

string Staff::getType() const{
	return userType;
}

string Staff::getUsername() const{
	return userName;
}

// Other functions.
ostream &operator<<(ostream &output, const Staff &S){
	output << S.getUsername() << " " << S.getPassword();

	return output;
}
